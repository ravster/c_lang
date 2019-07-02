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
	moving_average, true_range;
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

double max3(double high, double low, double prev_close) {
  double a, b, c, d;
  a = ABS(high - low);
  b = ABS(high - prev_close);
  c = ABS(prev_close - low);

  d = MAX(a, b);				/* Shenanigans because Glib and C do not allow multivariate MAX */
  return MAX(c, d);
}

void calc_true_range(GArray* data) {
  for(int i = 1; i < data->len; i++) {
	tick* this = &g_array_index(data, tick, i);
	tick previous = g_array_index(data, tick, i - 1);

	this->true_range = max3(this->high, this->low, previous.close);
  }
}

/*
  TODO:
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
  calc_true_range(arr);

  for(int i = 20; i < 30; i++) {
	tick this = g_array_index(arr, tick, i);
	printf("idx %d; %f, %f, %f; true_range: %f\n", i, this.high, this.low, this.close, this.true_range);
  }
}
