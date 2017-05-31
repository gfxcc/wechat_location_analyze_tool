CC = clang++
CXXFLAGS += -std=c++11 -g -Wall
SRC_DIR = ./src

analyze : $(SRC_DIR)/analyze.cc $(SRC_DIR)/util.cc $(SRC_DIR)/process.cc \
					$(SRC_DIR)/review.cc $(SRC_DIR)/statistic.cc
	$(CC) $(CXXFLAGS) $^ -o $@

clean:
	rm -f analyze
