#Makefile
#Compila matrix_multiplication.cpp junto a los algoritmos

CXX = g++
CXXFLAGS = -std=c++17 -O2
EXE = matrix
ALGOS = naive strassen
INPUT_DIR = data/matrix_input
MEASURE_DIR = data/measurements
SRCS = matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp

all: $(EXE)

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRCS)

run: $(EXE)
	mkdir -p $(MEASURE_DIR)
	for algo in $(ALGOS); do \
		rm -f $(MEASURE_DIR)/$$algo.txt; \
		for f1 in $(INPUT_DIR)/*_1.txt; do \
			f2=$${f1%_1.txt}_2.txt; \
			echo "$$(basename $$f1): $$(./$(EXE) $$f1 $$f2 $$algo)" >> $(MEASURE_DIR)/$$algo.txt; \
		done; \
	done

clean:
	rm -f $(EXE)
	rm -rf $(MEASURE_DIR)

.PHONY: all run clean