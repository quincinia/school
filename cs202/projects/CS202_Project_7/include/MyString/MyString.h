#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

//Class specification
class MyString{
 public:
 MyString(); //(1)
 MyString(const char * str); //(2)
 MyString(const MyString & other); //(3)
 ~MyString(); //(4)
 size_t size() const; //(5)
 size_t length() const; //(6)
 const char * c_str() const; //(7)

 bool operator== (const MyString & other) const; //(8)
 MyString & operator= (const MyString & ); //(9)
 MyString operator+ (const MyString & other_myStr) const; //(10)
 char & operator[] (size_t index); //(11a)
 const char & operator[] (size_t index) const; //(11b)

friend ostream& operator<<(ostream& os, const MyString& myStr); //(12)
 private:
 void buffer_deallocate(); //(13)
 void buffer_allocate(size_t size); //(14)
 char * m_buffer;
 size_t m_size;
};

#endif // MYSTRING_H
