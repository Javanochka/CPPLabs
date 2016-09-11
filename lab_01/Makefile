SRCS = main.c io.c algorithm.c util.c
INCLUDES = -I./include
OBJS = $(SRCS:.c=.o)

lab1: bin $(addprefix ./bin/, $(OBJS))
	gcc $(addprefix ./bin/, $(OBJS)) -o lab1

all: lab1
	

bin: 
	mkdir -p bin

./bin/main.o: ./src/main.c ./include/*.h bin
	echo $<
	gcc -c ./src/main.c -o ./bin/main.o $(INCLUDES)

./bin/io.o: ./src/io.c ./include/*.h bin
	echo $<
	gcc -c ./src/io.c -o ./bin/io.o $(INCLUDES)

./bin/algorithm.o: ./src/algorithm.c ./include/*.h bin
	echo $<
	gcc -c ./src/algorithm.c -o ./bin/algorithm.o $(INCLUDES)

./bin/util.o: ./src/util.c ./include/*.h bin
	echo $<
	gcc -c ./src/util.c -o ./bin/util.o $(INCLUDES)

clean:
	rm -rf ./bin lab1

