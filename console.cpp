#include "console.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

Console::Console() {
    bsets = std::vector<BSet*>();
	bsets.push_back(new BSet(-5, "10111"));
	bsets.push_back(new BSet(-5, "1010111000"));
}

Console::~Console() {
	for (int i = 0; i < static_cast<int>(bsets.size()); i++)
		delete bsets[i];
    bsets.clear();
}

void help() {
	std::cout << "help  ::  list and description of commands" << std::endl
		<< "add-set  ::  add empty set to the vector" << std::endl
		<< "add-rand  ::  add random set to the vector" << std::endl
		<< "add-set-str  ::  add set to the vector by a string of bitset" << std::endl
		<< "add-num  ::  add a number to set" << std::endl
		<< "union/+ ::  union of sets" << std::endl
		<< "intersect/*  ::  intersection of sets" << std::endl
		<< "substruct/-  ::  substruction" << std::endl
		<< "symdiffer/^  ::  symmetrical difference" << std::endl
		<< "test  ::  start tests" << std::endl
		<< "is-belong  ::  is number in set" << std::endl
		<< "bounds  ::  show bounds" << std::endl
		<< "show-bit  ::  show set of bits" << std::endl
		<< "show-num  ::  show set of numbers" << std::endl
		<< "show-all  ::  output all sets" << std::endl
		<< "clear  ::  clear set" << std::endl
		<< "clear-all  ::  clear all sets" << std::endl
		<< "exit  ::  exit" << std::endl;
}

void Console::start() {
    bool isWork = true;
    string command;
    while(isWork){
        cout << ">>>";
        cin >> command;
		if (command == "exit")
			isWork = false;
		else if (command == "help")
			help();
		else if (command == "add-set")
			createBSet();
		else if (command == "add-rand")
			createRand();
		else if (command == "add-set-str")
			createBSetByStr();
		else if (command == "add-num")
			addNumToSet();
		else if (command == "show-bit")
			showBSet();
		else if (command == "show-num")
			showNumSet();
		else if (command == "show-all")
			showAll();
		else if (command == "bounds")
			showBounds();
		else if (command == "clear")
			clearBSet();
		else if (command == "clear-all")
			clearAll();
		else if (command == "is-belong")
			isBelongInSet();
		else if (command == "union" || command == "+")
			bUnion();
		else if (command == "intersect" || command == "*")
			bIntersection();
		else if (command == "substruct" || command == "-")
			bSubstruct();
		else if (command == "symdiffer" || command == "^")
			bSymDiffer();
		else if (command == "test")
			test();
        else
            cout << "Unknown command" << endl;
    }
}

int inputNumber() {
	string str;
	int i;
	cin >> str;
	if (str == "0")
		return 0;
	else {
		i = strtol(str.c_str(), NULL, 10);
		if (i == 0) {
			cout << "Incorrect number. Try again: " << endl;
			return inputNumber();
		}
		return i;
	}
}


string randStr(int num) {
	string str;
	for (int i = 0; i < num; i++)
		if (rand() % 2 == 1)
			str += "1";
		else
			str += "0";
	return str;
}

void Console::test() {
	cout << "Please, input max bound of numbers in test: ";
	int max = inputNumber();
	clearAll();
	cout << "TEST!!! RANDOM DATA" << endl;
	for (int i = 0; i < 20; i++) {
		string str = randStr(1 + rand() % max);
		int beg = -max + rand() % (2*max - str.size());
		cout << ">>>add-set-str " << beg << ' ' << str << endl;
		bsets.push_back(new BSet(beg, str));
		bsets[i]->outputNums();
		cout << ">>>bounds" << endl;
		cout << "Min: " << bsets[i]->minNumber() << endl
			<< "Max: " << bsets[i]->maxNumber() << endl;
		cout << ">>>begin" << endl;
		cout << "Begin: " << bsets[i]->getBegin() << endl;
		cout << ">>>end" << endl;
		cout << "End: " << bsets[i]->getEnd() << endl;
		cout << endl << endl;
	}
	cout << endl << endl << endl << endl << endl << endl;
	cout << "TEST!!! RANDOM OPERATIONS" << endl;
	for (int i = 0; i < 10; i++) {


		int a = rand() % 20, b = rand() % 20;
		cout << ">>>union " << a << ' ' << b << endl;
		cout << a << "::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();
		cout << b << "::" << endl;
		bsets[b]->outputBits();
		bsets[b]->outputNums();
		*bsets[a] += *bsets[b];
		cout << "RESULT::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();

		cout << endl << endl;
		a = rand() % 20, b = rand() % 20;
		cout << ">>>intersect " << a << ' ' << b << endl;
		cout << a << "::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();
		cout << b << "::" << endl;
		bsets[b]->outputBits();
		bsets[b]->outputNums();
		*bsets[a] *= *bsets[b];
		cout << "RESULT::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();

		cout << endl << endl;
		a = rand() % 20, b = rand() % 20;
		cout << ">>>substruct " << a << ' ' << b << endl;
		cout << a << "::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();
		cout << b << "::" << endl;
		bsets[b]->outputBits();
		bsets[b]->outputNums();
		*bsets[a] -= *bsets[b];
		cout << "RESULT::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();

		cout << endl << endl;
		a = rand() % 20, b = rand() % 20;
		cout << ">>>symdiffer " << a << ' ' << b << endl;
		cout << a << "::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();
		cout << b << "::" << endl;
		bsets[b]->outputBits();
		bsets[b]->outputNums();
		*bsets[a] ^= *bsets[b];
		cout << "RESULT::" << endl;
		bsets[a]->outputBits();
		bsets[a]->outputNums();

		
	}

}


void Console::createBSet() {
    int beg, end;
    cout << "Input the lower bound of the set: ";
    beg = inputNumber();
    cout << "Input the higher bound of the set: ";
    end = inputNumber();
    if(end < beg)
        cout << "Error: End < begin" << endl;
    else{
		bsets.push_back(new BSet(beg, end));
        cout << "Success! ^)" << endl;
    }
}

void Console::createBSetByStr() {
	int beg;
	string str;
	cout << "Input the lower bound of the set: ";
	beg = inputNumber();
	cout << "Input the string of bitset: ";
	cin >> str;
	bsets.push_back(new BSet(beg, str));
	cout << "Success! ^)" << endl;
}

void Console::createRand() {
	cout << "Please, input max bound of numbers in test: ";
	int max = inputNumber();
	string str = randStr(1 + rand() % max);
	int beg = -max + rand() % (2 * max - str.size());
	bsets.push_back(new BSet(beg, str));
	cout << "Success! ^)" << endl;
}

void Console::clearBSet(){
    cout << "Input the index of set you want to clear" << endl;
    int id = inputNumber();
    if(id > static_cast<int>(bsets.size()) - 1 || id < 0)
        cout << "Index is invalid" << endl;
    else{
        bsets[id]->clear();
        cout << "Successfully cleared -_-" << endl;
    }
}

void Console::addNumToSet() {
    cout << "Input the index of set you want to edit: ";
    int id = inputNumber();
    if(id > static_cast<int>(bsets.size()) - 1 || id < 0)
        cout << "Index is invalid" << endl;
    else{
        cout << "Input the number: ";
        int num = inputNumber();
        if(bsets[id]->add(num))
            cout << "Successfully added ^-^" << endl;
        else
            cout << "Error: out of bounds :(" << endl;
    }
}

void Console::isBelongInSet() {
	cout << "Input the index of set you want to check: ";
	int id = inputNumber();
	if (id > static_cast<int>(bsets.size()) - 1 || id < 0)
		cout << "Index is invalid" << endl;
	else {
		cout << "Input the number: ";
		int num = inputNumber();
		if(bsets[id]->isBelong(num))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}

void Console::bUnion() {
	cout << "Input the index of first set you want to union: ";
	int id = inputNumber();
	if (id > static_cast<int>(bsets.size()) - 1 || id < 0)
		cout << "Index is invalid" << endl;
	else {
		cout << "Input the index of second set: ";
		int id_ = inputNumber();
		if (id_ > static_cast<int>(bsets.size()) - 1 || id_ < 0)
			cout << "Index is invalid" << endl;
		else {
			*bsets[id] += *bsets[id_];
			cout << "Success!))" << endl;
		}
	}
	
}

void Console::bIntersection()
{
	cout << "Input the index of first set you want to intersect: ";
	int id = inputNumber();
	if (id > static_cast<int>(bsets.size()) - 1 || id < 0)
		cout << "Index is invalid" << endl;
	else {
		cout << "Input the index of second set: ";
		int id_ = inputNumber();
		if (id_ > static_cast<int>(bsets.size()) - 1 || id_ < 0)
			cout << "Index is invalid" << endl;
		else {
			*bsets[id] *= *bsets[id_];
			cout << "Success!))" << endl;
		}
	}
}

void Console::bSubstruct()
{
	cout << "Input the index of first set you want to substruct: ";
	int id = inputNumber();
	if (id > static_cast<int>(bsets.size()) - 1 || id < 0)
		cout << "Index is invalid" << endl;
	else {
		cout << "Input the index of second set: ";
		int id_ = inputNumber();
		if (id_ > static_cast<int>(bsets.size()) - 1 || id_ < 0)
			cout << "Index is invalid" << endl;
		else {
			*bsets[id] -= *bsets[id_];
			cout << "Success!))" << endl;
		}
	}
}

void Console::bSymDiffer()
{
	cout << "Input the index of first set you want to xor: ";
	int id = inputNumber();
	if (id > static_cast<int>(bsets.size()) - 1 || id < 0)
		cout << "Index is invalid" << endl;
	else {
		cout << "Input the index of second set: ";
		int id_ = inputNumber();
		if (id_ > static_cast<int>(bsets.size()) - 1 || id_ < 0)
			cout << "Index is invalid" << endl;
		else {
			*bsets[id] ^= *bsets[id_];
			cout << "Success!))" << endl;
		}
	}
}

void Console::showBSet() const {
    cout << "Input the index of set you want to edit: ";
    int id = inputNumber();
    if(id > static_cast<int>(bsets.size()) - 1 || id < 0)
        cout << "Index is invalid" << endl;
    else
        bsets[id]->outputBits();
}

void Console::showNumSet() const {
    cout << "Input the index of set you want to edit: ";
    int id = inputNumber();
    if(id > static_cast<int>(bsets.size()) - 1 || id < 0)
        cout << "Index is invalid" << endl;
    else
        bsets[id]->outputNums();
}

void Console::showAll() {
	for(int i = 0; i < static_cast<int>(bsets.size()); i++){
		cout << i << "::" << endl;
		bsets[i]->outputBits();
		bsets[i]->outputNums();
	}
}

void Console::showBounds() {
	cout << "Input the index of set you want to check: ";
	int id = inputNumber();
	if (id > static_cast<int>(bsets.size()) - 1 || id < 0)
		cout << "Index is invalid" << endl;
	else
		cout << "Max: " << bsets[id]->minNumber() << endl
		<< "Min: " << bsets[id]->maxNumber() << endl;
}

void Console::clearAll() {
	if (static_cast<int>(bsets.size()) == 0)
		cout << "Vector is empty :(" << endl;
	else {
		for (int i = 0; i < static_cast<int>(bsets.size()); i++)
			delete bsets[i];
	}
	bsets.clear();
}





