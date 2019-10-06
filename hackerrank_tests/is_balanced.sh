gcc are_brackets_balanced.c \
    -Wall \
    -o are_brackets_balanced \
    `pkg-config --cflags --libs glib-2.0`

# E.g. ./are_brackets_balanced '((())'
# Should result in "NO" as output
./are_brackets_balanced $1
