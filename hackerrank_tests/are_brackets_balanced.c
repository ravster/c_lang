/*
  Started 0910
 */

#include <stdio.h>
#include <glib.h>

typedef char* string;

// Return BOOL
int is_empty(GSList* const list) {
  return (list == NULL);
}

// Return BOOL
int check_head(GSList* const list, char c) {
  if (is_empty(list)) {
    return 0;
  }

  if (c == (char) list->data) {
    return 1;
  }

  return 0;
}

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
      if (check_head(list, '(')) {
	list = g_slist_remove(list, (gpointer) '(');
      } else {
	return "NO";
      }

      break;
    case ']':
      if (check_head(list, '[')) {
	list = g_slist_remove(list, (gpointer) '[');
      } else {
	return "NO";
      }

      break;
    case '}':
      if (check_head(list, '{')) {
	list = g_slist_remove(list, (gpointer) '{');
      } else {
	return "NO";
      }

      break;
    }

    c++;
  }

  if (is_empty(list)) {
    return "YES";
  } else {
    return "NO";
  }
}

int main(int argc, char** argv) {
  string output = is_balanced(argv[1]);

  printf("%s\n", output);
}
