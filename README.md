/!\ works with nftables 9.6 and libnftnl 1.17

cd to nftq folder then compile with:
gcc -o nftq main.c getters.c processing.c  -lnftables -I ./headers/ -I ./headers/nftables/

run the program with no argument to get help.

Once you got the counters (bytes or packets), you can create graph(s) with your favorite monitoring solution.
In my case, I use zabbix (https://www.zabbix.com/):

![zabbix-graph](screenshots/zabbix-1.png)


Note: If you want to use previous/different versions of nftables , you will have to compile yourself then copy/use the corresponding header files: config.h and those inside "include".
