#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "token.h"

#include <sstream>
#include <vector>
#include <map>

class TokenStream
{
public:
    explicit TokenStream(const std::string &expression);

    Token get();
    void unget(const Token &token);
    long position();
    int size() const;

    Token variable(const std::string &name) const;
    void setVariable(const std::string &name, double value);

private:
    int m_size;
    std::vector<Token> m_buffer;
    std::stringstream m_stream;
    std::map<std::string, double> m_variables = {
        {"e", 2.7182818284590452},
        {"pi", 3.1415926535897932}
    };
};

#endif // TOKENSTREAM_H
