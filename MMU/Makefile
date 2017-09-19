src_c := $(shell ls *.c)
objs := $(patsubst %.c,%.o,$(src_c))
src_s := $(wildcard *.S)
objs += $(patsubst %.S,%.o,$(src_s))

mmu.bin:$(objs)
	@echo $(objs)
	arm-linux-ld -Tmmu.lds -o mmu_elf $^
	arm-linux-objcopy -O binary -S mmu_elf $@
	arm-linux-objdump -D -m arm mmu_elf > mmu.dis
%.o:%.c
	arm-linux-gcc -Wall -O2 -c -o $@ $<
%.o:%.S
	arm-linux-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f mmu_elf mmu.bin mmu.dis *.o
