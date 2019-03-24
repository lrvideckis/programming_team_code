# Random numbers and permutations
# List of N random integers from interval [a,b]:
print( [ randint(a, b) for i in range(N) ] )

# List of N random real numbers from interval [a,b]:
print( [ uniform(a, b) for i in range(N) ] )

# Random permutation of numbers 1 to N:
seq = list(range(1, N+1))
shuffle(seq)
print(seq)

# Random matrices
# Matrix of size NxN with random integers from interval [a,b]:
for r in range(N):
    print( [ randint(a, b) for c in range(N) ] )

# With zeros on diagonal:
for r in range(N):
    print( [ randint(a, b) if r != c else 0 for c in range(N) ] )

# Symmetric matrix:
matrix = [ [0] * N for r in range(N) ]
for r in range(N):
    for c in range(r+1):
        matrix[r][c] = matrix[c][r] = randint(a, b)
print(matrix)

# If you want to output matrix with spaces between the numbers:
for row in matrix:
    print( ' '.join( map(str, row) ) )

# Random tree on N vertices:
# Output is the list of edges. Vertices are numbered from 0 - (N-1).
print( [ (randint(0, i), i+1) for i in range(N-1) ] )

# As Michal Forišek pointed out, the above code will generate rather shallow trees, with expected depth only O(log(N)).
# To generate the deep trees use:
alpha = 3  # affects the depth of the tree. Smaller value generates deeper trees.
# If alpha == 0, then the code will generate a path, i.e. the deepest possible tree.
print( [ (randint(max(0, i-alpha), i), i+1) for i in range(N-1) ] )

# Random graph on N vertices (may be unconnected):
# Output is the list of edges. Vertices are numbered from 0 - (N-1).
print( [ (i,j) for i in range(N) for j in range(i) if randint(0,1) ] )

# Random connected graph on N vertices:
# Simply union the edges of random tree and random graph:
print(set((randint(0, i), i+1) for i in range(N-1)) | set((i,j) for i in range(N) for j in range(i) if randint(0,1)))

# Random string of length N:
# Letters of your choice:
print( ''.join( choice('ABCabc123') for i in range(N) ) )

# Upper-case / lower-case letters:
from string import *
print( ''.join( choice(ascii_uppercase) for i in range(N) ) )  # upper-case
print( ''.join( choice(ascii_lowercase) for i in range(N) ) )  # lower-case

# matching a regex
import re
letters_re = re.compile(r'[A-Za-z0-9]')  # regex of letters we are interested in
print( ''.join(chr(c) for c in range(256) if letters_re.match(chr(c))) )
