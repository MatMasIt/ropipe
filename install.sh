if [ $(id -u) -ne 0 ]
  then echo "Please run as root"
  exit
fi
if [ -z $(which gcc) ]
  then echo "Please install gcc first"
  exit
fi
echo "Compiling ropipe"
gcc -o ropipe ropipe.c 
mkdir -p /usr/local/share/man/man1/
echo "Copying man file"
cp ropipe.1 /usr/local/share/man/man1/ropipe.1
echo "Installing binary"
cp ropipe /usr/bin/ropipe
echo "Done"