gcc array_max_diff.c \
    -o array_max_diff

echo "Testing"

[ -1 -eq $(./array_max_diff 4 3) ] && echo '1'
[ 16 -eq $(./array_max_diff 4 20) ] && echo '2'
[ 5 -eq $(./array_max_diff 1 2 6 4) ] && echo '3'
[ 246 -eq $(./array_max_diff 6 7 10 256 3) ] && echo '4'

./array_max_diff >> /dev/null
[ $? -eq 1 ] && echo '5'

printf "Testing complete\n\n\n"

./array_max_diff $@
