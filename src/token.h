#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Type {
        Unknown = -1,
        Empty,

        Number,
        Variable,
        UndefinedVariable,
        Delimeter,

        // Operations
        Assignment,
        LeftBrace,
        RightBrace,
        Plus,
        Minus,
        Multiplication,
        Division,
        DivisionRemainder,
        Exponentiation,

        // Trigonometric functions
        Sin,
        Cos,
        Tg,
        Ctg,
        Sec,
        Cosec,
    };

    Token(Type type, double value = 0, std::string name = "");

    Type type() const;
    void setType(const Type &type);

    double value() const;
    void setValue(double m_value);

    std::string name() const;
    void setName(const std::string &name);

    int size() const;

private:
    Type m_type;
    double m_value;
    std::string m_name;
};

#endif // TOKEN_H
