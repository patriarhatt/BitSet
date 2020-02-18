#ifndef TASK3_CONSOLE_H
#define TASK3_CONSOLE_H
#include "bset.h"
#include <vector>
#include <string>

class Console {
public:
    Console();
    ~Console();
    void start();
	void test();
    void createBSet();
    void createBSetByStr();
	void createRand();
    void addNumToSet();
	void isBelongInSet();
	void bUnion();
	void bIntersection();
	void bSubstruct();
	void bSymDiffer();
    void showBSet() const;
    void showNumSet() const;
	void showAll();
	void showBounds();
    void clearBSet();
	void clearAll();
private:
    std::vector<BSet*> bsets;

};


#endif //TASK3_CONSOLE_H
