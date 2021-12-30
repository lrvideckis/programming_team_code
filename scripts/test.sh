for((i = 1; ; ++i)); do
    echo $i
    ./test.out > in
    diff --ignore-all-space <(./a.out < in) <(./brute.out < in) || break
done
