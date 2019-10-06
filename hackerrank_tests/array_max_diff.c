/*
  This program creates an array of ints from the command-line arguments, and then finds the max difference of elements if a later element is greater than an earlier one.

E.g. 1,2,6,4
find
2-1
6-2
6-1
4-2
4-1

and then max of all above results
 */

/*
  started 1115
  ended 1217 -> 1h
*/

#include <stdio.h>
#include <stdlib.h>

int m2(int const list[], int const idx) {
  int max = -1;
  int mark = list[idx];
  for (int i = 0; i < idx; i++) {
    if (list[i] < mark) {
      int diff = mark - list[i];

      if (diff > max) {
	max = diff;
      }
    }
  }

  return max;
}

int m1(int const list[], int const n) {
  int max = -1;

  for (int i = 1; i < n; i++) {
    int diff = m2(list, i);

    if (diff > max) {
      max = diff;
    }
  }

  return max;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Not enough arguments.\nTry ./foo 1 2 6 4\n");
    return 1;
  }

  int arg_count = argc -1;

  int array[arg_count];
  for (int i = 0; i < arg_count; i++) {
    array[i] = atoi(argv[i+1]);
  }

  int max_diff = m1(array, arg_count);

  printf("%d\n", max_diff);
}
