mkdir -p build
FILE="$1"
echo "
#include \"../template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
# Catching silly mistakes with GCC: https://codeforces.com/blog/entry/15547
g++ -Wall -Wextra -O2 -Wfatal-errors -std=c++2a -pedantic -Wno-unused-result -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align build/temp.cpp && rm a.out build/temp.cpp
