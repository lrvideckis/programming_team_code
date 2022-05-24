mkdir -p build
FILE="$1"
echo "
#include \"../../../template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ $(cat $(dirname "$0")/compile_flags.txt) build/temp.cpp && rm a.out build/temp.cpp
