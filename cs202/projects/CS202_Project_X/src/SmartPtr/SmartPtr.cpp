//SmartPtr implementation
#include <SmartPtr/SmartPtr.h>
#include <iostream>
using namespace std;

SmartPtr::SmartPtr() {
    m_ptr = new (nothrow) DataType;
    m_refcount = new (nothrow) size_t;
    if (m_ptr && m_refcount) {
        *m_refcount = 1;
    } else {
        cerr << "Dynamic Allocation failed!" << endl;
    }
    cout << "SmartPtr Default Constructor for new allocation, RefCount = " << *m_refcount << endl;
}

SmartPtr::SmartPtr(DataType *data) {
    m_ptr = data;

    if (data) {
        m_refcount = new (nothrow) size_t(1);
    } else {
        m_refcount = new (nothrow) size_t(0);
    }

    if (m_refcount == nullptr) {
        cerr << "Dynamic Allocation failed!" << endl;
    }

    cout << "SmartPtr Parameterized constructor from data pointer, RefCount = " << *m_refcount << endl;
}

SmartPtr::SmartPtr(const SmartPtr & other) {
    m_ptr = other.m_ptr;

    if (other.m_ptr) {
        m_refcount = other.m_refcount;
        ++(*m_refcount);
    } else {
		m_refcount = new (nothrow) size_t(0);
    }

    if (m_refcount == nullptr) {
        cerr << "Dynamic Allocation failed!" << endl;
    }

    cout << "SmartPtr Copy Constructor, RefCount = " << *m_refcount << endl;
}

SmartPtr::~SmartPtr() {
    if (*m_refcount != 0) {
        --(*m_refcount);
    }

	cout << "SmartPtr Destructor, RefCount = " << *m_refcount << endl;

    if (m_refcount == 0) {
        delete m_ptr;
        delete m_refcount;
    }
}

SmartPtr & SmartPtr::operator=(const SmartPtr &rhs) {
    if (this != &rhs) {
		if (*m_refcount <= 1) {
            delete m_ptr;
            delete m_refcount;
            //gonna delete refcount just to ensure that any existing values of refcount become invalid
        }
        m_ptr = rhs.m_ptr;
        if (rhs.m_ptr) {
            m_refcount = rhs.m_refcount;
            ++(*(rhs.m_refcount));
        } else {
            m_refcount = new (nothrow) size_t(0);
        }

    }
    if (m_refcount == nullptr) {
        cerr << "Dynamic Allocation failed!" << endl;
    }
	cout << "SmartPtr Copy Assignment RefCount = " << *m_refcount << endl;
	return *this;
}

DataType & SmartPtr::operator*() {
    return *m_ptr;
}

DataType * SmartPtr::operator->() {
    return m_ptr;
}


