# Ñî×¿Óî 1652292 ¼Æ¿Æ2°à
CC = gcc #Which compiler to use
CFLAGS = #Which flags to use -ggdb -Wall etc...
LDFLAGS = #Which libraries to use -lm -lefence etc...
OBJFILES1 = test1-1.o #Which object files are part of the final program
OBJFILES2 = test1-2.o
TARGET1 = test1-1 #What to name the final program
TARGET2 = test1-2

all: $(OBJFILES1) $(OBJFILES2)
	$(CC) -o $(TARGET1) $(OBJFILES1) $(CFLAGS) $(LDFLAGS)
	$(CC) -o $(TARGET2) $(OBJFILES2) $(CFLAGS) $(LDFLAGS)

$(TARGET1): $(OBJFILES1)
	$(CC) -o $(TARGET1) $(OBJFILES1) $(CFLAGS) $(LDFLAGS)

$(TARGET2): $(OBJFILES2)
	$(CC) -o $(TARGET2) $(OBJFILES2) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJFILES1) $(OBJFILES2) $(TARGET1) $(TARGET2)
