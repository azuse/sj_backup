# makefile
EXECNAME=test-1652238

all : lib1652238 test

test : 	test.c
	gcc test.c -L. -l1652238 -o test

lib1652238	:	lib1652238.c
	gcc -fPIC -shared lib1652238.c -o lib1652238.so

# .PHONY: install clean rpm

install	: all
	mkdir -p $(DIRROOT)/usr $(DIRROOT)/usr/sbin $(DIRROOT)/usr/lib64 $(DIRROOT)/etc $(DIRROOT)/usr/lib $(DIRROOT)/usr/lib/systemd $(DIRROOT)/usr/lib/systemd/system
	cp test $(DIRROOT)/usr/sbin/$(EXECNAME)
	cp lib1652238.so $(DIRROOT)/usr/lib64
	mkdir -p $(DIRROOT)/usr/1652238
	cp 1652238.dat $(DIRROOT)/usr/1652238
	cp 1652238.conf $(DIRROOT)/etc
	cp test-1652238.service $(DIRROOT)/usr/lib/systemd/system/
ifeq ($(DIRROOT), )
	systemctl daemon-reload
	systemctl enable test-1652238
	systemctl start test-1652238
endif

rpm	:
	mkdir -p SOURCES
	mkdir -p BUILD
	mkdir -p BUILDROOT
	mkdir -p RPMS
	mkdir -p SRPMS
	mkdir -p test-1652238-1.0.0
	cp makefile test.c lib1652238.c 1652238.dat 1652238.conf test-1652238.service test-1652238-1.0.0/
	# cp makefile test.c lib1652238.c 1652238.dat 1652238.conf test-1652238.service SOURCES/ 
	tar -cjf test.tar.bz2 test-1652238-1.0.0
	mv test.tar.bz2 SOURCES

	rpmbuild -ba test.spec --define "_topdir $(CURDIR)"

	# mv SRPMS/test-1652238-1.0.0-1.el7.centos.src.rpm test-1652238.src.rpm
	mv RPMS/x86_64/test-1652238-1.0.0-1.el7.centos.x86_64.rpm test-1652238.rpm

	rm -rf BUILD BUILDROOT RPMS SRPMS SOURCES SPECS test-1652238-1.0.0 
uninstall	:
	systemctl -q stop test-1652238 
	rm -f $(DIRROOT)/usr/sbin/$(EXECNAME) $(DIRROOT)/usr/lib64/lib1652238 $(DIRROOT)/etc/1652238.conf $(DIRROOT)/usr/1652238/1652238.dat 
	rm -df $(DIRROOT)/usr/1652238
	rm -f *.o test lib1652238.so
	rm -f $(DIRROOT)/usr/lib/systemd/system/test-1652238.service
	systemctl daemon-reload

clean:
	rm -rf BUILD BUILDROOT RPMS SRPMS SOURCES SPECS test-1652238-1.0.0 
	rm -f *.o test lib1652238.so *.rpm
