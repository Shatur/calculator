#ifndef PARSEERROR_H
#define PARSEERROR_H

#include <stdexcept>

class ParseError : public std::runtime_error
{
public:
    ParseError(const std::string &what, long position);
    long position() const;

private:
    long m_position;
};

#endif // PARSEERROR_H
