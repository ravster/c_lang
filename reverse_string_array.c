/*
gcc -o reverse_string_array reverse_string_array.c
./reverse_string_array
*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
  char *list[] = {"foo", "bar", "baz", "quux"};
  int count = sizeof(list)/sizeof(list[0]);
  char *list2[count];

  for(int i = 0; i < count; i++) {
	printf("%d - %s\n", i, list[i]);
	list2[count - 1 - i] = list[i];
  }

  for(int i = 0; i < count; i++) {
	printf("%d - %s\n", i, list2[i]);
  }
}
