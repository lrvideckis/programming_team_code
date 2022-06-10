# Hashes a file, ignoring all whitespace, comments, and includes. Use for
# verifying that code was correctly typed.

# usage:
#	chmod +x hash.sh
#	cat <file> | ./hash.sh
# or just copy this command:
#	cat <file> | sed -r '/^#(include|pragma)/d' | cpp -fpreprocessed -P | tr -d '[:space:]' | md5sum | cut -c-6
sed -r '/^#(include|pragma)/d' | cpp -fpreprocessed -P | tr -d '[:space:]' | md5sum | cut -c-6
