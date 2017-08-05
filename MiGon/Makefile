migon: main.o stack.o maze.o
	gcc main.o stack.o maze.o -o migon

main.o: main.c main.h stack.h maze.h
	gcc -c main.c

stack.o: stack.c stack.h main.h
	gcc -c stack.c

maze.o: maze.c maze.h main.h
	gcc -c maze.c

clean:
	@echo "cleanning project"
	-rm migon *.o
	@echo "clean completed"

.PHONY: clean
