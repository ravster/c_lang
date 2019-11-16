/*
gcc check_squares.c -o check_squares && ./check_squares
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool comp(const int *a, const int *b, size_t n)
{
  int c[n];
  for(int i = 0; i<n; i++){
    c[i] = b[i];
  }

  for(int i = 0; i < n; i++) {
    int el = a[i];
    int squared = el * el;
    int found = 0;

    for(int j = 0; j < n; j++) {
      if(c[j] == squared) {
        c[j] = -1;
        found = 1;
        break;
      }
    }

    if (found == 0) {
      return false;
    }
  }

  return true;
}

int main(){
  int a[8] = {121, 144, 19, 161, 19, 144, 19, 11};
  int b[8] = {14641, 20736, 361, 25921, 361, 20736, 362, 121};

  comp(a, b, 8);
}
