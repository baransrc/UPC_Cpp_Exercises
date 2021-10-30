#include <iostream>
#include "string.h"

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

void dump_leaks(void)
{
	_CrtDumpMemoryLeaks(); // show leaks with file and line where allocation was made
}

exercise::string get_me_a_string() 
{
	return exercise::string("another string");
}

int main()
{
	atexit(dump_leaks);
	
	exercise::string string1("Wow, this string looks good.");

	std::cout << "string1: ";
	string1.print();

	// Move Constructor - 1:
	std::cout << "Move string1 to string2:" << std::endl;

	exercise::string string2(std::move(string1)); 

	std::cout << "string2: ";
	string2.print();
	std::cout << "string1: ";
	string1.print();

	// Move Constructor - 2:
	std::cout << std::endl;
	std::cout << "Construct string3 with std::move(exercise::string(\"Howdy\")):" << std::endl;

	exercise::string string3(std::move(exercise::string("Howdy")));
	std::cout << "string3: ";
	string3.print();
	

	// Copy Constructor:
	std::cout << std::endl;
	std::cout << "Copy string3 to string4:" << std::endl;
	
	exercise::string string4(string3);
	
	std::cout << "string3: ";
	string3.print();
	std::cout << "string4: ";
	string4.print();

	std::cout << std::endl;

	exercise::string string5("Hello");

	// Move assignment Operator - 1:
	std::cout << std::endl;
	std::cout << "Move string4 to string5 with assignment operator:" << std::endl;

	std::cout << "string4: ";
	string4.print();
	std::cout << "string5: ";
	string5.print();

	string5 = std::move(string4);

	std::cout << "string4: ";
	string4.print();
	std::cout << "string5: ";
	string5.print();

	// Move assignment Operator - 2:
	std::cout << std::endl;
	std::cout << "Move std::move(exercise::string(\"Wassup\")) to string4 with assignment operator:" << std::endl;

	std::cout << "string4: ";
	string4.print();

	string4 = std::move(exercise::string("Wassup"));

	std::cout << "string4: ";
	string4.print();

	// Copy Constructor & Move Assignment combined?:
	std::cout << std::endl;
	std::cout << "Assign const char* \"HELLO\" to string5:" << std::endl;

	std::cout << "string5: ";
	string5.print();

	// This piece of code automatically calls string::string(const char* _string) 
	// constructor overload to construct a temporary string with "HELLO" and feeds
	// it to the Move assignment operator:
	string5 = "HELLO";

	std::cout << "string5: ";
	string5.print();

	std::cout << std::endl;
	
	string4 = " WORLD!";

	// + Operator Overloading:
	std::cout << std::endl;
	std::cout << "+ Operator Overloading: string6 = string4 + string5\n";
	
	std::cout << "string4: ";
	string4.print();
	std::cout << "string5: ";
	string5.print();

	exercise::string string6 = (string5 + string4);

	std::cout << "string4: ";
	string4.print();
	std::cout << "string5: ";
	string5.print();
	std::cout << "string6: ";
	string6.print();

	// == Operator Overloading:
	std::cout << std::endl;
	std::cout << "== Operator Overloading: string4 == string5 and string5 == \"HELLO\"\n";

	std::cout << "string4: ";
	string4.print();

	std::cout << "Is string4 and string5 equal? " << (string4 == string5 ? "true" : "false") << std::endl;
	std::cout << "Is string5 and \"HELLO\" equal? " << (string5 == "HELLO" ? "true" : "false") << std::endl;

	// clear():
	std::cout << std::endl;
	std::cout << "string4.clear()\n";

	std::cout << "Before\n";
	std::cout << "string4: ";
	string4.print();

	string4.clear();

	std::cout << "After\n";
	std::cout << "string4: ";
	string4.print();

	// Move assignment operator function:
	std::cout << std::endl;
	std::cout << "exercise::string a_string = get_me_a_string():\n";

	// If the following code is like this:
	// exercise::string a_string = get_me_a_string();,
	// compiler simplifies the expression to:
	// exercise::string a_string("another string");
	// but if the code is like below: 
	exercise::string a_string;
	a_string = get_me_a_string();
	// compiler actually uses move assignment operator
	// so that it's not copying the rvalue string.

	std::cout << std::endl;

	//std::cin.get();
	return 0;
}