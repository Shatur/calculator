#include "token.h"

#include <iostream>
#include <cmath>

Token::Token(Type type, double value, const std::string name) :
    m_type(type),
    m_value(value),
    m_name(name)
{
}

Token::Type Token::type() const
{
    return m_type;
}

void Token::setType(const Type &type)
{
    m_type = type;
}

double Token::value() const
{
    return m_value;
}

void Token::setValue(double value)
{
    m_value = value;
}

std::string Token::name() const
{
    return m_name;
}

void Token::setName(const std::string &name)
{
    m_name = name;
}

int Token::size()
{
    int size = 0;

    switch (m_type) {
    case Number:
        if (m_value == 0.0)
            size = 1;
        else
            size = static_cast<int>(log10(m_value) + 1);
        break;
    case Variable:
        size = static_cast<int>(m_name.size());
        break;
    case Null:
    case LeftBrace:
    case RightBrace:
    case Plus:
    case Minus:
    case Multiplication:
    case Division:
    case DivisionRemainder:
    case Delimeter:
        size = 1;
        break;
    case Sin:
    case Cos:
    case Ctg:
    case Sec:
        size = 3;
        break;
    case Tg:
        size = 2;
        break;
    case Cosec:
        size = 5;
        break;
    }

    return size;
}
