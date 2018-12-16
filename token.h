#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Type {
        Null = -1,

        Number,
        Variable,

        // Operations
        LeftBrace,
        RightBrace,
        Plus,
        Minus,
        Multiplication,
        Division,
        DivisionRemainder,
        Delimeter,

        // Trigonometric functions
        Sin,
        Cos,
        Tg,
        Ctg,
        Sec,
        Cosec,
    };

    explicit Token(Type type, double value = 0, const std::string name = "");

    Type type() const;
    void setType(const Type &type);

    double value() const;
    void setValue(double m_value);

    std::string name() const;
    void setName(const std::string &name);

    int size();

private:
    Type m_type;
    double m_value;
    std::string m_name;
};

#endif // TOKEN_H
