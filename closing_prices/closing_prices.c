/*
STDIN: Closing prices in decimal form
STDOUT: 10-day moving average of closing price
*/

/*
gcc -o closing_prices closing_prices.c
sed -n "2,300p" sp500_5_years.csv | cut -f 5 -d ',' | ./closing_prices
*/

#include <stdio.h>

int
main(int argc, char **argv) {
  printf("z1\n");
  /* Start small.  Read from STDIN, output to STDOUT */

  // Read in max 60 chars
  char line[60];
  printf("z2\n");

  while(fgets(line, 60, stdin) != NULL) {
	printf("Output: %s\n", line);
  }
}
