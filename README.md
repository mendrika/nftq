/!\ works with nftables 9.6 and libnftnl 1.17

cd to nftq folder then compile with:
gcc -o nftq main.c getters.c processing.c  -lnftables -I ./headers/ -I ./headers/nftables/

run the program with no arguments to get help.

example of zabbix integration:

![zabbix-graph](screenshots/zabbix-1.png)

Note: If you want to use previous versions of nftables , you will have to compile yourself then copy/use the corresponding header files: config.h and those inside "include"
