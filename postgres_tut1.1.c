/*
  This file is inspired from one of the comments on https://www.postgresql.org/docs/9.1/static/libpq-example.html

  It will read a table passed in from the command-line and print out the column passed in from the command-line

  Compiling:
    gcc -o list_column -I/usr/include/postgresql/ postgres_tut1.1.c -lpq
    // This will create an executable which is dynamically linked to libpq.

  Usage:
    ./list_column schema-name table-name column-name
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
  if (argc < 4) {
    fprintf(stderr, "Too few arguments: %d\n", argc);
    exit(1);
  }

  PGconn *conn;
  PGresult *res;
  char *conninfo = malloc(50 * sizeof(char)),
    *select_query = malloc(100 * sizeof(char)),
    *db_name = argv[1],
    *table_name = argv[2],
    *column_name = argv[3];

  printf("dbname: %s\ntablename: %s\ncolumn_name: %s\n", db_name, table_name, column_name);

  sprintf(conninfo, "dbname = %s", db_name);

  conn = PQconnectdb(conninfo);
  if (PQstatus(conn) != CONNECTION_OK){
    fprintf(stderr,
            "Connection to database failed: %s",
            PQerrorMessage(conn));

    exit_nicely(conn);
  }

  sprintf(select_query, "SELECT %s FROM %s", column_name, table_name);

  res = PQexec(conn, select_query);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "BAD QUERY!!: %s", PQresultErrorMessage(res));
  }

  printf("Total number of entries: %d\n", PQntuples(res));

  for (int i = 0; i < PQntuples(res); i++) {
    printf("%s\n", PQgetvalue(res, i, 0));
  }

  PQclear(res);

  PQfinish(conn);

  return 0;
}
