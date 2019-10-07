#pragma once
template <typename Type>
class DLLIter;

template <typename Type>
class DLList
{
	friend class DLLIter<Type>;
private:
	struct node
	{
		node* prev;
		node* next;
		Type v;

	};

	int count;
	node* head;
	node* tail;

public:

	DLList()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	~DLList()
	{
		clear();
	}
	DLList<Type>& operator=(const DLList<Type>& that)
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
		if (x == nullptr)
		{
			return;
		}
		recursion(x->next);
		addHead(x->v);


	}

	DLList(const DLList<Type>& that)
	{
		*this = that;
	}

	void addHead(const Type& v)
	{
		node* n = new node();
		n->v = v;
		n->next = nullptr;
		n->prev = nullptr;

		if (head)
		{
			head->prev = n;
			n->next = head;
		}
		else
		{
			tail = n;
		}
		head = n;
	


		++count;
	}

	void addTail(const Type& v)
	{
		node* n = new node();
		n->v = v;
		n->next = nullptr;
		n->prev = nullptr;

		if (tail)
		{
			tail->next = n;
			n->prev = tail;
		}
		else
		{
			head = n;
		}
		tail = n;

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
		tail = nullptr;
		count = 0;
	}

	void insert(DLLIter<Type>& index, const Type& v)
	{
		if (index.iterator != nullptr)
		{
			node* n = new node();
			n->v = v;
			n->next = nullptr;
			n->prev = nullptr;

			node* temp = index.iterator;

			if (temp == head)
			{
				addHead(v);
				index.iterator = head;
			}

			else
			{
				n->prev = temp->prev;
				n->next = temp;
				n->prev->next = n;
				temp->prev = n;
				++count;
				index.iterator = n;
			}
		}

	}



	void remove(DLLIter<Type>& index)
	{
		if (index.iterator != nullptr)
		{
			node* temp = index.iterator;

			if (temp == head && temp == tail)
			{

				head = nullptr;
				tail = nullptr;
				index.iterator = nullptr;
				delete temp;

				count = 0;
			}

			else if (temp == tail)
			{

				temp->prev->next = nullptr;
				tail = temp->prev;
				index.iterator = tail->prev;
				delete temp;


				--count;

			}

			else if (temp == head)
			{

				temp->next->prev = nullptr;
				head = temp->next;
				index.iterator = head;
				delete temp;
				--count;
			}

			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				index.iterator = temp->next;
				delete temp;
				--count;
			}

		}

	}

	inline unsigned int size() const
	{
		return count;
	}
};

template <typename Type>
class DLLIter
{
	friend class DLList<Type>;
private:
	DLList<Type> * List;

	typename DLList<Type>::node * iterator;
	typename DLList<Type>::node * prev;


public:

	DLLIter(DLList<Type>& listToIterate)
	{
		List = &listToIterate;
	}

	void beginHead()
	{
		iterator = List->head;

	}

	void beginTail()
	{
		iterator = List->tail;
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

	DLLIter<Type>& operator++()
	{
		prev = iterator;
		if (iterator != nullptr)
		{
			iterator = iterator->next;
		}

		return *this;
	}

	DLLIter<Type>& operator--()
	{
		iterator = prev;
		if (prev != nullptr)
		{
			prev = prev->prev;
		}

		return *this;
	}

	Type& current() const
	{
		return iterator->v;
	}

};