/*
  STDIN: Prices in decimal form
  STDOUT: 5-day moving average of prices
*/

// TODO:
// Calc moving average in parallel

/*
  time gcc -L/usr/lib/x86_64-linux-gnu -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -o closing_prices closing_prices.c -lglib-2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <glib.h>

typedef struct {
  double open, high, low, close, volume,
	moving_average;
} tick;

// Split string
// Return populated tick struct
tick parse_tick(char* line) {
  char* delim = ",";
  gchar** strings = g_strsplit(line, delim, 0);

  tick tick1;
  tick1.open = g_strtod(strings[1], NULL);
  tick1.high = g_strtod(strings[2], NULL);
  tick1.low = g_strtod(strings[3], NULL);
  tick1.close = g_strtod(strings[4], NULL);

  return tick1;
}

/* This function calculates a moving average for a given period for a given GArray and
   saves it in the structs in the array.
   This operation is embarrassingly parallel, and a prime location to use something like
   OpenMP. */
void calculate_moving_average(int period, GArray* array) {
  for(int i = period; i < array->len; i++) {
	double sum = 0.0;
	for(int j = i - period; j < i; j++) {
	  sum += g_array_index(array, tick, j).close;
	}

	g_array_index(array, tick, i).moving_average = sum / period;
  }

  return;
}

/*
  TODO:
  - Parse into a struct so we can gather data on more fields
  Probably a good time to add CSV support?
  - Figure out why we can't check for errno after the strtod() call
*/
int
main(int argc, char **argv) {
  FILE* fp = NULL;
  char* filepath = "sp500_5_years.csv";

  fp = fopen(filepath, "r");
  if (fp == NULL) {
	fprintf(stderr, "Cannot open file %s", filepath);
	return 1;
  }

  char* line = NULL;
  size_t len = 100;
  GArray* arr = g_array_new(FALSE, FALSE, sizeof(tick));

  // Read line from file, create tick struct, append tick to array
  while (getline(&line, &len, fp) != -1) {
	tick tick1 = parse_tick(line);

	g_array_append_val(arr, tick1);
  }

  printf("size of array: %d\n", arr->len);

  calculate_moving_average(5, arr);

  for(int i = 20; i < 30; i++) {
	printf("idx %d - moving-average %f\n", i, g_array_index(arr, tick, i).moving_average);
  }
}
