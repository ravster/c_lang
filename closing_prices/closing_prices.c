/*
  STDIN: Prices in decimal form
  STDOUT: 5-day moving average of prices
*/

/*
TODO:
- Set profit = 0
- Find min(100) ticks
- If low < min(100), then buy
- if low < (buy-price - 5%_of_buy_price), then sell and add to profit.
- If (high > max(50)) && (currently have bought), then sell & add to profit.
*/

/*
  time gcc -o closing_prices closing_prices.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct {
  double open, high, low, close, volume,
    moving_average, true_range, min_100, max_50;
} tick;

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

/* This function calculates a moving average for a given period for a given array and
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

double min(const double a, const double b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

void calc_min_100(tick* arr, int arr_len) {
  for(int i = 99; i < arr_len; i++) {
  double minimum = 20000;
    for (int j = 99; j >= 0; j--) {
      /* We might be able to optimize the inner loop by comparing the current min to the
	 next oldest tick.low.  If oldest tick.low > min, then we need to only compare
	 newest tick.low to min.  This will remove the need for so many reads. */
      minimum = min(minimum, arr[i-j].low);
    }
    arr[i].min_100 = minimum;
  }
}

double max(const double a, const double b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

void calc_max_50(tick* arr, const int arr_len) {
  for(int i = 49; i < arr_len; i++) {
    double maximum = 0;
    for (int j = 49; j >= 0; j--) {
      /* We can optimize this inner loop the same way we do for calc_min_100 */
      maximum = max(maximum, arr[i-j].high);
    }
    arr[i].max_50 = maximum;
  }
}

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
  int arr_len = 0;
  while (getline(&line, &len, fp) != -1) {
	tick tick1 = parse_tick(line);

	arr[arr_len] = tick1;
	arr_len++;
  }

  printf("size of array: %d\n", arr_len);

  calculate_moving_average(5, arr, arr_len);
  calc_true_range(arr, arr_len);
  calc_min_100(arr, arr_len);
  calc_max_50(arr, arr_len);

  for(int i = 100; i < 120; i++) {
	tick this = arr[i];
	printf("idx %d; %f, %f, %f; true_range: %f, min100: %f, max50: %f\n", i, this.high, this.low, this.close, this.true_range, this.min_100, this.max_50);
  }
}
