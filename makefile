#
# Antoine Carpentier
# 000324440
# BA2 informatique ULB 2013-2014
# Langages de programmation 2 - INFO-F-202
# Project C++

HEAD=$(wildcard *.hpp)
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=vector.app
CPPFLAGS=-c -g -std=c++11 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ \
-Wsign-promo -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion \
-Wstrict-null-sentinel -Wnoexcept -Wzero-as-null-pointer-constant
LDFLAGS=
CC=g++

all: $(SRC) $(EXEC)
	./$(EXEC)

valgrind: $(SRC) $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $< -o $@

$(OBJ): $(SRC) $(HEAD)
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper: clean
	rm $(EXEC)