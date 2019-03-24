all: test pdf

.PHONY: clean pdf

test: 

clean:
	rm main.pdf main.dvi main.aux main.log main.lol main.toc *.so .lqc 2>/dev/null || true

quickcheck: clibs
	lqc -c quickcheck

busted: clibs
	busted -p ".*" tests

pdf: 25_pg-reference.pdf

# TODO add cpp files as dep
25_pg-reference.pdf: 25_pg-reference.tex */*.cpp math/*
	pdflatex -halt-on-error 25_pg-reference.tex

clibs: libhungarian.so libfenwick.so libprimes.so libgraph.so libfourier.so libkmp.so

libfourier.so: fourier/fft.cpp fourier/fft-interface.cpp
	g++ -shared -fPIC --std=c++11 -o $@ $^

libfenwick.so: fenwick/fenwick.c
	gcc -shared -fPIC -o libfenwick.so fenwick/fenwick.c

libprimes.so: primes/primes-interface.cpp primes/primes.cpp
	g++ -shared -fPIC --std=c++11 -o libprimes.so primes/primes.cpp primes/primes-interface.cpp

libgraph.so: graph/graph-interface.cpp graph/djikstra.cpp graph/graph.hpp
	g++ -shared -fPIC --std=c++11 -o libgraph.so graph/graph-interface.cpp graph/djikstra.cpp

libkmp.so: kmp/kmp-interface.cpp kmp/kmp.hpp
	g++ -shared -fPIC --std=c++11 -o libkmp.so kmp/kmp-interface.cpp

libhungarian.so: hungarian/hungarian-interface.cpp hungarian/hungarian.cpp
	g++ -shared -fPIC --std=c++11 -o libhungarian.so hungarian/hungarian-interface.cpp hungarian/hungarian.cpp

