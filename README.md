/!\ this version works with nftables 9.6 and libnftnl 1.17 - please consider using the nftables headers matching your nftables version

cd to nftq folder then compile with:

gcc -o nftq main.c getters.c processing.c  -lnftables -I ./headers/ -I ./headers/nftables/

run the program with no argument to get help. This program prints out bytes/packets (integers) retrieved from nftables ruleset.
Once you got the counters (bytes or packets), you can create graph(s) with your favorite monitoring solution (zabbix, munin, ... etc ...).
In my case, I use zabbix (https://www.zabbix.com/). As example, here is an upload/Download graph (1) and statistics provided by nftq to Zabbix web interface (2):
 
![zabbix-graph](screenshots/zabbix-1.png)

![zabbix-graph](screenshots/zabbix-data-flow.png)

Note: Again ... if you want to use previous/different versions of nftables , you will have to compile yourself then copy/use the corresponding header files: config.h and those inside "include".
