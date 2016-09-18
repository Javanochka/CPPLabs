SRCS = main.c str.c test_str.c
INCLUDES = -I include
OBJS = $(SRCS:.c=.o)

lab2: bin $(addprefix bin/, $(OBJS))
	gcc $(addprefix bin/, $(OBJS)) -o lab2

all: lab2
	

bin: 
	mkdir -p bin

bin/main.o: src/main.c include/*.h
	gcc -c src/main.c -o bin/main.o $(INCLUDES)

bin/str.o: src/str.c include/*.h
	gcc -c src/str.c -o bin/str.o $(INCLUDES)

bin/test_str.o: src/test_str.c include/*.h
	gcc -c src/test_str.c -o bin/test_str.o $(INCLUDES)

clean:
	rm -rf bin lab2

