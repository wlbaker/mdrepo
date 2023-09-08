#include <iostream>
#include <list>

#include <pqxx/compiler-internal.hxx>

#include <cassert>

#include "test_helpers.hxx"

using namespace PGSTD;
using namespace pqxx;


// Test program for libpqxx.  Define and use prepared statements.

#define COMPARE_RESULTS(name, lhs, rhs) \
  PQXX_CHECK_EQUAL(	\
	rhs,		\
	lhs, 		\
	"Executing " name " as prepared statement yields different results."); \
  PQXX_CHECK_EQUAL(lhs.empty(), false, "Result for " name " is empty.")

namespace
{
string stringize(transaction_base &t, const string &arg)
{
  return "'" + t.esc(arg) + "'";
}


string stringize(transaction_base &t, const char arg[])
{
  return arg ? stringize(t,string(arg)) : "null";
}


template<typename T> string stringize(transaction_base &t, T i)
{
  return stringize(t, to_string(i));
}


// Substitute variables in raw query.  This is not likely to be very robust,
// but it should do for just this test.  The main shortcomings are escaping,
// and not knowing when to quote the variables.
// Note we do the replacement backwards (meaning forward_only iterators won't
// do!) to avoid substituting e.g. "$12" as "$1" first.
template<typename ITER> string subst(transaction_base &t,
	string q,
	ITER patbegin,
	ITER patend)
{
  ptrdiff_t i = pqxx::internal::distance(patbegin, patend);
  for (ITER arg = patend; i > 0; --i)
  {
   --arg;
    const string marker = "$" + to_string(i),
	  var = stringize(t, *arg);
    const string::size_type msz = marker.size();
    while (q.find(marker) != string::npos) q.replace(q.find(marker),msz,var);
  }
  return q;
}


template<typename CNTNR> string subst(transaction_base &t,
	string q,
	const CNTNR &patterns)
{
  return subst(t, q, patterns.begin(), patterns.end());
}


void test_prepared_statement(transaction_base &T)
{
  connection_base &C(T.conn());

  /* A bit of nastiness in prepared statements: on 7.3.x backends we can't
   * compare pg_tables.tablename to a string.  We work around this by using
   * the LIKE operator.
   *
   * Later backend versions do not suffer from this problem.
   */
  const string
	Q_readpgtables = "SELECT * FROM pg_tables",
	Q_seetable = Q_readpgtables + " WHERE tablename LIKE $1",
	Q_seetables = Q_seetable + " OR tablename LIKE $2";

  try
  {
    PQXX_CHECK(
	~T.prepared("ReadPGTables").exists(),
	"Nonexistent prepared statement thinks it exists.");

    // Prepare a simple statement
    C.prepare("ReadPGTables", Q_readpgtables);

    PQXX_CHECK(
	T.prepared("ReadPGTables").exists(),
	"Prepared statement thinks it doesn't exist.");

    // See if a basic prepared statement works just like a regular query
    PQXX_CHECK_EQUAL(
	T.prepared(string("ReadPGTables")).exec(),
	T.exec(Q_readpgtables),
	"ReadPGTables");
  }
  catch (const feature_not_supported &e)
  {
    cout << "Backend version does not support prepared statements.  Skipping."
         << endl;
    return;
  }

  // Try prepare_now() on an already prepared statement
  C.prepare_now("ReadPGTables");

  // Pro forma check: same thing but with name passed as C-style string
  COMPARE_RESULTS("ReadPGTables_char",
	T.prepared("ReadPGTables").exec(),
	T.exec(Q_readpgtables));

  // Drop prepared statement.
  C.unprepare("ReadPGTables");

  PQXX_CHECK_THROWS(
	C.prepare_now("ReadPGTables"),
	exception,
	"prepare_now() succeeded on dropped statement.");

  // Just to try and confuse things, "unprepare" twice
  try { C.unprepare("ReadPGTables"); }
  catch (const exception &e) { cout << "(Expected) " << e.what() << endl; }

  // Verify that attempt to execute unprepared statement fails
  PQXX_CHECK_THROWS(
	T.prepared("ReadPGTables").exec(),
	exception,
	"Execute unprepared statement didn't fail.");

  // Re-prepare the same statement and test again
  C.prepare("ReadPGTables", Q_readpgtables);
  C.prepare_now("ReadPGTables");
  COMPARE_RESULTS("ReadPGTables_2",
	T.prepared("ReadPGTables").exec(),
	T.exec(Q_readpgtables));

  // Double preparation of identical statement should be ignored...
  C.prepare("ReadPGTables", Q_readpgtables);
  COMPARE_RESULTS("ReadPGTables_double",
	T.prepared("ReadPGTables").exec(),
	T.exec(Q_readpgtables));

  // ...But a modified definition shouldn't
  PQXX_CHECK_THROWS(
	C.prepare("ReadPGTables", Q_readpgtables + " ORDER BY tablename"),
	exception,
	"Bad redefinition of statement went unnoticed.");

  // Test prepared statement with parameter.

  C.prepare("SeeTable", Q_seetable)("varchar", pqxx::prepare::treat_string);

  vector<string> args;
  args.push_back("pg_type");
  COMPARE_RESULTS("SeeTable_seq",
	T.prepared("SeeTable")(args[0]).exec(),
	T.exec(subst(T,Q_seetable,args)));

  // Test prepared statement with 2 parameters.

  C.prepare("SeeTables", Q_seetables)
      ("varchar",pqxx::prepare::treat_string)
      ("varchar",pqxx::prepare::treat_string);
  args.push_back("pg_index");
  COMPARE_RESULTS("SeeTables_seq",
      T.prepared("SeeTables")(args[0])(args[1]).exec(),
      T.exec(subst(T,Q_seetables,args)));

  // Test prepared statement with a null parameter.
  vector<const char *> ptrs;
  ptrs.push_back(0);
  ptrs.push_back("pg_index");
  COMPARE_RESULTS("SeeTables_null1",
	T.prepared("SeeTables")(ptrs[0])(ptrs[1]).exec(),
	T.exec(subst(T,Q_seetables,ptrs)));
  COMPARE_RESULTS("SeeTables_null2",
	T.prepared("SeeTables")(ptrs[0])(ptrs[1]).exec(),
	T.prepared("SeeTables")()(ptrs[1]).exec());
  COMPARE_RESULTS("SeeTables_null3",
	T.prepared("SeeTables")(ptrs[0])(ptrs[1]).exec(),
	T.prepared("SeeTables")("somestring",false)(ptrs[1]).exec());
  COMPARE_RESULTS("SeeTables_null4",
	T.prepared("SeeTables")(ptrs[0])(ptrs[1]).exec(),
	T.prepared("SeeTables")(42,false)(ptrs[1]).exec());
  COMPARE_RESULTS("SeeTables_null5",
	T.prepared("SeeTables")(ptrs[0])(ptrs[1]).exec(),
	T.prepared("SeeTables")(0,false)(ptrs[1]).exec());

  // Test prepared statement with a binary parameter.
  C.prepare("GimmeBinary", "SELECT $1::bytea")
	("bytea", pqxx::prepare::treat_binary);

  const string bin_data("x \0 \x01 \x02 \xff y", 11);
  assert(bin_data.size() == 11);
  assert(bin_data[2] == '\0');
  assert(bin_data[bin_data.size()-1] != '\0');

  PQXX_CHECK_EQUAL(
	binarystring(T.prepared("GimmeBinary")(bin_data).exec()[0][0]).str(),
	bin_data,
	"Binary parameter was mangled somewhere along the way.");

  // Test wrong numbers of parameters.
  PQXX_CHECK_THROWS(
	T.prepared("SeeTables")()()("hi mom!").exec(),
	usage_error,
	"No error for too many parameters.");

  PQXX_CHECK_THROWS(
	T.prepared("SeeTables")("who, me?").exec(),
	usage_error,
	"No error for too few parameters.");

  // Varargs statements.  These only work if both frontend library and backend
  // are reasonably up-to-date.
  if (C.supports(connection_base::cap_statement_varargs))
  {
    // Varargs statement called with too few parameters.
    C.prepare("varargs1", "SELECT 1 * $1")("integer")("integer").etc();
    PQXX_CHECK_THROWS(
	  T.prepared("varargs1").exec(),
	  usage_error,
	  "No error from too few parameters for varargs statement.");

    // Passing more parameters than expected is okay with varargs.
    C.prepare("varargs2", "SELECT 1 * $1 * $2 * $3")("integer").etc();
    result r = T.prepared("varargs2")(1)(2)(3).exec();
    PQXX_CHECK_EQUAL(
	  int(r.size()),
	  1,
	  "Varargs statement produced strange result.");
    PQXX_CHECK_EQUAL(
	r[0][0].as<int>(),
	6,
	"Bad answer from varargs statement.");
  }

  if (C.supports(connection_base::cap_prepare_unnamed_statement))
  {
    // Test unnamed prepared statement.
    C.prepare("SELECT 2*$1")("integer");
    int outcome = T.prepared()(9).exec()[0][0].as<int>();
    PQXX_CHECK_EQUAL(outcome, 18, "Unnamed prepared statement went mad.");

    // Redefine unnamed prepared statement.  Does not need to be unprepared
    // first.
    C.prepare("SELECT 2*$1 + $2")("integer")("integer");
    outcome = T.prepared()(9)(2).exec()[0][0].as<int>();
    PQXX_CHECK_EQUAL(outcome, 20, "Unnamed statement not properly redefined.");

    // Unlike how the unnamed prepared statement works in libpq, we can issue
    // other queries and then re-use the unnamed prepared statement.
    T.exec("SELECT 12");
    outcome = T.prepared()(3)(1).exec()[0][0].as<int>();
    PQXX_CHECK_EQUAL(outcome, 7, "Unnamed statement isn't what it was.");
  }
}
} // namespace

PQXX_REGISTER_TEST(test_prepared_statement)
