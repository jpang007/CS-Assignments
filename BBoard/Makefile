
#makefile

#variables
G = g++

FILES= BBoard.o Message.o Reply.o User.o Topic.o

all: main.cpp $(FILES) 
	$(G) main.cpp $(FILES) 
	
bboard: BBoard.cpp BBoard.h
	$(G) -c BBoard.cpp -o BBoard.o

message: Message.cpp Message.h
	$(G) -c Message.cpp -o Message.o

reply: Reply.cpp Reply.h
	$(G) -c Reply.cpp -o Reply.o
    
topic: Topic.cpp Topic.h
	$(G) -c Topic.cpp -o Topic.o
    
user: User.cpp User.h
	$(G) -c User.cpp -o User.o

clean:
	rm -rf *~ *.o a.out
