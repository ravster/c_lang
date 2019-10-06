gcc are_brackets_balanced.c \
    -Wall \
    -o are_brackets_balanced \
    `pkg-config --cflags --libs glib-2.0`

./are_brackets_balanced
