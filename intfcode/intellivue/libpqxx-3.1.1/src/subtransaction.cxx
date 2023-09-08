/*-------------------------------------------------------------------------
 *
 *   FILE
 *	subtransaction.cxx
 *
 *   DESCRIPTION
 *      implementation of the pqxx::subtransaction class.
 *   pqxx::transaction is a nested transaction, i.e. one within a transaction
 *
 * Copyright (c) 2005-2009, Jeroen T. Vermeulen <jtv@xs4all.nl>
 *
 * See COPYING for copyright license.  If you did not receive a file called
 * COPYING with this source code, please notify the distributor of this mistake,
 * or contact the author.
 *
 *-------------------------------------------------------------------------
 */
#include "pqxx/compiler-internal.hxx"

#include <stdexcept>

#include "pqxx/connection_base"
#include "pqxx/subtransaction"

#include "pqxx/internal/gates/transaction-subtransaction.hxx"

using namespace PGSTD;
using namespace pqxx::internal;


pqxx::subtransaction::subtransaction(dbtransaction &T,
    const PGSTD::string &Name) :
  namedclass("subtransaction", T.conn().adorn_name(Name)),
  transactionfocus(T),
  dbtransaction(T.conn(), false),
  m_parent(T)
{
#if defined(PQXX_HAVE_PQSERVERVERSION)
  check_backendsupport();
#endif
}


void pqxx::subtransaction::do_begin()
{
  try
  {
    DirectExec(("SAVEPOINT \"" + name() + "\"").c_str());
  }
  catch (const sql_error &)
  {
#if !defined(PQXX_HAVE_PQSERVERVERSION)
    check_backendsupport();
#endif
    throw;
  }
}


void pqxx::subtransaction::do_commit()
{
  const int ra = m_reactivation_avoidance.get();
  m_reactivation_avoidance.clear();
  DirectExec(("RELEASE SAVEPOINT \"" + name() + "\"").c_str());
  gate::transaction_subtransaction(m_parent).add_reactivation_avoidance_count(
	ra);
}


void pqxx::subtransaction::do_abort()
{
  DirectExec(("ROLLBACK TO SAVEPOINT \"" + name() + "\"").c_str());
}


void pqxx::subtransaction::check_backendsupport() const
{
  if (!m_parent.conn().supports(connection_base::cap_nested_transactions))
    throw feature_not_supported(
	"Backend version does not support nested transactions");
}

