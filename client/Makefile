CC = g++
CC += -g
all: client.o Hub.o DirectoryList.o Directory.o Network.o
	$(CC) -g -o client client.o Hub.o DirectoryList.o Directory.o Network.o -lpthread
client.o: client.cpp
	$(CC) -c -o client.o client.cpp -lpthread
Network.o: Network.cpp
	$(CC) -c -o Network.o Network.cpp
Hub.o: Hub.cpp
	$(CC) -c -o Hub.o Hub.cpp -lpthread
DirectoryList.o: DirectoryList.cpp
	$(CC) -c -o DirectoryList.o DirectoryList.cpp
Directory.o: Directory.cpp
	$(CC) -c -o Directory.o Directory.cpp

#%.o : %.c
#	$(CC) -lm -c -o $@ $<
clean:
	rm *.o client
