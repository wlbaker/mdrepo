#!/bin/bash

# script to create dicesdb if it doesn't already exist

versionstring=`grep "schema version" MP70db.sql`
versionstringarray=($versionstring)
versionstr="${versionstringarray[3]}"
version=`echo $versionstr | tr -d '\r'`

dbname=mp70db

# make sure postgres is running before using database commands
wait_count=0
postgres_status="ERROR"
while [  $wait_count -lt 30 ]
do
  for i in `pgrep -f postgres` ; do
    postgres_status="OK"
  done
  if [ $postgres_status = "OK" ] ; then
    break;
  fi
  wait_count=$(( $wait_count + 1 ))
  sleep 1
done 
if [ $postgres_status = "ERROR" ] ; then
  exit 1
fi
#echo "postgres is running!"
 
databasetest="select count(1) from pg_catalog.pg_database where datname = '$dbname'"
databasetestcmd="psql -U postgres -t -c \"$databasetest\"" 
database_exists=`eval $databasetestcmd` || exit 1

if [ $database_exists -eq 0 ] ; then
  echo "no MP70db database"
  psql -U postgres < MP70db.sql > /dev/null 2>&1 || exit 1
  insertversion="INSERT into mp70db_version (version) values ('$version');"
  insertcmd="psql -U postgres -t -c \"$insertversion\" mp70db"
  insertresult=`eval $insertcmd` > /dev/null 2>&1 || exit 1
else
  versiontest="select count(relname) from pg_class where relname='mp70db_version'"
  versiontestcmd="psql -U postgres -t -c \"$versiontest\" mp70db"
  versiontable_exists=`eval $versiontestcmd` || exit 1
  if [ $versiontable_exists -eq 0 ] ; then
    createversiontable="CREATE TABLE mp70db_version (id SERIAL, version character varying(32));"
    createversioncmd="psql -U postgres -t -c \"$createversiontable\" mp70db"
    createresult=`eval $createversioncmd` || exit 1
    altertable="ALTER TABLE mp70db_version ADD CONSTRAINT pk_mp70db_version PRIMARY KEY (id);"
    altercmd="psql -U postgres -t -c \"$altertable\" mp70db"
    alterresult=`eval $altercmd` || exit 1
    insertversion="INSERT into mp70db_version (version) values ('$version');"
    insertcmd="psql -U postgres -t -c \"$insertversion\" mp70db"
    insertresult=`eval $insertcmd` > /dev/null 2>&1 || exit 1
  else
    selectversion="select version from mp70db_version;"
    selectversioncmd="psql -U postgres -t -c \"$selectversion\" mp70db"
    dbversion=`eval $selectversioncmd` > /dev/null 2>&1 || exit 1
    dbversion_clean="$(echo -e "${dbversion}" | tr -d '[[:space:]]')"
    if [[ "${dbversion_clean}" != "${version}" ]] ; then
      echo "new schema - replace old one"
      psql -U postgres < MP70db.sql > /dev/null 2>&1 || exit 1
      insertversion="INSERT into mp70db_version (version) values ('$version');"
      insertcmd="psql -U postgres -t -c \"$insertversion\" mp70db"
      insertresult=`eval $insertcmd` > /dev/null 2>&1 || exit 1
    fi
  fi
fi

echo "OK"

exit 0
