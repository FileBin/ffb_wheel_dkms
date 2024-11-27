obj-m += hid-ffb-wheel.o

OUTPUT := $(PWD)/build 

all: 

	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 


clean: 

	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean