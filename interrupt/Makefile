# src_s := $(wildcard *.S)
# objs := $(patsubst %.S,%.o,$(src_s))
# src_c := $(shell ls *.c)
# objs += $(patsubst %.c,%.o,$(src_c))
objs := head.o init.o interrupt.o main.o   

interrupt.bin:$(objs)
	arm-linux-ld -Ttext 0x00000000 -o interrupt_elf $^
	arm-linux-objcopy -O binary -S interrupt_elf $@
	arm-linux-objdump -D -m arm interrupt_elf > interrupt.dis
%.o:%.c
	arm-linux-gcc -Wall -O2 -c -o $@ $<
%.o:%.S
	arm-linux-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f interrupt_elf interrupt.bin interrupt.dis *.o
