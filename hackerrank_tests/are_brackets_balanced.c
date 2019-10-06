/*
  Started 0910
 */

#include <stdio.h>
#include <glib.h>

typedef char* string;

string is_balanced(string input) {
  GSList* list = NULL;
  char* c = input; // Use explicitly as a pointer

  while (c && *c) {
    switch(c[0]) {
    case '{':
      list = g_slist_prepend(list, (gpointer) '{');

      break;
    case '[':
      list = g_slist_prepend(list, (gpointer) '[');

      break;
    case '(':
      list = g_slist_prepend(list, (gpointer) '(');

      break;
    case ')':
      if (list == NULL) {
	return "NO";
      }
      if ('(' == (char) list->data) {
	list = g_slist_remove(list, (gpointer) '(');
      } else {
	return "NO";
      }

      break;
    case ']':
      if ('[' == (char) list->data) {
	list = g_slist_remove(list, (gpointer) '[');
      } else {
	return "NO";
      }

      break;
    case '}':
      if ('{' == (char) list->data) {
	list = g_slist_remove(list, (gpointer) '{');
      } else {
	return "NO";
      }

      break;
    }

    c++;
  }

  if (list == NULL) { // Empty list
    return "YES";
  } else {
    return "NO";
  }
}

int main(int argc, char** argv) {
  string output = is_balanced(argv[1]);

  printf("%s\n", output);
}
