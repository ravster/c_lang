/*
  STDIN: Prices in decimal form
  STDOUT: 5-day moving average of prices
*/

/*
  gcc -o closing_prices closing_prices.c
  sed -n "2,21p" sp500_5_years.csv | cut -f 5 -d ',' | ./closing_prices
*/

#include <stdio.h>
#include <stdlib.h>

/*
  TODO:
  - Parse into any number of lines
  Probably easiest to push onto a linked-list during parsing and then
  put it all into an array for faster lookup when doing calculations.
  - Parse into a struct so we can gather data on more fields
  Probably a good time to add CSV support?
  - Figure out why we can't check for errno after the strtod() call
*/
int
main(int argc, char **argv) {
  char line[60]; // Read in max 60 chars per line
  int max_data = 20; // Read only 20 lines
  double all_data[max_data];
  int moving_average_window = 5;

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
