#ifndef TOKEN_H
#define TOKEN_H

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

    explicit Token(Type type, double value = 0);

    Type type() const;
    void setType(const Type &type);

    double value() const;
    void setValue(double m_value);

private:
    Type m_type;
    double m_value;
};

#endif // TOKEN_H
