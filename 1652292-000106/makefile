# ��׿�� 1652292 �ƿ�2��
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
