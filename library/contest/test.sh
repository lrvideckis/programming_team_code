#see: https://github.com/Errichto/youtube/blob/master/testing/s.sh
#usage:
#	chmod +x test.sh
#	./test.sh

g++ -std=c++17 a.cpp -o a.out
g++ -std=c++17 b.cpp -o b.out
g++ -std=c++17 gen_test.cpp -o gen_test.out

while :; do
	echo "hi"
	./gen_test.out >in
	diff -w <(./a.out <in) <(./b.out <in) || break
done
