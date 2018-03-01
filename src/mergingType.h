#pragma once
#ifndef MERGINGTYPE_H
#define MERGINGTYPE_H

class mergingType
{
	friend class HuffmanCoding;
public:
	//constructor copy data and count to class
	mergingType(int dat = 0, int cnt = 0)
	{
		data = dat; count = cnt;
	}

	//copy right's elements into this class's elements
	mergingType &operator=(const mergingType &right)
	{
		data = right.data; count = right.count; return *this;
	}

	//both of items must be equal
	bool operator==(const mergingType &right) const
	{
		return ((count == right.count) && (data == right.data));
	}

	//because equality is checked data is useless
	bool operator<=(const mergingType &right) const
	{
		return count <= right.count;
	}

	//because equality is checked data is useless
	bool operator>=(const mergingType &right) const
	{
		return count >= right.count;
	}

	bool operator<(const mergingType &right) const
	{
		if (count < right.count)
			return true;
		else if (count > right.count)
			return false;
		else 
			return data > right.data;
	}

	bool operator>(const mergingType &right) const
	{
		if (count > right.count)
			return true;
		else if (count < right.count)
			return false;
		else
			return data < right.data;
	}

	//return a new object containing some of both elements
	mergingType operator+(const mergingType &right) const
	{
		mergingType tmp(data + right.data, count + right.count); return tmp;
	}
private:
	int data;
	int count;
};
#endif