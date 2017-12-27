cmake_minimum_required(VERSION 3.9)
project(I2C)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(lib)

add_executable(I2C
        include/ctype.h
        include/gcclib.h
        include/kernel.h
        include/stdio.h
        include/system.h
        include/types.h
        lib/ctype.c
        lib/div64.h
        lib/div64.S
        lib/lib1funcs.S
        lib/libc.a
        lib/Makefile
        lib/muldi3.c
        lib/printf.c
        lib/printf.h
        lib/string.c
        lib/string.h
        lib/vsprintf.c
        lib/vsprintf.h
        cfg.txt
        head.S
        i2c.c
        i2c.h
        init.c
        interrupt.c
        m41t11.c
        m41t11.h
        nand.c
        s3c2440.h
        serial.c
        serial.h)
