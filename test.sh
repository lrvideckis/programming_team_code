for((i = 1; ; ++i)); do
    echo $i
    ./test.out $i > int
    diff -w <(./a.out < int) <(./brute.out < int) || break
done
