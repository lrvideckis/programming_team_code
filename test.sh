for((i = 1; ; ++i)); do
    echo $i
    ./test.out $i > int
    diff --ignore-all-space <(./a.out < int) <(./brute.out < int) || break
done
