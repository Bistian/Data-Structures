#pragma once
#define TH template<typename Type>


template<typename Type>
class DynArray
{
protected:
	unsigned int Size;
	unsigned int Capacity;
	Type * Array;
	

public:
	DynArray()
	{
		Type * Array = new Type[0];
		Size = 0;
		Capacity = 0;
	}
	~DynArray()
	{
		clear();
	}



	DynArray(const DynArray<Type>& that)
	{
		*this = that;
	}

	DynArray<Type>& operator=(const DynArray<Type>& that)
	{
		if (this != & that)
		{
			Capacity = that.Capacity;
			Size = that.Size;
			Array = that.Array;
		}
		return *this;
	}

	Type& operator[](const unsigned int index)
	{
		return Array[index];
	}

	const Type& operator[](const unsigned int index) const
	{
		return Array[index];
	}

	unsigned int size() const
	{
		return Size;
	}

	unsigned int capacity() const
	{
		return Capacity;
	}

	void clear()
	{
		Size = 0;
		Capacity = 0;
		Array = nullptr;
	}


	void append(const Type& item)
	{
		Type * array2;
		if (Size == Capacity)
		{
			if (Capacity == 0)
			{
				Capacity++;
				array2 = new Type[Capacity];
			}
			else
			{
				Capacity = Capacity * 2;
				 array2 = new Type[Capacity];
			}
			for (int i = 0; i < Size; i++)
			{
				array2[i] = Array[i];
			}
			array2[Size] = item;
			 Array = array2;
		
		
		}
		else
		{
			Array[Size] = item;
		}
		
		++Size;
		
	}

	void reserve(const unsigned int & newCap = 0)
	{
		Type * array3;
		if (newCap <= Capacity && newCap != 0)
		{

		}
		else
		{

			if (newCap > 0)
			{
				Capacity = newCap;
				array3 = new Type[Capacity];
			}
			
			else
			{
				Capacity = Capacity * 2;
				array3 = new Type[Capacity];
			}

			if (Capacity == 0)
			{
				Capacity++;
				array3 = new Type[Capacity];
			}
			for (int i = 0; i < Size; i++)
			{
				array3[i] = Array[i];
			}
			Array = array3;
		

		}
	}

};