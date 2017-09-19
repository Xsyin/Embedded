led_on.bin:led_on.S
	arm-linux-gcc -g -c -o led_on.o led_on.S
	arm-linux-ld -Ttext 0x00000000 -g led_on.o -o led_on_elf
	arm-linux-objcopy -O binary -S led_on_elf led_on.bin
	arm-linux-objdump -D -m arm led_on_elf > led_on.dis
clean:
	rm -f led_on.bin led_on_elf led_on.dis *.o