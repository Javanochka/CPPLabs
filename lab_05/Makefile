SRCS = main.c position.c clist.c
INCLUDES = -I include
OBJS = $(SRCS:.c=.o)

main: bin $(addprefix bin/, $(OBJS))
	gcc -std=c99 $(addprefix bin/, $(OBJS)) -o main

all: ms_cli
	

bin: 
	mkdir -p bin

bin/main.o: src/main.c include/*.h
	gcc -std=c99 -c -g src/main.c -o bin/main.o $(INCLUDES)

bin/position.o: src/position.c include/*.h
	gcc -std=c99 -c -g src/position.c -o bin/position.o $(INCLUDES)

bin/clist.o: src/clist.c include/*.h
	gcc -std=c99 -c -g src/clist.c -o bin/clist.o $(INCLUDES)

clean:
	rm -rf bin main

