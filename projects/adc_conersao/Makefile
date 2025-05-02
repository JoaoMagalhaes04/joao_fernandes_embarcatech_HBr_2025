CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -IUnity/src

SRCS = test_temperature.c temperature.c Unity/src/unity.c
OBJS = $(SRCS:.c=.o)
TARGET = test_temperature

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)
