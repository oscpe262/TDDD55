CC      = g++
CCFLAGS = -g
LDFLAGS =

lab1 : lex.o main.o lab1.o
	$(CC) -o lab1 $(CCFLAGS) $(LDFLAGS) lex.o main.o lab1.o

lex.o: lex.hh lex.cc
	$(CC) $(CFLAGS) -c lex.cc
lab1.o: lab1.hh lex.hh lab1.cc
	$(CC) $(CFLAGS) -c lab1.cc
main.o: lab1.hh lex.hh main.cc
	$(CC) $(CFLAGS) -c main.cc

clean:
	rm *.o lab1
