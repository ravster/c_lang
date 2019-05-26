/*
  STDIN: Prices in decimal form
  STDOUT: 5-day moving average of prices
*/

/*
  gcc -o closing_prices closing_prices.c
  sed -n "2,71p" sp500_5_years.csv | cut -f 5 -d ',' | ./closing_prices 30 7
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
  TODO:
  - Parse into a struct so we can gather data on more fields
  Probably a good time to add CSV support?
  - Figure out why we can't check for errno after the strtod() call
*/
int
main(int argc, char **argv) {
  // Check that we got a number for how many lines to analyze from STDIN
  if (argc < 3) {
	printf("How many lines to parse from STDIN, and what is the period of the moving-average?\n");
	return EINVAL;
  }

  char line[60]; // Read in max 60 chars per line
  int max_data = atoi(argv[1]);
  double all_data[max_data];
  int moving_average_window = atoi(argv[2]);

  if (max_data == 0 || moving_average_window == 0) {
	printf("\nOne of the args couldn't be converted to an int.\n");
	return EINVAL;
  }

  for(int i = 0; i < max_data; i++) {
	double closing;
	if(fgets(line, 60, stdin) == NULL){
	  printf("\nBroke at %d", i);
	  break;
	}

	closing = strtod(line, NULL); // Parse input string to double
	/* Should check errno after above, but its always 0 even with obviously incorrect data.
	   Not sure why.  Continuing for now. */

	all_data[i] = closing;
  }

  for(int i = 0; i < max_data; i++) {
	if(i < moving_average_window){
	  printf("Array[%d] = %f\n", i, all_data[i]);
	} else {
	  double sum = 0;
	  for(int j = i - moving_average_window; j < i; j++) {
		sum += all_data[j];
	  }
	  sum = sum / moving_average_window;
	  printf("Array[%d] = %f, %d-moving-average = %f\n", i, all_data[i], moving_average_window, sum);
	}
  }
}
