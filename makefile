HEAD=$(wildcard *.hpp)
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=vector.app
CPPFLAGS=-c -std=c++11 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ \
-Wstrict-null-sentinel -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion \
-Wsign-promo -Wzero-as-null-pointer-constant
LDFLAGS=
CC=clang++

all: $(SRC) $(EXEC)
	./$(EXEC)

valgrind: $(SRC) $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ): $(SRC) $(HEAD)
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper: clean
	rm $(EXEC)