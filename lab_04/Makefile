SRCS = ms_cli.c mergesort.c str.c
INCLUDES = -I include
OBJS = $(SRCS:.c=.o)

pose_db: bin $(addprefix bin/, $(OBJS))
	gcc $(addprefix bin/, $(OBJS)) -o ms_cli

all: ms_cli
	

bin: 
	mkdir -p bin

bin/ms_cli.o: src/ms_cli.c include/*.h
	gcc -c -g src/ms_cli.c -o bin/ms_cli.o $(INCLUDES)

bin/mergesort.o: src/mergesort.c include/*.h
	gcc -c -g src/mergesort.c -o bin/mergesort.o $(INCLUDES)

bin/str.o: src/str.c include/*.h
	gcc -c -g src/str.c -o bin/str.o $(INCLUDES)

clean:
	rm -rf bin ms_cli

