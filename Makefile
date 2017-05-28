analyze : analyze.cc util.cc
	g++ -std=c++11 -g -o analyze analyze.cc util.cc

clean:
	rm -f analyze
