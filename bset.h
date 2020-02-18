#ifndef BSET_H
#define BSET_H
#include <string>

class BSet
{
public:
	class Biter;
	BSet();
	BSet(const BSet& bset);
	BSet(int beg, int end);
    BSet(int beg, std::string set);
    ~BSet();
    void clear();
    bool add(int number);
    bool del(int number);
    bool isBelong(int number);
    int maxNumber() const;
    int minNumber() const;
    void operator+=(BSet &bSet);
    void operator*=(BSet &bSet);
    void operator-=(BSet &bSet);
    void operator^=(BSet &bSet);
    bool updateBegin(int begin);
    bool updateEnd(int end);
    int getBegin() const;
    int getEnd() const;
    void outputBits() const;
    void outputNums() const;
	Biter beg() { return set; }
	Biter end() { return set + length; }
	bool* set;
	class Biter
	{
	public:
		Biter(bool* first) : curr(first) {}
		void operator++(int) { curr++; }
		bool operator!=(Biter it) { return curr != it.curr; }
		bool value() { return *curr; }
	private:
		bool* curr;
	};
    int begin;
    int length;
};

#endif // BSET_H
