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
