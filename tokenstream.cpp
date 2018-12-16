#include "tokenstream.h"

#include <iostream>

using namespace std;

TokenStream::TokenStream(const std::string &expression) :
    m_stream(expression)
{
}

Token TokenStream::get()
{
    if (m_stream.tellg() == -1)
        return Token(Token::Null);

    char token;
    m_stream >> token;

    switch (token) {
    case '(':
        return Token(Token::LeftBrace);
    case ')':
        return Token(Token::RightBrace);
    case '+':
        return Token(Token::Plus);
    case '-':
        return Token(Token::Minus);
    case '*':
        return Token(Token::Multiplication);
    case '/':
        return Token(Token::Division);
    case '%':
        return Token(Token::DivisionRemainder);
    case ',':
        return Token(Token::Delimeter);
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        double value;
        m_stream.unget();
        m_stream >> value;
        return Token(Token::Number, value);
    }
    default:
        if (isalpha(token)) {
            string text;
            m_stream.unget();
            m_stream >> text;

            // Constants
            if (text.substr(0, 1) == "e") {
                m_stream.seekg(1 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Variable, 2.7182818284590452, "e");
            }
            if (text.substr(0, 2) == "pi") {
                m_stream.seekg(2 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Variable, 3.1415926535897932, "pi");
            }

            // Trigonometric functions
            if (text.substr(0, 3) == "sin") {
                m_stream.seekg(3 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Sin);
            }
            if (text.substr(0, 3) == "cos") {
                m_stream.seekg(3 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Cos);
            }
            if (text.substr(0, 2) == "tg") {
                m_stream.seekg(2 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Tg);
            }
            if (text.substr(0, 3) == "ctg") {
                m_stream.seekg(3 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Ctg);
            }
            if (text.substr(0, 3) == "sec") {
                m_stream.seekg(3 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Sec);
            }
            if (text.substr(0, 5) == "cosec") {
                m_stream.seekg(5 - static_cast<int>(text.size()), std::ios_base::cur);
                return Token(Token::Cosec);
            }

            // Return string
            m_stream.seekg(-static_cast<int>(text.size()), std::ios_base::cur);
        }

        return Token(Token::Null);
    }
}

void TokenStream::unget(int count)
{
    m_stream.seekg(-count, std::ios_base::cur);
}

long TokenStream::position()
{
    return m_stream.tellg();
}
