#include "parseerror.h"

ParseError::ParseError(const std::string &what, long position) :
    std::runtime_error(what),
    m_position(position)
{
}

long ParseError::position() const
{
    return m_position;
}
