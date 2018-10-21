# makefile 1652238-000103
 
subdir=$(shell find . -maxdepth 1 -type d)
dirs:=$(basename $(patsubst ./%,%,$(subdir)))
 
.PHONY: $(dirs) clean
 
$(dirs):
		@for dir in $(dirs); do \
				$(MAKE) -C $$dir; \
		done
 
clean:
		@for dir in $(dirs); do \
				$(MAKE) -C $$dir clean; \
		done
