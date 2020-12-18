#ifndef PRECONDVIOLATEDEXCEPT_H
#define PRECONDVIOLATEDEXCEPT_H
//from Homework #4 Fall 2018 Code Package
#include <stdexcept>
#include <string>

/** @class PrecondViolatedExcep PrecondViolatedExcep.h "PrecondViolatedExcep.h"
 *
 *  Specification for an object thrown on violation of precondition. */
class PrecondViolatedExcept : public std::logic_error {
public:
    explicit PrecondViolatedExcept(const std::string& message = "");

    virtual ~PrecondViolatedExcept() noexcept = default; //throw();
};

#include "../src/PrecondViolatedExcept.cpp"
#endif // PRECONDVIOLATEDEXCEPT_H
