#ifndef BITER_H
#define BITER_H
#include <string>

class Biter
{
public:
	bool& operator++(int) { return *curr++; }
private:
	bool* curr;
};

#endif // BITER_H