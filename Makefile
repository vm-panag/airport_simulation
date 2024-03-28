CC=g++
CFLAGS=-g
OBJECTS=main.o Application_constr.o Flight_constr.o Airport_constr.o

airport_sim:$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o airport_sim

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

Application_constr.o: Application_constr.cpp
	$(CC) $(CFLAGS) -c Application_constr.cpp -o Application_constr.o

Flight_constr.o: Flight_constr.cpp
	$(CC) $(CFLAGS) -c Flight_constr.cpp -o Flight_constr.o

Airport_constr.o: Airport_constr.cpp
	$(CC) $(CFLAGS) -c Airport_constr.cpp -o Airport_constr.o

.PHONY: clean
clean:
	rm airport_sim $(OBJECTS) 

