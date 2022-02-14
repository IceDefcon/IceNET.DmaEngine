/* Simple C program that connects to MySQL Database server*/
#include <mysql/mysql.h>
#include <stdio.h>
#include <iostream> 

void InitMySQL(void) 
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	// mysql -h serwer2246104.home.pl -u 35670400_icenet -p 35670400_icenet
	char *server 	= "serwer2246104.home.pl";
	char *user 		= "35670400_icenet";
	char *password 	= "D3fc0d!ng!5590"; /* set me first */
	char *database 	= "35670400_icenet";

	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	else
	{
		printf("IceNET 3 ---> MySQL database connected\n");	
	}

	/* send SQL query */
	if (mysql_query(conn, "show tables")) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);

	/* output table name */
	printf("IceNET 4 ---> MySQL Tables in mysql database:\n");
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		printf("%s \n", row[0]);
	}

	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
}