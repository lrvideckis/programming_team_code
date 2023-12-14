# Don't type comments nor #include "..."
# Do type asserts

# usage:
#	chmod +x hash.sh
#	cat a.cpp | ./hash.sh
# or just copy this command:
#	cat a.cpp | tr -d '[:space:]' | md5sum
tr -d '[:space:]' | md5sum
