#include "token.h"

#include <iostream>

Token::Token(Type type, double value) :
    m_type(type),
    m_value(value)
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
