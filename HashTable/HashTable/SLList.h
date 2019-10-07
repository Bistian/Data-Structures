#pragma once
template <typename Type>
class SLLIter;

template <typename Type>
class SLList
{
	friend class SLLIter<Type>;
private:
	struct node
	{
		node* next;
		Type v;
	
	};

	int count;
	node* head;

public:

	SLList()
	{
		head = nullptr;
		count = 0;
	}
	~SLList()
	{
		clear();
	}
	SLList<Type>& operator=(const SLList<Type>& that)
	{
		if (this != &that)
		{
			clear();
				recursion(that.head);
		}
		return *this;

	}

	void recursion(node *x)
	{
		if(x == nullptr)
		{
			return;
		}
		recursion(x->next);
	    	addHead(x->v);

		
	}

	SLList(const SLList<Type>& that)
	{
		*this = that;
	}

	void addHead(const Type& v)
	{
		node* n = new node();
		n->v = v;
		n->next = nullptr;

		if (head)
		{
			n->next = head;
			head = n;
		}
		else
		head = n;


		++count;
	}

	void clear()
	{
		node* del = head;
		while (del)
		{
			head = head->next;
			delete del;
			del = head;

		}
		head = nullptr;
		count = 0;
	}

	void insert(SLLIter<Type>& index, const Type& v)
	{
		if (index.iterator != nullptr)
		{
			node* n = new node();
			n->v = v;
			n->next = nullptr;

			node* temp = index.iterator;


			if (temp == head)
			{
				addHead(v);
				index.iterator = head;
			}

			else
			{
				n->next = temp;
				index.prev->next = n;
				index.iterator = n;
				++count;
			}
		}
			
	}

	

	void remove(SLLIter<Type>& index)
	{
		if (index.iterator != nullptr)
		{
			node* temp = index.iterator;


			if (temp == head)
			{
				head = index.iterator->next;
				index.iterator = head;
				--count;
			}
			else
			{
				index.prev->next = index.iterator->next;
				index.iterator = temp->next;
				--count;
			}

			delete temp;
		}
		
	}

	inline unsigned int size() const
	{
		return count;
	}
};

template <typename Type>
class SLLIter
{
	friend class SLList<Type>;
private:
	SLList<Type> * List;
public:
	typename SLList<Type>::node * iterator;
	typename SLList<Type>::node * prev;


public:

	SLLIter(SLList<Type>& listToIterate)
	{
		List = &listToIterate;
	}

	void begin()
	{
		iterator = List->head;
		
	}


	bool end() const
	{
		if (iterator == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	SLLIter<Type>& operator++()
	{
		prev = iterator;
		if (iterator != nullptr)
		{
			iterator = iterator->next;
		}
		
		return *this;
	}

	Type& current() const
	{
		return iterator->v;
	}

};