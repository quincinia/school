#include "../../include/MyString/MyString.h"
#include <iostream>
#include <cstring>
#include <cstddef> //for nullptr
using namespace std;



void MyString::buffer_deallocate() {

	delete [] m_buffer;
	m_buffer = nullptr;
	m_size = 0;
}

void MyString::buffer_allocate(size_t size) {
	if (m_buffer != nullptr) {
		buffer_deallocate();
	}

	m_buffer = new char[size+1];
	m_size = size + 1; //not sure if this is needed here
	//m_size represents the size of the buffer, not the size of the string
}

MyString::MyString() :
	m_buffer(nullptr),
	m_size(0)
	{ }

MyString::MyString(const char * str) : MyString() {
	buffer_allocate(strlen(str));
	strcpy(m_buffer, str);
}

MyString & MyString::operator= (const MyString & other) {
	if (this != &other) {
		if (m_buffer != nullptr) {
			buffer_deallocate();
		}
		buffer_allocate(other.length());
		strcpy(m_buffer, other.c_str());
	}
	return *this;
}

MyString::MyString(const MyString & other) : MyString() {
	*this = other;
}

MyString::~MyString() {
	delete [] m_buffer;
}

size_t MyString::size() const {
	return m_size;
}

size_t MyString::length() const {
	return strlen(m_buffer);
}

const char * MyString::c_str() const {
	return m_buffer;
}

bool MyString::operator==(const MyString & other) const {
	if (strcmp(m_buffer, other.c_str()))
		return 0;

	return 1;
}

MyString MyString::operator+(const MyString &other_myStr) const {
	//normally, strcat does break the array limit
	char tempstr[length() + other_myStr.length() + 1];
	strcpy(tempstr, m_buffer);
	strcat(tempstr, other_myStr.c_str());
	MyString tempobj(tempstr);
	return tempobj;
}

char & MyString::operator[](size_t index) {
	//Should not care if the index requested is more than the m_buffer size
	return m_buffer[index];
}

const char & MyString::operator[](size_t index) const {
	return m_buffer[index];
}

ostream& operator<<(ostream& os, const MyString& myStr) {
	os << myStr.c_str() << endl;
	return os;
}
