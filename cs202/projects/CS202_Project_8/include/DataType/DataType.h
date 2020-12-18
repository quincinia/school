/**
 * @brief  CS-202 DataType class Declaration
 * @author Christos Papachristos (cpapachristos@unr.edu)
 *
 * This file contains a sample declaration for a general DataType class for the purposes of CS-202.
 */
 
#ifndef DATATYPE_H_
#define DATATYPE_H_

#include <iostream>

class DataType{

friend std::ostream & operator<<(std::ostream & os, const DataType & dataType);
friend std::istream & operator>>(std::istream & is, DataType & dataType);

  public:
    DataType();
    DataType(int intVal, double doubleVal);
	DataType(const DataType & other);
	
    bool operator==(const DataType & rhs) const;
    DataType & operator= (const DataType & rhs);
    
    const int & intVal() const;  // allows read-only (e.g. getter) access in const-qualified context
    int & intVal();  // allows read - and - write (e.g. setter / getter) access in non-const-qualified context
    const double & doubleVal() const;  // allows read-only (e.g. getter) access in const-qualified context
    double & doubleVal();  // allows read - and - write (e.g. setter / getter) access in non-const-qualified context

  private:
    int m_intVal;
    double m_doubleVal;
};

#endif //DATATYPE_H_
