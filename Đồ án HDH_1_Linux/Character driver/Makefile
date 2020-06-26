KDIR= /lib/modules/`uname -r`/build
all:
	make -C $(KDIR) M=`pwd` modules
	$(CC) testran.c -o test
clean:
	make -C $(KDIR) M=`pwd` clean
	rm test
