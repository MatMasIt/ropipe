all:
	echo "Compiling"
	gcc -o ropipe ropipe.c
install:
ifeq (,$(wildcard ./ropipe))
	make
endif
ifneq ($(shell id -u), 0)
	@echo "You must be root to install"
else
	mkdir -p /usr/local/share/man/man1/
	echo "Copying man file"
	cp ropipe.1 /usr/local/share/man/man1/ropipe.1
	echo "Installing binary"
	cp ropipe /usr/bin/ropipe
endif
uninstall:
ifneq ($(shell id -u), 0)
	@echo "You must be root to uninstall"
else
	echo "Removing man file"
	rm -rf /usr/local/share/man/man1/ropipe.1
	echo "Uninstalling binary"
	rm -rf /usr/bin/ropipe
endif
update:
	git pull
	make install

