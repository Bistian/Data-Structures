#pragma once
#include "DynArray.h"
using namespace std;

template <typename Type>
class BinaryHeap :
	public DynArray <Type>
{
public:

	void enqueue(const Type &v)
	{
		this->append(v);
		for (int i = size() - 1; i > 0; i = (i-1)/2 )
		{
			
			if(this->Array[(i-1)/2] > this->Array[i])
			{
					Type temp = this->Array[(i - 1) / 2];
					this->Array[(i - 1) / 2] = this->Array[i];
					this->Array[i] = temp;
			}
			else
			{
				break;
			}
		}

	}

	Type dequeue()
	{
		
			Type Done = this->Array[0];
			this->Array[0] = this->Array[size() -1];
			int change = 0;

			for (int i = 0; i < size(); i = change)
			{
				int left = i * 2 + 1;
				int right = i * 2 + 2;

				if (left >= size())
				{
					break;
				}

				else if (right >= size())
				{
					if (this->Array[left] < this->Array[i])
					{
						Type temp = this->Array[left];
						this->Array[left] = this->Array[i];
						this->Array[i] = temp;
						break;
					}
					else
					{
						break;
					}
				}

				 else if (this->Array[left] >= this->Array[right])
				{
					if (this->Array[right] < this->Array[i])
					{
						Type temp = this->Array[right];
						this->Array[right] = this->Array[i];
						this->Array[i] = temp;
						change = right;
					}
					else
					{
						break;
					}
				}

				else if (this->Array[left] < this->Array[right])
				{
					if (this->Array[left] < this->Array[i])
					{
						Type temp = this->Array[left];
						this->Array[left] = this->Array[i];
						this->Array[i] = temp;
						change = left;
					}
					else
					{
						break;
					}
				}

			}
			this->Size--;
			
			return Done;
		
	}

	void clear()
	{
		DynArray<Type>::clear();
    }

	Type& operator[](int index)
	{
		return this->Array[index];
    }


	unsigned int size()
	{
		return this->Size;
    }

};