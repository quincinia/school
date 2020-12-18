//nodequeue implementations

#include <NodeQueue/NodeQueue.h>
using namespace std;

NodeQueue::NodeQueue()
	: m_front(nullptr),
	  m_back(nullptr)
{
	cout << "NodeQueue Default Constructor" << endl;
}

NodeQueue::NodeQueue(size_t size, const DataType & value)
	: m_front(nullptr),
	  m_back(nullptr)
{
	cout << "NodeQueue Parameterized Constructor" << endl;
	Node ** curr = &m_front;
	for (size_t i = 0; i < size-1; ++i) {
		try {
			*curr = new Node(value);
				} catch (bad_alloc & ex) {
			delete *curr;
			*curr = nullptr;
			cerr << "Allocation error!" << endl;
		}
		curr = &((*curr)->m_next);
	}
	try {
		*curr = new Node(value);
	} catch (bad_alloc & ex) {
		delete *curr;
		*curr = nullptr;
		cerr << "Allocation error!" << endl;
	}
	m_back = *curr;
}

NodeQueue::NodeQueue(const NodeQueue & other)
{
	//not sure if this is even possible to be made with this setup
	cout << "NodeQueue Copy Constructor" << endl;
	size_t otherSize = other.empty() ? 0 : other.size()-1;
	Node ** curr = &m_front;
	Node * otherCurr = other.m_front;
	if (m_front != nullptr || other.m_front == nullptr) {
		deleteAll(m_front);
		delete m_front;
		m_front = nullptr;
	}
	for (size_t i = 0; i < otherSize; ++i) {
		try {
			*curr = new Node(otherCurr->data());
		} catch (bad_alloc & ex) {
			delete curr;
			cerr << "Allocation error!\n";
		}
		curr = &((*curr)->m_next);
		otherCurr = otherCurr->m_next;
	}
	try {
		*curr = new Node(otherCurr->data());
	} catch (bad_alloc & ex) {
		delete *curr;
		*curr = nullptr;
		cerr << "Allocation error!" << endl;
	}
	m_back = *curr;
}

void NodeQueue::deleteAll(Node * curr) {
	if (curr->m_next->m_next != nullptr) {
		deleteAll(curr->m_next);
	}
	delete curr->m_next;
	curr->m_next = nullptr;
}


NodeQueue::~NodeQueue()
{
	cout << "NodeQueue Destructor" << endl;
	if (m_front != nullptr)
		deleteAll(m_front);
	delete m_front;
}

NodeQueue & NodeQueue::operator=(const NodeQueue &rhs)
{
	cout << "NodeQueue operator=" << endl;
	if (this != &rhs) {
		size_t rhsSize = rhs.empty() ? 0 : rhs.size()-1;
		Node ** curr = &m_front;
		Node * otherCurr = rhs.m_front;
		if (m_front != nullptr || rhs.m_front == nullptr) {
			//checking rhs for nullptr is kind of redundant b/c we already check for that when we initialize rhsSize
			deleteAll(m_front);
			delete m_front;
			m_front = nullptr;
		}
		for (size_t i = 0; i < rhsSize; ++i) {
			try {
				*curr = new Node(otherCurr->data());
			} catch (bad_alloc & ex) {
				delete curr;
				cerr << "Allocation error!\n";
			}
			curr = &((*curr)->m_next);
			otherCurr = otherCurr->m_next;
		}
		if (rhs.m_back != nullptr) {
			try {
				*curr = new Node(otherCurr->data());
			} catch (bad_alloc & ex) {
				delete *curr;
				*curr = nullptr;
				cerr << "Allocation error!" << endl;
			}
		}
		m_back = *curr;
	}
	return *this;
}

//always use an if statement before using front()
DataType & NodeQueue::front()
{
	cout << "NodeQueue front()" << endl;
	return m_front->data();
}

const DataType & NodeQueue::front() const
{
	cout << "NodeQueue front()" << endl;
	return m_front->data();
}


//put an if statement before using back() as well
DataType & NodeQueue::back()
{
	cout << "NodeQueue back()" << endl;
	return m_back->data();
}

const DataType & NodeQueue::back() const
{
	cout << "NodeQueue back()" << endl;
	return m_back->data();
}

void NodeQueue::push(const DataType &value)
{
	cout << "NodeQueue push()" << endl;
	try {
		m_back->m_next = new Node(value);
	} catch (bad_alloc) {
		delete m_back->m_next;
		m_back->m_next = nullptr;
		cerr << "Allocation error!" << endl;
	}
	m_back = m_back->m_next;
}


void NodeQueue::pop()
{
	cout << "NodeQueue pop()" << endl;
	Node * temp = m_front->m_next;
	if (m_front == m_back) {
		delete m_front;
		m_front = m_back = nullptr;
	} else if (m_front == nullptr) {
		return;
	} else {
		delete m_front;
		m_front = temp;
	}
}

size_t NodeQueue::size() const
{
	cout << "NodeQueue size()" << endl;
	size_t size = 0;
	Node * curr = m_front;
	while (curr != nullptr) {
		++size;
		curr = curr->m_next;
	}
	return size;
}

bool NodeQueue::empty() const
{
	cout << "NodeQueue empty()" << endl;
	return m_front ? 0 : 1;
}

bool NodeQueue::full() const
{
	cout << "NodeQueue full()" << endl;
	return 0;
}

void NodeQueue::clear()
{
	cout << "NodeQueue clear()" << endl;
	deleteAll(m_front);
	delete m_front;
	m_front = m_back = nullptr;
}

void NodeQueue::serialize(std::ostream &os) const
{
	Node * curr = m_front;
	if (curr == nullptr) {
		cout << "Empty queue." << endl;
	}
	while (curr != nullptr) {
		os << curr->m_data << endl;
		curr = curr->m_next;
	}
}

ostream & operator<<(ostream & os, const NodeQueue & nodeQueue)
{
	nodeQueue.serialize(os);
	return os;
}
