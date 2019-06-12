/*
gcc -L/usr/lib/x86_64-linux-gnu -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -o reverse_array reverse_array.c -lglib-2.0
./reverse_array
*/

#include <stdio.h>
#include <glib.h>

int
main(int argc, char **argv) {
  GArray* arr = g_array_new(FALSE, FALSE, sizeof(int));
  for(int i = 10; i <= 40; i += 10) {
	g_array_append_val(arr, i);
  }

  int length = arr->len;

  for(int i = 0; i < length; i++) {
	printf("- %d\n", g_array_index(arr, int, length-i-1));
  }
}
