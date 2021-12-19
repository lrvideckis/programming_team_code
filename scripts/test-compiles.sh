mkdir -p build
FILE="$1"
echo "
#include \"../template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ -Wall -Wextra -pedantic -Wno-unused-result -Wfatal-errors -DLOCAL -std=c++2a -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector build/temp.cpp && rm a.out build/temp.cpp
