CFLAGS=-Wall -Wextra -Werror

.PHONY: clean run

build: arbore.c
	gcc -g arbore.c sufix.h BFS.c task1.c task2.c task3.c task4.c $(CFLAGS) -o tema2

run: tema2
	./tema2

clean:
	rm -f tema2