#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "token.h"

#include <sstream>
#include <map>

class TokenStream
{
public:
    TokenStream(const std::string &expression);

    Token get();
    void unget();
    long position();

private:
    std::stringstream m_stream;
};

#endif // TOKENSTREAM_H
