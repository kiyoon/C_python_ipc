CC=gcc
OBJ=main_sender.o main_receiver.o
TARGET=sender receiver


%.o: %.c
	$(CC) -c -o $@ $<

all: $(OBJ)
	$(CC) -o sender main_sender.o
	$(CC) -o receiver main_receiver.o

clean:
	rm -f $(OBJ) $(TARGET)
