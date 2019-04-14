/*
This program outputs to STDOUT the number of characters that were put into STDIN.  It
should match the count from the "wc -c" program.
 */

/*
gcc count_chars.c
echo "12345" | ./a.out
*/

#include <stdio.h>
#include <unistd.h>

int count_chars() {
  char c;
  int count = 0;

  while(read(0, &c, 1) > 0) {
	count++;
  }

  return count;
}

int
main(int argc, char **argv) {
  int count;

  // Get count
  count = count_chars();

  // Print count
  printf("The number of characters is %d\n", count);

  return 0;
}
