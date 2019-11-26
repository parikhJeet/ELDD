SUBDIRS := 1_NothingLKM 

all:
	for dir in $(SUBDIRS); do \
        $(MAKE) -C $$dir; \
    done


clean:
	for dir in $(SUBDIRS); do \
        $(MAKE) -C $$dir clean; \
    done
