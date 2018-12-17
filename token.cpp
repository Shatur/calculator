#include "token.h"

#include <iostream>
#include <cmath>

Token::Token(Type type, double value, std::string name) :
    m_type(type),
    m_value(value),
    m_name(std::move(name))
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

int Token::size() const
{
    switch (m_type) {
    case Number:
        if (m_value == 0.0)
            return 1;
        return static_cast<int>(log10(m_value) + 1);
    case Variable:
    case UndefinedVariable:
        return static_cast<int>(m_name.size());
    case Sin:
    case Cos:
    case Ctg:
    case Sec:
        return 3;
    case Tg:
        return 2;
    case Cosec:
        return 5;
    default:
        return 1;
    }

}
