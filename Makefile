CC = cc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 
UNAME := $(shell uname)

all:
	@echo "Compiling"
	$(CC) $(CFLAGS) -o ropipe ropipe.c
	@echo "Done"


install:
ifneq ($(UNAME), Linux)
	@echo "Automatic installation is only supported on Linux"
	@echo "Please copy the binary to a directory in your PATH"
	@echo "and the manpage to your manpages directory"
	@exit
endif
ifeq (,$(wildcard ./ropipe))
	make
endif
ifneq ($(shell id -u), 0)
	@echo "You must be root to install"
else
	mkdir -p /usr/local/share/man/man1/
	@echo "Copying man file"
	cp ropipe.1 /usr/local/share/man/man1/ropipe.1
	@echo "Installing binary"
	cp ropipe /usr/bin/ropipe
endif

uninstall:
ifneq ($(UNAME), Linux)
	@echo "Automatic uninstalling is only supported on Linux"
	@exit
endif
ifneq ($(shell id -u), 0)
	@echo "You must be root to uninstall"
else
	@echo "Removing man file"
	rm -rf /usr/local/share/man/man1/ropipe.1
	@echo "Uninstalling binary"
	rm -rf /usr/bin/ropipe
endif

update:
	git pull
	make install

