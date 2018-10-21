all : mysql_demo

MYLIBDIR = "/usr/lib/x86_64-redhat-linux6E/lib64/"
MYLIBDIR2 = "/usr/lib/gcc/x86_64-redhat-linux/4.8.2/"
MYLIBDIR3 = "/usr/lib64/"

mysql_demo : mysql_demo.cpp
	g++ -static -nostartfiles -nostdlib `mysql_config --cflags` -o $@ $(MYLIBDIR3)crt1.o $(MYLIBDIR3)crti.o $(MYLIBDIR2)crtbeginT.o $^ ./libmysqlclient.a ./libstdc++.a $(MYLIBDIR)libpthread.a $(MYLIBDIR)libdl.a $(MYLIBDIR)librt.a $(MYLIBDIR)libm.a ./libz.a $(MYLIBDIR)libc.a $(MYLIBDIR2)libgcc_eh.a $(MYLIBDIR)libc.a $(MYLIBDIR2)crtend.o $(MYLIBDIR3)crtn.o

.PHONY : clean
clean : 
	rm -f mysql_demo mysql_demo.o
