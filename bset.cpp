#include <iostream>
#include "bset.h"
#define iter BSet::Biter

BSet::BSet() {
	length = 1;
	begin = 0;
	set = new bool[length];
	set[0] = false;
}

BSet::BSet(const BSet& bset) {
	length = bset.length;
	begin = bset.begin;
	set = new bool[length];
	for (int i = 0; i < length; i++)
		set[i] = false;
}

BSet::BSet(int beg, int end) {
	length = end - beg + 1;
	begin = beg;
	set = new bool[length];
	for (int i = 0; i < length; i++)
		set[i] = false;
}

BSet::BSet(int beg, std::string bset){
    length = static_cast<int>(bset.size());
    begin = beg;
    set = new bool[length + 1];
    for(int i = 0; i < length; i++)
        if(bset[i] == '1')
            set[i] = true;
        else if(bset[i] == '0')
            set[i] = false;

}

BSet::~BSet() {
	delete[] set;
}

void BSet::clear() {
    for(int i = 0; i < length; i++)
		set[i] = false;
}

bool BSet::add(int number) {
    if (number > begin + length - 1 || number < begin)
        return false;
    else
        set[number - begin] = true;
    return true;
}

bool BSet::del(int number) {
    if (number > begin + length || number < begin)
        return false;
    else
        set[number - begin] = false;
    return true;
}

bool BSet::isBelong(int number) {
    if (number > begin + length - 1 || number < begin)
        return false;
    else
        return set[number - begin];
}

int BSet::maxNumber() const {
    for(int i = length - 1; i >= 0; i--)
        if(set[i])
            return begin + i;
    return begin - 1;
}

int BSet::minNumber() const {
    for(int i = 0; i < length; i++)
        if(set[i])
            return begin + i;
    return begin - 1;
}

int min(int a, int b){
    return a <= b ? a : b;
}

int max(int a, int b){
    return a >= b ? a : b;
}

void BSet::operator+=(BSet &bSet) {
    BSet newSet = BSet(min(begin, bSet.begin),
                             max(bSet.begin + length - 1, begin + length - 1));
	for (int i = 0; i < length; i++) {
		if (isBelong(begin + i)) {
			newSet.add(begin + i);
		}
	}
	for (int i = 0; i < bSet.length; i++) 
	{
		if (bSet.isBelong(bSet.begin + i)) 
		{
			newSet.add(bSet.begin + i);
		}
	}
	delete[] set;
	set = new bool[newSet.length];
	for (int i = 0; i < newSet.length; i++)
		set[i] = newSet.set[i];
	begin = newSet.begin;
	length = newSet.length;
}

void BSet::operator*=(BSet &bSet) {
    int minNum = min(begin, bSet.begin) - 1,
        maxNum = max(begin + length - 1, bSet.begin + bSet.length - 1) + 1;
	for (int i = 0; i < length; i++) {
		if (isBelong(begin + i) && bSet.isBelong(begin + i) &&
			minNum == min(begin, bSet.begin) - 1)
			maxNum = minNum = begin + i;
		else if (isBelong(begin + i) && bSet.isBelong(begin + i))
			maxNum = begin + i;
	}
	if (minNum == min(begin, bSet.begin) - 1) {
		BSet newSet = BSet();
		delete[] set;
		set = new bool[newSet.length];
		for (int i = 0; i < newSet.length; i++)
			set[i] = newSet.set[i];
		begin = newSet.begin;
		length = newSet.length;
	}
	else if (minNum == maxNum) {
		BSet test = BSet(minNum, maxNum);
		test.add(minNum);
		delete[] set;
		set = new bool[test.length];
		for (int i = 0; i < test.length; i++)
			set[i] = test.set[i];
		begin = test.begin;
		length = test.length;
	}
    else{
        BSet newSet = BSet(minNum, maxNum);
		for (int i = 0; i < newSet.length; i++) {
			if (isBelong(newSet.begin + i) && bSet.isBelong(newSet.begin + i))
				newSet.add(newSet.begin + i);
		}
		delete[] set;
		set = new bool[newSet.length];
		for (int i = 0; i < newSet.length; i++)
			set[i] = newSet.set[i];
		begin = newSet.begin;
		length = newSet.length;
    }
}

void BSet::operator-=(BSet &bSet) {
    int minNum = min(begin, bSet.begin) - 1,
            maxNum = max(begin + length - 1, bSet.begin + bSet.length - 1) + 1;
	for (int i = 0; i < length; i++) {
		if (isBelong(begin + i) && !bSet.isBelong(begin + i) &&
			minNum == min(begin, bSet.begin) - 1)
			maxNum = minNum = begin + i;
		else if (isBelong(begin + i) && !bSet.isBelong(begin + i))
			maxNum = begin + i;
	}
	if (minNum == min(begin, bSet.begin) - 1) {
		BSet newSet = BSet();
		delete[] set;
		set = new bool[newSet.length];
		for (int i = 0; i < newSet.length; i++)
			set[i] = newSet.set[i];
		begin = newSet.begin;
		length = newSet.length;
	}
    else if (minNum == maxNum) {
		BSet test = BSet(minNum, maxNum);
		test.add(minNum);
		delete[] set;
		set = new bool[test.length];
		for (int i = 0; i < test.length; i++)
			set[i] = test.set[i];
		begin = test.begin;
		length = test.length;
	}
    else{
        BSet newSet = BSet(minNum, maxNum);
		for (int i = 0; i < newSet.length; i++) {
			if ((isBelong(newSet.begin + i) && !bSet.isBelong(newSet.begin + i)))
				newSet.add(newSet.begin + i);
		}
		delete[] set;
		set = new bool[newSet.length];
		for (int i = 0; i < newSet.length; i++)
			set[i] = newSet.set[i];
		begin = newSet.begin;
		length = newSet.length;
    }
}

void BSet::operator^=(BSet &bSet) {
    int minNum = min(begin, bSet.begin) - 1,
            maxNum = max(begin + length -1, bSet.begin + bSet.length - 1) + 1;
	int len1 = maxNum - minNum;
	int min1 = minNum;
	for (int i = 0; i < len1; i++) {
		if (((isBelong(min1 + i) && !bSet.isBelong(min1 + i)) ||
			(!isBelong(min1 + i) && bSet.isBelong(min1 + i))) &&
			minNum == min(begin, bSet.begin) - 1)
			maxNum = minNum = min1 + i;
		else if ((isBelong(min1 + i) && !bSet.isBelong(min1 + i)) ||
			(!isBelong(min1 + i) && bSet.isBelong(min1 + i)))
			maxNum = min1 + i;
	}
    if(minNum == min(begin, bSet.begin) - 1) {
		BSet newSet = BSet();
		delete[] set;
		set = new bool[newSet.length];
		for (int i = 0; i < newSet.length; i++)
			set[i] = newSet.set[i];
		begin = newSet.begin;
		length = newSet.length;
	}
    else if (minNum == maxNum) {
		BSet test = BSet(minNum, maxNum);
		test.add(minNum);
		delete[] set;
		set = new bool[test.length];
		for (int i = 0; i < test.length; i++)
			set[i] = test.set[i];
		begin = test.begin;
		length = test.length;
	}
    else{
        BSet newSet = BSet(minNum, maxNum);
		for (int i = 0; i < len1; i++) {
			if (((isBelong(min1 + i) && !bSet.isBelong(min1 + i)) ||
				(!isBelong(min1 + i) && bSet.isBelong(min1 + i)))) {
				newSet.add(newSet.begin + i);
			}
		}
		delete[] set;
		set = new bool[newSet.length];
		for (int i = 0; i < newSet.length; i++)
			set[i] = newSet.set[i];
		begin = newSet.begin;
		length = newSet.length;
    }
}

int BSet::getBegin() const {
    return begin;
}

int BSet::getEnd() const {
    return begin + length - 1;
}

bool BSet::updateBegin(int beg) {
    if(beg >= begin + length)
        return false;
    else if(beg == begin)
        return true;
    else{
		int len = length;
        if(beg > begin)
            len -= beg - begin;
        else
            len += beg - begin;
		delete[] set;
		set = new bool[len];
		for (int i = 0; i < len; i++)
			set[i] = isBelong(beg + i);
        begin = beg;
		length = len;
        return true;
    }
}

bool BSet::updateEnd(int end) {
    if(end < begin)
        return false;
    else if(end == begin + length - 1)
        return true;
    else{
		int len = end - begin + 1; 
		bool* temp = new bool[len];
		for (int i = 0; i < len; i++)
			temp[i] = false;
        for (int i = 0; i < len; i++) {
			temp[i] = isBelong(begin + i);
		}
		delete[] set;
		set = new bool[len];
		length = len;
		for (int i = 0; i < len; i++)
			set[i] = temp[i];
		delete[] temp;
        return true;
    }
}

void BSet::outputBits() const {
    for(int i = 0; i < length; i++)
        if(set[i])
            std::cout << 1 << ' ';
        else
            std::cout << 0 << ' ';
    std::cout << std::endl;
}

void BSet::outputNums() const {
    bool isNum = false;
    for(int i = 0; i < length; i++)
		if (set[i]) {
			std::cout << begin + i << ' ';
			isNum = true;
		}
    if(!isNum)
        std::cout << "There are no numbers";
    std::cout << std::endl;
}

