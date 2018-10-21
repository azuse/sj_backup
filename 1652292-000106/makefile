# Ñî×¿Óî 1652292 ¼Æ¿Æ2°à
SUBDIRS = $(shell ls -l | grep ^d | awk '{print $$9}')

all:
	@for subdir in $(SUBDIRS); \
	do \
		(cd $$subdir && make); \
	done \

clean:
	@for subdir in $(SUBDIRS); \
	do \
		(cd $$subdir && make clean); \
	done \
