#Makefile
#Compila sorting.cpp junto a los 4 algoritmos

CXX = g++
CXXFLAGS = -std=c++17 -O2
EXE = sorting
ALGOS = merge quick sort patience
INPUT_DIR = data/array_input
MEASURE_DIR = data/measurements
SRCS = sorting.cpp algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/sort.cpp algorithms/patiencesort.cpp

all: $(EXE)

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRCS)

run: $(EXE)
	mkdir -p $(MEASURE_DIR)
	for algo in $(ALGOS); do \
		rm -f $(MEASURE_DIR)/$$algo.txt; \
		for f in $(INPUT_DIR)/*.txt; do \
			echo "$$(basename $$f): $$(./$(EXE) $$f $$algo)" >> $(MEASURE_DIR)/$$algo.txt; \
		done; \
	done

clean:
	rm -f $(EXE)
	rm -rf $(MEASURE_DIR)

.PHONY: all run clean