#include <iostream>
#include <exception>
#include "console.h"
#include "bset.h"
#include <set>
#include <iterator>
#include <string>
#define iter BSet::Biter
#define _CRTDBG_MAP_ALLOC ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif
using namespace std;
int main() {
    Console* test = new Console();
    test->start();
	delete test;
	/*BSet bset(1, "1010101010");
	for (iter it = iter(bset.beg()); it != bset.end(); it++) {
		cout << it.value() << endl;
	}*/


	_CrtDumpMemoryLeaks();
    return 0;
}
