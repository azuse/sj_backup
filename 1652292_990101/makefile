# ��׿�� 1652292 �ƿ�2��
CC = g++ #Which compiler to use
CFLAGS = -static -I/usr/include/mysql #Which flags to use -ggdb -Wall etc...
LDFLAGS = -L/usr/lib64/mysql ./libmysqlclient.a ./libz.a -lpthread -lm -ldl #Which libraries to use -lm -lefence etc...
CFILES = mysql_demo.cpp
OBJFILES = mysql_demo.o #Which object files are part of the final program
TARGET = mysql_demo #What to name the final program

$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES) $(CFLAGS) $(LDFLAGS)

$(OBJFILES): $(CFILES)
	$(CC) -c $(CFILES) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJFILES)
