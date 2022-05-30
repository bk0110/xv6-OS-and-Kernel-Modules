
obj-m += KernelModuleWriting.o
obj-m += ListingRunningTasks.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
