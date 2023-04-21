# NAME: Emma Topolovec
# GITHUB: EmmaTopolovec

# The name of the executable
EXE = convex-hull

REPODIR = ../ConvexHullVisualizer

FLAGS = -Wall -Wextra -pedantic -g -O
CC = g++
BIN = bin
OBJ = obj

# Store executables in a subdirectory
all: $(EXE)

$(EXE): Main.cpp Points.cpp
	$(CC) $(FLAGS) Main.cpp -o $@

test: $(EXE)
	./$(EXE) 100 0

10: $(EXE)
	./$(EXE) 10 1 > output.txt
	python3 output.py output.txt

50: $(EXE)
	./$(EXE) 50 1 > output.txt
	python3 output.py output.txt

100: $(EXE)
	./$(EXE) 100 1 > output.txt
	python3 output.py output.txt

1000: $(EXE)
	./$(EXE) 1000 1 > output.txt
	python3 output.py output.txt

clean:
	rm -f $(OBJ)/*.o $(EXE) *.tar.gz *.txt
	
valgrind: $(EXE)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./$(EXE) 100 0