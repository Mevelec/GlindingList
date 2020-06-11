#pragma once
#include <stdint.h>


template <class T>
class GlindingList
{
protected:
	typedef T value_type; 
	typedef T* pointer; 
	typedef const T* const_pointer; 
	typedef T& reference; 
	typedef const T& const_reference; 
	typedef size_t size_type;

// NODE
	template< class T>
	class Node
	{
	public:
		Node(const T& ref)
			:
			data(ref),
			next(nullptr),
			previous(nullptr)
		{
		}
	public:
		T data;
		Node* next;
		Node* previous;
	};
	typedef	Node<value_type> value_node;
	typedef	Node<value_type>* value_node_ptr;

// ITERATOR
	template< class T>
	class Iterator
	{
	private:
		value_node_ptr node;
	public:
		Iterator(value_node_ptr node)
			:
			node(node)
		{
		};

	// OPERATORS
	public:
		Iterator<typename T>& operator++() {
			return *this->next;
		};

		Iterator operator++(int) {
			if (this->next != nullptr)
			{
				return *this->next;
			}
			else
			{
				throw std::exception("illegal offset");
			}
		};
		Iterator& operator--() {
			if (this->previous != nullptr)
			{
				return *this->previous;
			}
			else
			{
				throw std::exception("illegal offset");
			}
		};
		Iterator operator--(int) {
			if (this->previous != nullptr)
			{
				return *this->previous;
			}
			else
			{
				throw std::exception("illegal offset");
			}
		};
		Iterator operator+(int n)
		{
			auto it = *this;

			if (n > 0)
			{
				for (int i = 0; i < n; i++)
				{
					it = ++it;
				}
			}
			else if (n < 0)
			{
				for (int i = 0; i > n; i--)
				{
					it = it--;
				}
			}
			return it;
		}
		Iterator& operator+=(int n)
		{
			return *this->next;
		}
		Iterator operator-(int n)
		{
			auto it = *this;

			if (n > 0)
			{
				for (int i = 0; i < n; i++)
				{
					it = --it;
				}
			}
			else if (n < 0)
			{
				for (int i = 0; i > n; i--)
				{
					it = it++;
				}
			}
			return it;
		}
		/*Iterator& operator-=(difference_type n)
			bool operator==(const self_type& other) const
			bool operator!=(const self_type& other) const*/
	};
	typedef
		Iterator iterator;
	typedef
		Iterator* iterator_ptr;

	private:
		value_node_ptr root;		
		value_node_ptr tail;
		value_node_ptr head;


// Member functions
	public:
		GlindingList() {};

	public:
	// [back][.]...[.]...[center]...[.]...[.][head]
	// MODIFIERS 
		void push_back(const value_type& val)
		{
			if (root == nullptr)
			{
				root = new value_node(val);
				head = root;
				tail = root;
			}
			else
			{
				value_node_ptr node = new value_node(val);
				tail->previous = node;
				tail = node;
			}
		}
		void push_front(const value_type& val)
		{
			if (root == nullptr)
			{
				root = new value_node(val);
				head = root;
				tail = root;
			}
			else
			{
				value_node_ptr node = new value_node(val);
				head->next = node;
				head = node;
			}
		}
	// ELEMENT acces
		reference operator[] (int n);
		reference at(int n)
		{

		};
		reference front()
		{
			return this->head->data;
		};
		reference back()
		{
			return this->tail->data;
		};

};