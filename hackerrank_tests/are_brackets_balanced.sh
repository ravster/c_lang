set -e

gcc are_brackets_balanced.c \
    -Wall \
    -o are_brackets_balanced \
    `pkg-config --cflags --libs glib-2.0`

# Tests
echo "Testing"

test "YES" = $(./are_brackets_balanced '((()))') && \
    echo "1 test"

test "YES" = $(./are_brackets_balanced '') && \
    echo "2 test"

test "NO" = $(./are_brackets_balanced '((()') && \
    echo "3 test"

test "NO" = $(./are_brackets_balanced ')') && \
    echo "4 test"

test "NO" = $(./are_brackets_balanced '[{]}') && \
    echo "5 test"

# E.g. ./are_brackets_balanced '((())'
# Should result in "NO" as output
./are_brackets_balanced $1
