#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "database.h"

using namespace std;

	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;


int MySQL::InitMySQL(void)
{
	cout << endl;

	try 
	{
		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("serwer2246104.home.pl", "35670400_icenet", "password123");

		/* Connect to the MySQL test database */
		con->setSchema("35670400_icenet");

		stmt = con->createStatement();

	} 
	catch (sql::SQLException &e) 
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;

	return EXIT_SUCCESS;
}

int MySQL::CreateServerTable(void)
{
	char buffer[256];
	sprintf(buffer,"CREATE TABLE 35670400_icenet.DmaServer 	( id INT(11) NOT NULL AUTO_INCREMENT , client  INT(11) NOT NULL , PRIMARY KEY (id)) ENGINE = InnoDB");

	cout << "IceNET ---> Create Server Table " << endl;

	stmt->execute(buffer);

	return EXIT_SUCCESS;
}

int MySQL::DeleteServerTable(void)
{
	char buffer[256];
	sprintf(buffer,"DROP TABLE DmaServer");

	cout << "IceNET ---> Delete Server Table " << endl;

	stmt->execute(buffer);

	return EXIT_SUCCESS;
}

int MySQL::CreateDmaTable(void)
{
	char buffer[256];
	sprintf(buffer,"CREATE TABLE 35670400_icenet.dma  		( id INT(11) NOT NULL AUTO_INCREMENT , address INT(11) NOT NULL , data INT(11) NOT NULL , length INT(11) NOT NULL , PRIMARY KEY (id)) ENGINE = InnoDB");

	cout << "IceNET ---> Create Dma Table " << endl;

	stmt->execute(buffer);

	return EXIT_SUCCESS;
}

int MySQL::DeleteDmaTable(void)
{
	char buffer[256];
	sprintf(buffer,"DROP TABLE dma");

	cout << "IceNET ---> Delete Dma Table " << endl;

	stmt->execute(buffer);

	return EXIT_SUCCESS;
}

int MySQL::ReadDmaTable(void)
{
	res = stmt->executeQuery("SELECT * FROM dma");
	while (res->next()) 
	{
		// You can use either numeric offsets...
		cout 	<< "IceNET --->" << " id = " << res->getInt(1) 
		 		<< " address = " << res->getInt(2) 
		 		<< " data = " << res->getInt(3) << endl;
	}

	return EXIT_SUCCESS;
}

int MySQL::ReadLastId(void)
{
	int ret;
	res = stmt->executeQuery("SELECT MAX(id) FROM dma");

	while (res->next()) 
	{
		// You can use either numeric offsets...
		ret = res->getInt(1);
	}
	
	return ret;
}

int MySQL::InsertIntoDmaTable(void)
{	
	char buffer[256];
	sprintf(buffer,"INSERT INTO dma (id, address, data, length) VALUES (NULL, '3355', '7766', '1')");

	cout << "IceNET ---> Insert Into Dma Table" << endl;
	stmt->execute(buffer);

	return EXIT_SUCCESS;
}

int MySQL::DeleteFormDmaTable(void)
{
	char buffer[256];
	sprintf(buffer,"DELETE FROM dma WHERE dma.id = %d",ReadLastId());

	cout << "IceNET ---> Remove From Dma Table" << endl;
	stmt->execute(buffer);

	return EXIT_SUCCESS;
}

int MySQL::DeleteDatabase(void)
{
	delete res;
	delete stmt;
	delete con;

	return EXIT_SUCCESS;
}