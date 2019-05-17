/*
gcc -o subtract subtract.c
./subtract 4 1
*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
  int count = 3;
  char *list[] = {"5", "5", "6"};
  int final = atoi(list[0]);

  for(int i = 1; i < count; i++) {
	printf("i = %d\n", i);
	final = final - atoi(list[i]);
  }

  printf("Final: %d\n", final);

  return 0;
}
