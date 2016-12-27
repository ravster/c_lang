/*
   This file has been pretty much copied from https://www.postgresql.org/docs/9.1/static/libpq-example.html
   while I try to figure out how to do C programming with PostgreSQL.
*/

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

static void
exit_nicely(PGconn *conn) {
  PQfinish(conn);
  exit(1);
}

int
main(int argc, char **argv) {
  const char *conninfo;
  PGconn *conn;
  PGresult *res;
  int nFields;
  int i, j;

  if (argc > 1)
    conninfo = argv[1];
  else
    conninfo = "dbname = postgres";

  conn = PQconnectdb(conninfo);
  if (PQstatus(conn) != CONNECTION_OK){
    fprintf(stderr,
            "Connection to database failed: %s",
            PQerrorMessage(conn));

    exit_nicely(conn);
  }

  res = PQexec(conn, "BEGIN");
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));

    exit_nicely(conn);
  }

  res = PQexec(conn, "declare myportal cursor for select * from pg_database");
  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "DECLARE FOR command failed: %s", PQerrorMessage(conn));

    exit_nicely(conn);
  }

  res = PQexec(conn, "FETCH ALL IN myportal");
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "FETCH ALL command failed: %s", PQerrorMessage(conn));

    exit_nicely(conn);
  }

  nFields = PQnfields(res);
  for(i = 0; i < nFields; i++) {
    printf("%-15s", PQfname(res, i));
  }
  printf("\n\n");

  for (i = 0; i < PQntuples(res); i++) {
    for (j = 0; j < nFields; j++) {
      printf("%-15s", PQgetvalue(res, i, j));
    }
    printf("\n");
  }

  res = PQexec(conn, "CLOSE myportal");
  PQclear(res);

  PQfinish(conn);

  return 0;
}
