//implementations of NodeList functions
#include <NodeList/NodeList.h>
#include <iostream>
using namespace std;

ostream & operator<<(ostream & os, const NodeList & nodelist)
{
	if (nodelist.m_head == nullptr) {
		os << "List is empty.\n";
		return os;
	}
	for (size_t i = 0; i < nodelist.size(); ++i) { //this can be a while loop, but it wouldn't be able to print the indexes
		os << "[" << i << "]: " << nodelist[i] << endl;
	}
	return os;
}

NodeList::NodeList() //an "empty" LL is just a nullptr
	: m_head(nullptr)
{ }

NodeList::NodeList(size_t count, const DataType & value)
	: m_head(nullptr)
{
	/*try {
		m_head = new Node(value);
	} catch (bad_alloc & ex) {
		delete m_head;
		m_head = nullptr;
		cerr << "Allocation error!\n";
	}
	Node * curr = m_head;
	for (size_t i = 0; i < count-1; ++i) {
		curr = insertAfter(curr, value);
	}*/

	Node ** curr2 = &m_head;
	for (size_t i2 = 0; i2 < count; ++i2) {
		try {
			*curr2 = new Node(value);
                } catch (bad_alloc & ex) {
			delete *curr2;
			*curr2 = nullptr;
			cerr << "Allocation error!\n";
		}
		curr2 = &((*curr2)->m_next);
	}
}

NodeList::NodeList(const NodeList & other)
{
	Node ** curr = &m_head;
	for (size_t i = 0; i < other.size(); ++i) {
		try {
			*curr = new Node(other[i]);
		} catch (bad_alloc & ex) {
			delete curr;
			cerr << "Allocation error!\n";
		}
		curr = &((*curr)->m_next);
	}
}

void NodeList::deleteAll(Node * curr) { //deletes everything after curr
	//could add (delete m_head) in this but it doesn't really need it
	//also could add a check to see if curr is null or not
	if (curr->m_next->m_next != nullptr) {
		deleteAll(curr->m_next);
	}
	delete curr->m_next;
	curr->m_next = nullptr;
}


NodeList::~NodeList()
{
	if (m_head != nullptr)
		deleteAll(m_head);
	delete m_head;
}

NodeList & NodeList::operator=(const NodeList &rhs)
{
	if (this != &rhs) {
		Node ** curr;
		if (m_head != nullptr) {
			deleteAll(m_head);
			delete m_head;
			m_head = nullptr;
		}
		curr = &m_head;
		for (size_t i = 0; i < rhs.size(); ++i) {
			try {
				*curr = new Node(rhs[i]);
			} catch (bad_alloc & ex) {
				delete curr;
				cerr << "Allocation error!\n";
			}
			curr = &((*curr)->m_next);
		}
	}
	return *this;
}

//front() and back() should probably return const pointers because they should not be used to change these values, but w.e
Node * NodeList::front()
{
	return m_head;
	//if head is empty, it should already be null
}

Node * NodeList::back()
{
	Node * curr = m_head;
	if (curr) {
		while (curr->m_next != nullptr)
			curr = curr->m_next;
		return curr;
	} else {
		return nullptr;
	}
}

Node * NodeList::find(const DataType &target, Node *&previous, const Node *after)
{
	const Node *curr, *prev;
	if (after) {
		prev = curr = after;
	} else {
		prev = curr = m_head;
		if (m_head->m_data == target) {
			previous = nullptr;
			return m_head;
		}
	}
	if (curr->m_next) {
		curr = curr->m_next;
	} else { //in the case that there is nothing after the given pointer
		previous = nullptr;
		return nullptr;
	}
	while (curr != nullptr) {
		if (curr->m_data == target) {
			previous = const_cast<Node*>(prev);
			return const_cast<Node*>(curr);
		}
		prev = prev->m_next;
		curr = curr->m_next;
	}
	previous = nullptr;
	return nullptr;
}

Node * NodeList::insertAfter(Node * target, const DataType &value)
{
	Node *curr = m_head, *temp, **add;
	if (target == nullptr) {
		add = &m_head;
	} else {
		while (curr != target)
			curr = curr->m_next;
		add = &(curr->m_next);
	}
	try {
		temp = new Node(value, *add);
	} catch (bad_alloc & ex) {
		delete temp;
		cerr << "Insertion error\n";
		return nullptr;
	}
	*add = temp;
	return *add;
}

Node * NodeList::insertBefore(Node * target, const DataType &value)
{
	Node *curr = m_head, *temp, **add;
	if (target == m_head) {
		add = &m_head;
	} else {
		while (curr->m_next != target)
			curr = curr->m_next;
		add = &(curr->m_next);
	}
	try {
		temp = new Node(value, *add);
	} catch (bad_alloc & ex) {
		delete temp;
		cerr << "Insertion error\n";
		return nullptr;
	}
	*add = temp;
	return *add;
}

Node * NodeList::erase(Node * target)
{
	Node *curr = m_head, *temp, **del;
	if (target == nullptr) {
			return nullptr;
	}
	if (target == m_head) {
		del = &m_head;
	} else {
		while (curr->m_next != target)
			curr = curr->m_next; //sets curr to be the node before target
		del = &(curr->m_next);
	}
	temp = (*del)->m_next; //temp is the node after target
	delete *del;
	*del = temp;
	return *del;
}

DataType & NodeList::operator[](size_t position)
{
	Node * curr = m_head; //assumes valid list
	for (int i = position; i > 0; --i) {
		curr = curr->m_next;
	}
	return curr->m_data;
}

const DataType & NodeList::operator[](size_t position) const
{
	Node * curr = m_head;
	for (int i = position; i > 0; --i) {
		curr = curr->m_next;
	}
	return curr->m_data;
}

size_t NodeList::size() const
{
	size_t size = 0;
	Node * curr = m_head;
	while (curr != nullptr) {
		++size;
		curr = curr->m_next;
	}
	return size;
}

bool NodeList::empty() const
{
	if (m_head == nullptr)
		return 1;
	return 0;
}

void NodeList::clear()
{
	if (m_head) {
		deleteAll(m_head);
		delete m_head;
		m_head = nullptr;
	} else {
		return;
	}
}
