for((i = 1; ; ++i)); do
    echo $i
    ./test.out $i > in
    diff --ignore-all-space <(./a.out < in) <(./brute.out < in) || break
done
