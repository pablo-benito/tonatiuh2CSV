.PHONY: all linux windows clean

PROGRAM = Tonatiuh2CSV
SOURCE = Tonatiuh2CSV.c
CC_LINUX_32 = gcc -m32
CC_LINUX_64 = gcc -m64
CC_WINDOWS_32 = i686-w64-mingw32-gcc
CC_WINDOWS_64 = x86_64-w64-mingw32-gcc

all: $(PROGRAM)_linux32 $(PROGRAM)_linux64 $(PROGRAM)_win32.exe $(PROGRAM)_win64.exe

linux: $(PROGRAM)_linux32 $(PROGRAM)_linux64

windows: $(PROGRAM)_win32.exe $(PROGRAM)_win64.exe


$(PROGRAM)_linux32:
	$(CC_LINUX_32) -O2 $(SOURCE) -o $@

$(PROGRAM)_linux64:
	$(CC_LINUX_64) -O2 $(SOURCE) -o $@

$(PROGRAM)_win32.exe:
	$(CC_WINDOWS_32) -O2 $(SOURCE) -o $@

$(PROGRAM)_win64.exe:
	$(CC_WINDOWS_64) -O2 $(SOURCE) -o $@

clean:
	rm -f  $(PROGRAM)_linux32 $(PROGRAM)_linux64 $(PROGRAM)_win32.exe $(PROGRAM)_win64.exe

