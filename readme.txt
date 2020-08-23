/!\ works with nftables 9.4 and prior versions

cd to nftq folder then compile with:
gcc -o nftq main.c getters.c processing.c  -lnftables -I ./headers/ -I ./headers/nftables/

Note: If you want to use previous versions of nftables , you will have to compile yourself thenthe header files: config.h and those inside "include"
