#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"
#include "../../../library/math/fibonacci.hpp"

#include "../../../kactl/content/data-structures/Matrix.h"
#include "../../../hackpack-cpp/content/number-theory/ModInt.h"

void check(long long n) {
    using mat_2_by_2 = Matrix<mi, 2>;
    mat_2_by_2 mat;
    mat.d = {{{{1, 1}}, {{1, 0}}}};
    vector<mi> vec = {1, 0};
    long long res = fib(n).first;
    assert(res == int(((mat ^ n) * vec)[1]));
}

int main() {
    //n=0 -> val=0
    //n=1 -> val=1
    //n=2 -> val=1
    //n=3 -> val=2
    //n=4 -> val=3
    //n=5 -> val=5
    assert(fib(0).first == 0);
    assert(fib(1).first == 1);
    assert(fib(2).first == 1);
    assert(fib(3).first == 2);
    assert(fib(4).first == 3);
    assert(fib(5).first == 5);
    for (int i = 0; i < 500; i++)
        check(i);
    for (int tests = 1000; tests--;)
        check(get_rand<long long>(0, LLONG_MAX));
    cout << "Hello World\n";
    return 0;
}
