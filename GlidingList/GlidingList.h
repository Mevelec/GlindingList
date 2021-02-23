#pragma once
#include <stdint.h>
#include <stdexcept>

template <class T>
class GlindingList
{

////////////////////////////////////////////////////////////////
/////////////////////////  DECLARATIONS  ///////////////////////
////////////////////////////////////////////////////////////////
protected:
	typedef T value_type; 
	typedef T* pointer; 
	typedef const T* const_pointer; 
	typedef T& reference; 
	typedef const T& const_reference; 
	typedef size_t size_type;

///////// NODE /////////////////
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
		Node(const Node<T>& ref){
			this->data = ref.data;
			this->next = new Node<T>(ref.next());
			this->previous = new Node<T>(ref.previous());
		}
		Node<T>& operator=(const Node<T>& ref) {
			delete this->next;
			delete this->previous;

			this->data = ref.data;
			this->next = new Node<T>(ref.next());
			this->previous = new Node<T>(ref.previous());

			return *this;
		}
	public:
		T data;
		Node* next;
		Node* previous;
	};
	typedef	Node<value_type> value_node;
	typedef	Node<value_type>* value_node_ptr;

///////////////// ITERATOR /////////////////
	template< class T>
	class Iterator
	{
	private:
		value_node_ptr node;
	public:
		Iterator()
		{
		};

		Iterator( value_node_ptr node) :
			node(node)
		{
		};

	// OPERATORS
	public:
		reference operator*()
		{
			return node->data;
		}
		Iterator& operator++() {
			if (node->next != nullptr)
			{
				this->node = node->next;
				return *this;
			}
			else
			{
				throw std::exception("illegal offset");
			}
		};
		Iterator operator++(int) {
			if (node->next != nullptr)
			{
				this->node = node->next;
				return *this;
			}
			else
			{
				throw std::exception("illegal offset");
			}
		};
		Iterator& operator--() {
			if (node->previous != nullptr)
			{
				this->node = node->previous;
				return *this;
			}
			else
			{
				throw std::exception("illegal offset");
			}
		};
		Iterator operator--(int) {
			if (node->previous != nullptr)
			{
				this->node = node->previous;
				return *this;
			}
			else
			{
				throw std::exception("illegal offset");
			}
		};
		
		Iterator operator+(int n)
		{
			iterator it(*this);

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
		Iterator operator-(int n)
		{
			iterator it(*this);

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
		bool operator==(const Iterator& other) const
		{
			if (this->node->data != other.node->data)
				return 1;
			else
				return 0;
		}
		bool operator!=(const Iterator& other) const
		{
			if (this->node == nullptr && other.node == nullptr) {
				return false;
			}
			else if (this->node == nullptr || other.node == nullptr) {
				return true;
			}
			else {
				if (this->node->data == other.node->data)
					return false;
				else
					return true;
			}
		}
	};
	public :
		typedef	Iterator<value_type> iterator;
		typedef	Iterator<value_type>* iterator_ptr;


////////////////////////////////////////////////////////////////
/////////////////////////  GLIDINGLIST CLASS  //////////////////
////////////////////////////////////////////////////////////////

	private:
		size_t size, size_max;
		value_node_ptr midle;
		value_node_ptr tail;
		value_node_ptr head;

// Member functions
	public:
		GlindingList( size_t max = 0) : size(0), size_max(max){};
		~GlindingList() {
			//TODO : delete nodes
		};

		GlindingList(const GlindingList<value_type>& ref) : size(ref.size), size_max(ref.size_max) {
			if (ref.midle != nullptr) {
				this->midle = new Node<value_type>(ref.midle->data);
				if (ref.head == ref.midle && ref.tail == ref.midle) {
					this->head = this->midle;
					this->tail = this->midle;
				}
				else
				{
					// forward
					if (ref.head != ref.midle) {
						Node<value_type>* it2 = this->midle;
						Node<value_type>* it = ref.midle->next;
						for (; it != ref.head; it = it->next)
						{
							it2->next = new Node<value_type>(it->data);
							it2->next->previous = it2;
							it2 = it2->next;
						}
						it2->next = new Node<value_type>(it->data);
						it2->next->previous = it2;
						it2 = it2->next;

						this->head = it2;
					}
					else {
						this->head = this->midle;
					}

					// backward
					if (ref.tail != ref.midle) {
						Node<value_type>* it2 = this->midle;
						Node<value_type>* it = ref.midle->previous;
						for (; it != ref.tail; it = it->previous)
						{
							it2->previous = new Node<value_type>(it->data);
							it2->previous->next = it2;
							it2 = it2->previous;
						}
						it2->previous = new Node<value_type>(it->data);
						it2->previous->next = it2;
						it2 = it2->previous;

						this->tail = it2;
					}
					else {
						this->tail = this->midle;
					}
				}
			}
		};
		GlindingList<T>& operator= (const GlindingList<T>& ref) {};
	public:
	// [back/tail][.]...[.]...[center]...[.]...[.][front/head]
	// MODIFIERS 
		void push_back(const value_type& val)
		{
			if (midle == nullptr)
			{
				midle = new value_node(val);
				head = midle;
				tail = midle;
			}
			else
			{
				if(size_max > 0 && size == size_max) {
					head->data = val;
					tail = head;
					head = head->previous;
				}
				else {
					value_node_ptr node = new value_node(val);

					// assign refs
					tail->previous = node;
					node->next = tail;
					node->previous = head;
					tail = node;
					head->next = tail;
				}
			}
			++size;
		}
		void push_front(const value_type& val)
		{
			if (midle == nullptr)
			{
				midle = new value_node(val);
				head = midle;
				tail = midle;
			}
			else
			{
				if (size_max > 0 && size == size_max) {
					tail->data = val;
					head = tail;
					tail = tail->next;
				}
				else{
					value_node_ptr node = new value_node(val);

					// assign refs
					head->next = node;
					node->previous = head;
					node->next = tail;
					head = node;
					tail->previous = head;
				}
			}
			++size;
		}
	// ELEMENT acces
		reference operator[] (int n)
		{
			return at(n);
		}
		reference at(int n)
		{
			auto it = this->midle;
			if (n >= 0) {
				for (size_t i = 0; i < n; i++)
				{
					it = it->next;
				}
			}
			else {
				for (int i = 0; i > n; i--)
				{
					it = it->previous;
				}
			}
			return it->data;
		};	
		// [back/tail][.]...[.]...[center]...[.]...[.][front/head]
		iterator front()
		{
			return iterator(this->head);
		};
		iterator back()
		{
			return iterator(this->tail);
		};
		iterator root()
		{
			return iterator(this->midle);
		};
	// Operator ==
		friend bool operator==(const GlindingList<T>& ref, const GlindingList<T>& ref2){
			GlindingList<T>::iterator it1 = ref2.midle;
			GlindingList<T>::iterator it2 = ref.midle;
			bool ret = true;
			if (ref.size != ref2.size || ref.size_max != ref2.size_max) {
				return false;
			}
			size_t size = std::min(ref.size, ref2.size);
			for (size_t i = 0; i < size && ret; ++i)
			{
				if (it1 != it2) ret = false;
				++it1;
				++it2;
			}
			return ret;
		}
		friend bool operator!=(const GlindingList<T>& ref, const GlindingList<T>& ref2) {
			GlindingList<T>::iterator it1 = ref2.midle;
			GlindingList<T>::iterator it2 = ref.midle;
			bool ret = false;
			if (ref.size != ref2.size || ref.size_max != ref2.size_max) {
				return true;
			}
			size_t size = std::min(ref.size, ref2.size);
			for (size_t i = 0; i < size && ret; ++i)
			{
				if (it1 != it2) ret = true;
				++it1;
				++it2;
			}
			return ret;
		}
};