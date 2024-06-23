obj-m += test_basic_allocation.o
obj-m += test_buffer_overflow.o
obj-m += test_invalid_free.o
obj-m += test_max_allocation.o
obj-m += test_non_initialized.o
obj-m += test_performance_allocation.o
obj-m += test_times.o
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
 
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean