#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H

//used in BST and BNT
#include <stdexcept>
#include <string>

//uses the same structure as PrecondViolatedExcept
class NotFoundException : public std::out_of_range
{
	public:
		explicit NotFoundException(const std::string& message = "") : std::out_of_range(message.c_str()) {}

		virtual ~NotFoundException() noexcept = default;
};

#endif // NOTFOUNDEXCEPTION_H
