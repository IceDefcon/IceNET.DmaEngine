#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
 
using namespace std;

class interface 
{
	public:
		void setLength( double len );
		double getLength( void );

		interface();   // This is the constructor declaration
		~interface();  // This is the destructor: declaration

	private:
		double length;
};
 
// Constructor
interface::interface(void) 
{
	cout << "IceNET 5 ---> Interface Created" << endl;
}

// Destructor
interface::~interface(void) 
{
	cout << "IceNET 6 ---> Interface Destroyed" << endl;
}

void interface::setLength( double len ) 
{
	length = len;
}

double interface::getLength( void ) 
{
	return length;
}




#endif /* INTERFACE_H */
