SRCS = main.c clist.c
INCLUDES = -I include
OBJS = $(SRCS:.c=.o)

pose_db: bin $(addprefix bin/, $(OBJS))
	gcc $(addprefix bin/, $(OBJS)) -o pose_db

all: pose_db
	

bin: 
	mkdir -p bin

bin/main.o: src/main.c include/*.h
	gcc -c src/main.c -o bin/main.o $(INCLUDES)

bin/clist.o: src/clist.c include/*.h
	gcc -c src/clist.c -o bin/clist.o $(INCLUDES)

clean:
	rm -rf bin pose_db

