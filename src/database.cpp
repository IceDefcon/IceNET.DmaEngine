#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

// mysql -h serwer2246104.home.pl -u 35670400_icenet -p 35670400_icenet

		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

int InitMySQL(void)
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

int AddTableComponent(void)
{
	cout << "IceNET ---> INSERT INTO dma (id, address, data, length) VALUES (NULL, '5000', '5555', '1'), (NULL, '6000', '6666', '1');" << endl;

	return 0;
}

int ReadDmaTable(void)
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

int DeleteDatabase(void)
{
	delete res;
	delete stmt;
	delete con;

	return EXIT_SUCCESS;
}