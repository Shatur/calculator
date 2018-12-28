#include "tokenstream.h"

#include <iostream>

using namespace std;

TokenStream::TokenStream(const std::string &expression) :  
    m_size(static_cast<int>(expression.size())),
    m_stream(expression)
{
}

Token TokenStream::get()
{
    if (!m_buffer.empty()) {
        const Token token = m_buffer.back();
        m_buffer.pop_back();
        return token;
    }

    char token;
    m_stream >> token;

    if (m_stream.fail())
        return Token(Token::Empty);

    switch (token) {
    case '=':
        return Token(Token::Assignment);
    case ',':
        return Token(Token::Delimeter);
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
    case '^':
        return Token(Token::Exponentiation);
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
        const long position = m_stream.tellg(); // Save position
        m_stream >> value;

        if (!m_stream.fail())
            return Token(Token::Number, value);

        // Restore stream state
        m_stream.clear();
        m_stream.seekg(position);

        // Get number by number
        std::string number;
        while (true) {
            char symbol;
            m_stream >> symbol;
            if (!isdigit(symbol)) {
                m_stream.unget();
                break;
            }

            number += symbol;
        }
        return Token(Token::Number, stoi(number));

    }
    default:
        if (!isalpha(token))
            return Token(Token::Unknown);

        string text;
        m_stream.unget();
        m_stream >> text;

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

        // Search for end of variable (Example: return 's_var1' if text is 's_var1=64')
        unsigned long endOfVariable = text.size(); // End of text by default
        for (unsigned long i = 0; i < text.size(); ++i) {
            const char symbol = text.at(i);
            if (!isdigit(symbol)
                    && !isalpha(symbol)
                    && (symbol != '_' || i == 0)) {
                endOfVariable = i;
                m_stream.seekg(static_cast<int>(endOfVariable - text.size()), std::ios_base::cur);
                break;
            }
        }

        return variable(text.substr(0, endOfVariable));
    }
}

void TokenStream::unget(const Token &token)
{
    m_buffer.push_back(token);
}

long TokenStream::position()
{
    if (m_stream.tellg() == -1)
        return m_size;

    return m_stream.tellg();
}

int TokenStream::size() const
{
    return m_size;
}

Token TokenStream::variable(const string &name) const
{
    for (const auto &[variable, value] : m_variables) {
        if (variable == name)
            return Token(Token::Variable, value, name);
    }

    return Token(Token::UndefinedVariable, 0, name);
}

void TokenStream::setVariable(const string &name, double value)
{
    m_variables.insert({name, value});
}
