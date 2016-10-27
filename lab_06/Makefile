SRCS = main.c phonebook.c
INCLUDES = -I include
OBJS = $(SRCS:.c=.o)

main: bin $(addprefix bin/, $(OBJS))
	gcc -std=c99 $(addprefix bin/, $(OBJS)) -o main -lexpat

all: ms_cli
	

bin: 
	mkdir -p bin

bin/main.o: src/main.c include/*.h
	gcc -std=c99 -c -g src/main.c -o bin/main.o $(INCLUDES)

bin/phonebook.o: src/phonebook.c include/*.h
	gcc -std=c99 -c -g src/phonebook.c -o bin/phonebook.o $(INCLUDES)

clean:
	rm -rf bin main
