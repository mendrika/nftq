/!\ works with nftables 9.4 and prior versions

cd to nftq folder then compile with:
gcc -o nftq main.c getters.c processing.c  -lnftables -I ./headers/ -I ./headers/nftables/
