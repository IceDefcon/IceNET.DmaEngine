#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int InitMySQL(void)
{
	cout << endl;

	try 
	{
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("serwer2246104.home.pl", "35670400_icenet", "password123");

		/* Connect to the MySQL test database */
		con->setSchema("35670400_icenet");

		stmt = con->createStatement();

		res = stmt->executeQuery("SELECT * FROM dma");
		while (res->next()) 
		{
			// You can use either numeric offsets...
			cout << "id = " << res->getInt(1) << "  address = " << res->getInt(2) << "  data = " << res->getInt(3) << endl;
		}

		// while (res->next()) 
		// {
		// 	cout << endl << "IceNET MySQL ---> ";
		// 	/* Access column data by alias or column name */
		// 	cout << res->getString("DmaMessage") << endl;
		// 	cout << "IceNET MySQL ---> ";
		// 	/* Access column data by numeric offset, 1 is the first column */
		// 	cout << res->getString(1) << endl;
		// }

		delete res;
		delete stmt;
		delete con;

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
