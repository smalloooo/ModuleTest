KERNEL=/home/rd/ti-processor-sdk-linux-am335x-evm-04.02.00.09/board-support/linux-4.9.59+gitAUTOINC+a75d8e9305-ga75d8e9305
CROSS=/home/rd/git/buildroot-2017.11.2/output/host/usr/bin/arm-none-linux-gnueabi-

PWD := $(shell pwd)
obj-m += gpioTest.o

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) SUBDIRS=$(PWD) modules
clean:
	make -C $(KERNEL) SUBDIRS=$(PWD) clean
