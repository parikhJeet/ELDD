PWD := $(shell pwd)
LINUX_PATH := /home/jeet/ELDD/WorkshopSetup/linux
ARCH_NAME := arm

obj-m := timer.o

all:
	make ARCH=${ARCH_NAME} CROSS_COMPILE=${CC} -C ${LINUX_PATH} M=$(PWD) modules
clean:
	make ARCH=${ARCH_NAME} CROSS_COMPILE=${CC} -C ${LINUX_PATH} M=$(PWD) clean


