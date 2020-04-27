#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int hostOctet1, hostOctet2, hostOctet3, hostOctet4;
int majOctet1, majOctet2, majOctet3, majOctet4;
int subOctet1, subOctet2, subOctet3, subOctet4;

void MajorNetworkAnswers(int host1, int host2, int host3, int host4)
{
	bool cond = true;
	while (cond)
	{
		if (majOctet1 == 0)
		{
			printf("Major Network Address is: 0.0.0.0\n");
			printf("Major Network Broadcast Address is: 255.255.255.255\n");
			printf("CIDR Notation Major Network is: 0.0.0.0/8\n");
			printf("Number of Host Bits: 32\n");
			printf("Number of Usable Hosts per Network: 4,294,967,294\n");
			cond = false;
		}
		else if (majOctet1 == 255 && majOctet2 == 0)
		{
			printf("Major Network Address is: %d.0.0.0\n", host1);
			printf("Major Network Broadcast Address is: %d.255.255.255\n", host1);
			printf("CIDR Notation Major Network is: %d.0.0.0/8\n", host1);
			printf("Number of Host Bits: 24\n");
			printf("Number of Usable Hosts per Network: 16,777,214\n");
			cond = false;
		}
		else if (majOctet2 == 255 && majOctet3 == 0)
		{
			printf("Major Network Address is: %d.%d.0.0\n", host1, host2);
			printf("Major Network Broadcast Address is: %d.%d.255.255\n", host1, host2);
			printf("CIDR Notation Major Network is: %d.%d.0.0/16\n", host1, host2);
			printf("Number of Host Bits: 16\n");
			printf("Number of Usable Hosts per Network: 65,534\n");
			cond = false;
		}
		else if (majOctet3 == 255 && majOctet4 == 0)
		{
			printf("Major Network Address is: %d.%d.%d.0\n", host1, host2, host3);
			printf("Major Network Broadcast Address is: %d.%d.%d.255\n", host1, host2, host3);
			printf("CIDR Notation Major Network is: %d.%d.%d.0/24\n", host1, host2, host3);
			printf("Number of Host Bits: 8\n");
			printf("Number of Usable Hosts per Network: 254\n");
			cond = false;
		}
		else
		{
			printf("Please type choose either 255.0.0.0, 255.255.0.0, or 255.255.255.0 for the Major Network Mask: ");
			scanf("%d.%d.%d.%d", &majOctet1, &majOctet2, &majOctet3, &majOctet4);
		}
	}
}

//Function for counting how many subnet bits there are in a decimal number
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

//Function for converting decimal number into binary and storing the binary number into the binaryArray
int binaryArray[8];
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

void SubnetMaskAnswers(int sub1, int sub2, int sub3, int sub4)
{
	bool cond = true;
	while (cond)
	{
		if (majOctet1 == 255 && majOctet2 == 0) //if the Major Network Mask is 255.0.0.0
		{
			//Check if Subnet Mask is valid
			while ((sub1 == 255 && sub2 == 0) || sub1 == 0)
			{
				printf("Please choose an appropriate Subnet Mask: ");
				scanf("%d.%d.%d.%d", &subOctet1, &subOctet2, &subOctet3, &subOctet4);
				SubnetMaskAnswers(subOctet1, subOctet2, subOctet3, subOctet4);
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
		else if (majOctet2 == 255 && majOctet3 == 0) //if the Major Network Mask is 255.255.0.0
		{
			//Check if Subnet Mask is valid
			while ((sub1 == 255 && sub2 == 255 && sub3 == 0) || sub1 == 0 || sub2 == 0)
			{
				printf("Please choose an appropriate Subnet Mask: ");
				scanf("%d.%d.%d.%d", &subOctet1, &subOctet2, &subOctet3, &subOctet4);
				SubnetMaskAnswers(subOctet1, subOctet2, subOctet3, subOctet4);
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
		else if (majOctet3 == 255 && majOctet4 == 0) //if the Major Network Mask is 255.255.255.0
		{
			//Check if Subnet Mask is valid
			while ((sub1 == 255 && sub2 == 255 && sub3 == 255 && sub4 == 0) || sub1 == 0 || sub2 == 0 || sub3 == 0)
			{
				printf("Please choose an appropriate Subnet Mask: ");
				scanf("%d.%d.%d.%d", &subOctet1, &subOctet2, &subOctet3, &subOctet4);
				SubnetMaskAnswers(subOctet1, subOctet2, subOctet3, subOctet4);
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
			scanf("%d.%d.%d.%d", &subOctet1, &subOctet2, &subOctet3, &subOctet4);
			SubnetMaskAnswers(subOctet1, subOctet2, subOctet3, subOctet4);
		}
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

void Translation(int sub1, int sub2, int sub3, int sub4)
{

	if (sub2 == 255 && sub3 == 255) //if Subnet Mask is 255.255.255.# where # is some other number
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

  	 	printf("Subnet Address for this Host: %d.%d.%d.%d\n", hostOctet1, hostOctet2, hostOctet3, decimalOutput);
	}
	else if (sub2 == 255) //if Subnet Mask is 255.255.#.0 where # is some other number
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

  	 	printf("Subnet Address for this Host: %d.%d.%d.0\n", hostOctet1, hostOctet2, decimalOutput);
	}
	else //if Subnet Mask is 255.#.0.0 where # is some other number
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

  	 	printf("Subnet Address for this Host: %d.%d.0.0\n", hostOctet1, decimalOutput);
	}
}

int main()
{
	bool keepGoing = true; //Bool for keeping the program running
	int yesOrNo; //Int for switch case
	while (keepGoing)
	{
		//------------------------------Major Network Portion----------------------------------------------------
		printf("Please enter host IP address in this form \"#.#.#.#\": ");
		scanf("%d.%d.%d.%d", &hostOctet1, &hostOctet2, &hostOctet3, &hostOctet4);
		//Host Address Check
		while ((hostOctet1 > 255 || hostOctet2 > 255 || hostOctet3 > 255 || hostOctet4 > 255) || (hostOctet1 == 0 && hostOctet2 == 0 && hostOctet3 == 0 && hostOctet4 == 0))
		{
			printf("Please type in an appropriate Host Address: ");
			scanf("%d.%d.%d.%d", &hostOctet1, &hostOctet2, &hostOctet3, &hostOctet4);
		}

		printf("Please enter Major Network Mask IP Address in this form \"#.#.#.#\": ");
		scanf("%d.%d.%d.%d", &majOctet1, &majOctet2, &majOctet3, &majOctet4);
		//Major Network Mask Check
		while ((majOctet1 > 255 || majOctet2 > 255 || majOctet3 > 255 || majOctet4 > 255) || (majOctet1 == 255 && majOctet2 == 255 && majOctet3 == 255 && majOctet4 == 255))
		{
			printf("Please type in an appropriate Major Network Mask: ");
			scanf("%d.%d.%d.%d", &majOctet1, &majOctet2, &majOctet3, &majOctet4);
		}

		MajorNetworkAnswers(hostOctet1, hostOctet2, hostOctet3, hostOctet4);

		//------------------------------Subnet Mask Portion------------------------------------------------------
		printf("Please enter Subnet Mask IP Address in this form \"#.#.#.#\": ");
		scanf("%d.%d.%d.%d", &subOctet1, &subOctet2, &subOctet3, &subOctet4);
		//Subnet Mask Check
		while ((subOctet1 > 255 || subOctet2 > 255 || subOctet3 > 255 || subOctet4 > 255) || (subOctet1 == 255 && subOctet2 == 255 && subOctet3 == 255 && subOctet4 == 255))
		{
			printf("Please type in an appropriate Subnet Mask: ");
			scanf("%d.%d.%d.%d", &subOctet1, &subOctet2, &subOctet3, &subOctet4);
		}

		SubnetMaskAnswers(subOctet1, subOctet2, subOctet3, subOctet4);
		//----------------------------Host Address Translation Portion-------------------------------------------
		printf("Host Address Translation: \n");
		Translation(subOctet1, subOctet2, subOctet3, subOctet4);

		//Ask user to do another calculation
		printf("Do you want to do another calculation?\n1 = Yes\n2 = No\n: ");
		scanf("%d", &yesOrNo);
		switch (yesOrNo)
		{
			case 1: keepGoing = true;
			break;
			case 2: keepGoing = false;
			break;
		}
	}
	return 0;
}
