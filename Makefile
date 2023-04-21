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
	./$(EXE) 100

output: $(EXE)
	./$(EXE) 100 > output.txt
	python3 output.py output.txt

clean:
	rm -f $(OBJ)/*.o $(EXE) *.tar.gz *.txt
	
valgrind: $(EXE)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./$(EXE) 100