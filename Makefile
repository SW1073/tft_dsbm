CC = g++
CFLAGS = -pthread
RM = rm
LIB = -lpigpio -lrt

all: test.cpp TFT.cpp SPI.cpp Command.cpp
	$(CC) $(CFLAGS) -o testCpp test.cpp TFT.cpp SPI.cpp Command.cpp $(LIB)

clean:
	$(RM) testCpp *.o