#pragma once
#include "SLList.h"
template <typename Type>
class HTable
{
public:
	unsigned int Buckets;
	unsigned int(*pf) (const Type &v) = nullptr;
	SLList <Type> *Table = nullptr;

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor 
	// Parameters : numOfBuckets - the number of buckets
	//              hFunction - pointer to the hash function for this table
	// Notes : constructs an empty hash table
	/////////////////////////////////////////////////////////////////////////////
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
	{
		Table = new SLList<Type>[numOfBuckets];
		Buckets = numOfBuckets;
		pf = hFunction;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys a hash table
	/////////////////////////////////////////////////////////////////////////////
	~HTable()
	{
		delete[] Table;

	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	/////////////////////////////////////////////////////////////////////////////
	HTable<Type>& operator=(const HTable<Type>& that)
	{
		if (this != &that)
		{
			delete[] Table;
			this->Buckets = that.Buckets;
			this->pf = that.pf;
			this->Table = new SLList<Type>[that.Buckets];

			for (size_t i = 0; i < Buckets; i++)
			{
				Table[i] = that.Table[i];
			}
		
		}
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	HTable(const HTable<Type>& that)
	{
		*this = that;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters : v - the item to insert into the hash table
	/////////////////////////////////////////////////////////////////////////////
	void insert(const Type& v)
	{
		int Bucket = (*pf)(v);
		Table[Bucket].addHead(v);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : findAndRemove
	// Parameters : v - the item to remove(if it is found)
	/////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& v)
	{
		int Bucket = (*pf)(v);
		int count = 0;

		SLLIter <Type> iter(Table[Bucket]);
		iter.begin();

		while (iter.iterator != nullptr)
		{
			if (iter.current() != v)
			{
				++iter;
			}
			else
			{
				Table[Bucket].remove(iter);
				return true;
			}
		}
		return false;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the hash table
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		for (size_t i = 0; i < Buckets; i++)
		{
				Table[i].clear();
		}
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : find
	// Parameters : v - the item to look for
	// Return : the bucket we found the item in or -1 if we didn’t find the item.
	/////////////////////////////////////////////////////////////////////////////
	int find(const Type& v) const
	{
		int index = (*pf)(v);

		SLLIter <Type> iter(Table[index]);
		iter.begin();

		while (!iter.end())
		{
			if (iter.current() == v)
			{
				return index;
			}
		
				++iter;
		}
		return -1;
	}
};