#include <stdio.h>
#include <mysql.h>

int main()
{
    printf("Hi\n");
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
 
	char *server = "";
	char *user = "";
	char *password = "";
	char *database = "";
 
	conn = mysql_init(NULL);
 
	//Making connection to database
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
	 	printf("Connection Failed... Error: %s\n", mysql_error(conn));
		return 0;
	}
 	else
 	{
 		printf("IT WORKED");
	}
	
	//Test Query
	mysql_query(conn, "show databases");
	res = mysql_use_result(conn);
	
	printf("Table:\n");
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		printf("%s \n", row[0]);	
	}




 
}

int subnetCalculator{ // Not fully implemented -- just conceptual -- Will likely split into multiplefunctions
	/* OCT variable for each octet x.x.x.x and CIDR for mask */
	int OCT0, OCT1, OCT2, OCT3, CIDR; 
	/* Finding IP class */
	char class;	

	/* Conditional statement to remove invalid IP addresses */
	if( ((OCT0 < 0) || (OCT1 < 0) || (OCT2 < 0) || (OCT3 < 0)) || 
	((OCT0 > 255) || (OCT1 > 255) || (OCT2 > 255) || (OCT3 > 255)) || 
	((OCT0 == 127)) || 
	((OCT0 == 0) && (OCT1 == 0) && (OCT2 == 0) && (OCT3 == 0)){
		
		return -1; // Conceptual; requery user for a correct IP
	}

	/* Conditional statement to remove invalid CIDR */
	if(CIDR > 32 || CIDR < 0){
		return -1; // Conceptual; requery user for a correct CIDR
	}
	
	/* Conditional statement to assign IP class */
	if(OCT0 <=127){ // Assigning Class
		class = 'A';
	}else if (OCT0 <=192){
		class = 'B';
	} else{
		class = 'C';
	}
	
	
}
