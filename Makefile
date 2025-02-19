CC = gcc
TARGET = netmonn
SRC = netmonn.c format_bytes.c

all:
	$(CC) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
