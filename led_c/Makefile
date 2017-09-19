led_c.bin:crt0.S led_c.c 
	arm-linux-gcc -g -c -o crt0.o crt0.S
	arm-linux-gcc -g -c -o led_c.o led_c.c
	arm-linux-ld -Ttext 0x00000000 -g crt0.o led_c.o -o led_c_elf
	arm-linux-objcopy -O binary -S led_c_elf led_c.bin
	arm-linux-objdump -D -m arm led_c_elf > led_c.dis
clean:
	rm -f led_c.dis led_c_elf led_c.bin *.o
	