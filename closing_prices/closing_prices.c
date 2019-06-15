// DOING :
// Read from file
// Populate struct
// Append to GArray

/*
  gcc -L/usr/lib/x86_64-linux-gnu -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -o closing_prices closing_prices.c -lglib-2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <glib.h>

typedef struct {
  double open, high, low, close, volume;
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

  /* int moving_average_window = 5; */

  /* for(int i = 0; i < max_data; i++) { */
  /* 	double closing; */
  /* 	if(fgets(line, 60, stdin) == NULL){ */
  /* 	  printf("\nBroke at %d", i); */
  /* 	  break; */
  /* 	} */

  /* 	closing = strtod(line, NULL); // Parse input string to double */
  /* 	/\* Should check errno after above, but its always 0 even with obviously incorrect data. */
  /* 	   Not sure why.  Continuing for now. *\/ */

  /* 	all_data[i] = closing; */
  /* } */

  /* for(int i = 0; i < max_data; i++) { */
  /* 	if(i < moving_average_window){ */
  /* 	  printf("Array[%d] = %f\n", i, all_data[i]); */
  /* 	} else { */
  /* 	  double sum = 0; */
  /* 	  for(int j = i - moving_average_window; j < i; j++) { */
  /* 		sum += all_data[j]; */
  /* 	  } */
  /* 	  sum = sum / moving_average_window; */
  /* 	  printf("Array[%d] = %f, %d-moving-average = %f\n", i, all_data[i], moving_average_window, sum); */
  /* 	} */
  /* } */
}
