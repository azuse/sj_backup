# Ñî×¿Óî 1652292 ¼Æ¿Æ2°à
CC = gcc #Which compiler to use
CFLAGS = #Which flags to use -ggdb -Wall etc...
LDFLAGS = #Which libraries to use -lm -lefence etc...
OBJFILES1 = test2.o #Which object files are part of the final program
TARGET1 = test2 #What to name the final program

all: $(OBJFILES1)
	$(CC) -o $(TARGET1) $(OBJFILES1) $(CFLAGS) $(LDFLAGS)

$(TARGET1): $(OBJFILES1)
	$(CC) -o $(TARGET1) $(OBJFILES1) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJFILES1) $(TARGET1)
