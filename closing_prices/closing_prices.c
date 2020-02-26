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
#include <string.h>

typedef struct {
  double open, high, low, close, volume,
	moving_average, true_range;
} tick;

// Split string
// Return populated tick struct
tick parse_tick(char* line) {
  char* delim = ",";
  char* ptr = strtok(line, delim);
  ptr = strtok(NULL, delim);

  tick tick1;
  tick1.open = atof(ptr);
  ptr = strtok(NULL, delim);
  tick1.high = atof(ptr);
  ptr = strtok(NULL, delim);
  tick1.low = atof(ptr);
  ptr = strtok(NULL, delim);
  tick1.close = atof(ptr);

  return tick1;
}

/* This function calculates a moving average for a given period for a given GArray and
   saves it in the structs in the array.
   This operation is embarrassingly parallel, and a prime location to use something like
   OpenMP. */
void calculate_moving_average(int period, tick* array, int array_len) {
  for(int i = period; i < array_len; i++) {
	double sum = 0.0;
	for(int j = i - period; j < i; j++) {
	  sum += array[j].close;
	}

	array[i].moving_average = sum / period;
  }

  return;
}

double max3(double high, double low, double prev_close) {
  double max, temp;
  max = high - low;
  temp = high - prev_close;
  if (temp < 0) {
    temp = -temp;
  }
  if (temp > max) {
    max = temp;
  }
  temp = prev_close - low;
  if (temp < 0) {
    temp = -temp;
  }
  if (temp > max) {
    max = temp;
  }

  return max;
}

void calc_true_range(tick* data, int length) {
  for(int i = 1; i < length; i++) {
	tick* this = &data[i];
	tick previous = data[i - 1];

	this->true_range = max3(this->high, this->low, previous.close);
  }
}

/*
  TODO:
  - Figure out why we can't check for errno after the strtod() call
*/
int
main(int argc, char **argv) {
  char* a1 = argv[1];
  int a2 = atoi(a1);
  if (a2 == 0) {
    fprintf(stderr, "arg 1 on command line must be an int for the size of the array.\n");
    return 1;
  }
  FILE* fp = NULL;
  char* filepath = "sp500_5_years.csv";

  fp = fopen(filepath, "r");
  if (fp == NULL) {
	fprintf(stderr, "Cannot open file %s", filepath);
	return 1;
  }

  char* line = NULL;
  size_t len = 100;
  tick arr[a2];

  // Read line from file, create tick struct, append tick to array
  int i = 0;
  while (getline(&line, &len, fp) != -1) {
	tick tick1 = parse_tick(line);

	arr[i] = tick1;
	i++;
  }

  printf("size of array: %d\n", i);

  calculate_moving_average(5, arr, i);
  calc_true_range(arr, i);

  for(int i = 20; i < 30; i++) {
	tick this = arr[i];
	printf("idx %d; %f, %f, %f; true_range: %f\n", i, this.high, this.low, this.close, this.true_range);
  }
}
