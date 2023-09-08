################################################################################
# AUTOMATICALLY GENERATED FILE--DO NOT EDIT
#
# This file is generated automatically by libpqxx's template2mak.py script.
#
# If you modify this file, chances are your modifications will be lost because
# the file will be re-written from time to time.
#
# The template2mak.py script should be available in the tools directory of the
# libpqxx source archive.
#
# Generated from template '/home/jtv/proj/libpqxx/tags/3.1.1/win32/mingw.mak.template'.
################################################################################
# MinGW makefile for libpqxx.  Don't use this; use the configure script instead!
# Based on original contributed by Pasquale Fersini <basquale.fersini@libero.it>

include "win32/common"

CXX = g++.exe

OBJ = \
  "src/binarystring.o" \
  "src/connection.o" \
  "src/connection_base.o" \
  "src/cursor.o" \
  "src/dbtransaction.o" \
  "src/except.o" \
  "src/largeobject.o" \
  "src/nontransaction.o" \
  "src/notify-listen.o" \
  "src/pipeline.o" \
  "src/prepared_statement.o" \
  "src/result.o" \
  "src/robusttransaction.o" \
  "src/statement_parameters.o" \
  "src/strconv.o" \
  "src/subtransaction.o" \
  "src/tablereader.o" \
  "src/tablestream.o" \
  "src/tablewriter.o" \
  "src/transaction.o" \
  "src/transaction_base.o" \
  "src/util.o" \


LDFLAGS = -L$(LIBPATH1) -L$(LIBPATH2) --export-all-symbols --add-stdcall-alias -fpic
LIBS = -lpq -lm -lwsock32

CPPFLAGS = -Iinclude -I$(PGSQLSRC)/src/include -I$(PGSQLSRC)/src/interfaces \
  -DBUILDING_DLL -DPQXX_SHARED -DPGSTD=$(STD)

BIN = libpqxx.dll

.PHONY: all clean

all: libpqxx.dll

clean:
	rm -f $(OBJ) $(BIN)

DLLWRAP=dllwrap.exe
DEFFILE=libpqxx.def
STATICLIB=libpqxx.a

$(BIN): $(OBJ)
	$(DLLWRAP) --output-def $(DEFFILE) --driver-name c++ --implib $(STATICLIB) $(OBJ) $(LDFLAGS) $(LIBS) -o $(BIN)

src/binarystring.o: src/binarystring.cxx
	$(CXX) $(CPPFLAGS) -c src/binarystring.cxx -o src/binarystring.o $(CXXFLAGS)

src/connection.o: src/connection.cxx
	$(CXX) $(CPPFLAGS) -c src/connection.cxx -o src/connection.o $(CXXFLAGS)

src/connection_base.o: src/connection_base.cxx
	$(CXX) $(CPPFLAGS) -c src/connection_base.cxx -o src/connection_base.o $(CXXFLAGS)

src/cursor.o: src/cursor.cxx
	$(CXX) $(CPPFLAGS) -c src/cursor.cxx -o src/cursor.o $(CXXFLAGS)

src/dbtransaction.o: src/dbtransaction.cxx
	$(CXX) $(CPPFLAGS) -c src/dbtransaction.cxx -o src/dbtransaction.o $(CXXFLAGS)

src/except.o: src/except.cxx
	$(CXX) $(CPPFLAGS) -c src/except.cxx -o src/except.o $(CXXFLAGS)

src/largeobject.o: src/largeobject.cxx
	$(CXX) $(CPPFLAGS) -c src/largeobject.cxx -o src/largeobject.o $(CXXFLAGS)

src/nontransaction.o: src/nontransaction.cxx
	$(CXX) $(CPPFLAGS) -c src/nontransaction.cxx -o src/nontransaction.o $(CXXFLAGS)

src/notify-listen.o: src/notify-listen.cxx
	$(CXX) $(CPPFLAGS) -c src/notify-listen.cxx -o src/notify-listen.o $(CXXFLAGS)

src/pipeline.o: src/pipeline.cxx
	$(CXX) $(CPPFLAGS) -c src/pipeline.cxx -o src/pipeline.o $(CXXFLAGS)

src/prepared_statement.o: src/prepared_statement.cxx
	$(CXX) $(CPPFLAGS) -c src/prepared_statement.cxx -o src/prepared_statement.o $(CXXFLAGS)

src/result.o: src/result.cxx
	$(CXX) $(CPPFLAGS) -c src/result.cxx -o src/result.o $(CXXFLAGS)

src/robusttransaction.o: src/robusttransaction.cxx
	$(CXX) $(CPPFLAGS) -c src/robusttransaction.cxx -o src/robusttransaction.o $(CXXFLAGS)

src/statement_parameters.o: src/statement_parameters.cxx
	$(CXX) $(CPPFLAGS) -c src/statement_parameters.cxx -o src/statement_parameters.o $(CXXFLAGS)

src/strconv.o: src/strconv.cxx
	$(CXX) $(CPPFLAGS) -c src/strconv.cxx -o src/strconv.o $(CXXFLAGS)

src/subtransaction.o: src/subtransaction.cxx
	$(CXX) $(CPPFLAGS) -c src/subtransaction.cxx -o src/subtransaction.o $(CXXFLAGS)

src/tablereader.o: src/tablereader.cxx
	$(CXX) $(CPPFLAGS) -c src/tablereader.cxx -o src/tablereader.o $(CXXFLAGS)

src/tablestream.o: src/tablestream.cxx
	$(CXX) $(CPPFLAGS) -c src/tablestream.cxx -o src/tablestream.o $(CXXFLAGS)

src/tablewriter.o: src/tablewriter.cxx
	$(CXX) $(CPPFLAGS) -c src/tablewriter.cxx -o src/tablewriter.o $(CXXFLAGS)

src/transaction.o: src/transaction.cxx
	$(CXX) $(CPPFLAGS) -c src/transaction.cxx -o src/transaction.o $(CXXFLAGS)

src/transaction_base.o: src/transaction_base.cxx
	$(CXX) $(CPPFLAGS) -c src/transaction_base.cxx -o src/transaction_base.o $(CXXFLAGS)

src/util.o: src/util.cxx
	$(CXX) $(CPPFLAGS) -c src/util.cxx -o src/util.o $(CXXFLAGS)


