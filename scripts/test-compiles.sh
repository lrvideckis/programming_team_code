mkdir -p build
FILE="$1"
echo "
#include \"../template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ -Wall -Wextra -Wfatal-errors -Wconversion -std=c++2a build/temp.cpp && rm a.out build/temp.cpp
