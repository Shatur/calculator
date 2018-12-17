#include "tokenstream.h"
#include "parseerror.h"

#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

// Grammar
double primary(TokenStream &stream);
double term(TokenStream &stream);
double expression(TokenStream &stream);
double statement(TokenStream &stream);
vector<double> command(TokenStream &stream);

int main() {
    cout.precision(numeric_limits<double>::max_digits10); // Set max preception

    string input;
    while (cin) {
        cout << "> ";
        getline(cin, input);

        if (input.empty())
            continue;

        if (input == "q")
            return 0;

        TokenStream stream(input);
        try {
            const vector<double> answers = command(stream);

            cout << "= " << answers.at(0);
            for (unsigned i = 1; i < answers.size(); ++i)
                cout << ", " << answers.at(i);
            cout << endl;
        } catch (ParseError& error) {
            // Mark error position
            for (int i = 0; i < error.position() + 1; ++i)
                cerr << " ";
            cerr << "^" << endl;

            // Show information
            cerr << error.what() << " at: " << error.position() << endl;
        }
    }
}

double primary(TokenStream &stream)
{
    Token token = stream.get();

    switch (token.type()) {
    case Token::LeftBrace:
    {
        double braceExpression = expression(stream);
        token = stream.get();
        if (token.type() != Token::RightBrace)
            throw ParseError("Excepted brace", stream.position() + token.size());
        return braceExpression;
    }
    case Token::Sin:
        return sin(primary(stream));
    case Token::Cos:
        return cos(primary(stream));
    case Token::Tg:
        return tan(primary(stream));
    case Token::Ctg:
        return 1 / tan(primary(stream));
    case Token::Sec:
        return 1 / cos(primary(stream));
    case Token::Cosec:
        return 1 / sin(primary(stream));
    case Token::Minus:
        return - primary(stream);
    case Token::Plus:
        return + primary(stream);
    case Token::Variable:
    case Token::Number:
        return token.value();
    case Token::UndefinedVariable:
        throw ParseError("Undefined variable", stream.position() - token.size() + 1);
    default:
        throw ParseError("Expected number", stream.position() + token.size());
    }
}

double term(TokenStream &stream)
{
    double left = primary(stream);
    Token token = stream.get();

    while (true) {
        switch (token.type()) {
        case Token::LeftBrace:
        {
            double braceExpression = expression(stream);
            token = stream.get();
            if (token.type() != Token::RightBrace)
                throw ParseError("Excepted brace", stream.position() + token.size());
            return left * braceExpression;
        }
        case Token::Sin:
            left *= sin(primary(stream));
            token = stream.get();
            break;
        case Token::Cos:
            left *= cos(primary(stream));
            token = stream.get();
            break;
        case Token::Tg:
            left *= tan(primary(stream));
            token = stream.get();
            break;
        case Token::Ctg:
            left *= 1 / tan(primary(stream));
            token = stream.get();
            break;
        case Token::Sec:
            left *= 1 / cos(primary(stream));
            token = stream.get();
            break;
        case Token::Cosec:
            left *= 1 / sin(primary(stream));
            token = stream.get();
            break;
        case Token::Multiplication:
            left *= primary(stream);
            token = stream.get();
            break;
        case Token::Division:
        {
            double right = primary(stream);
            if (right == 0.0)
                throw ParseError("Division by zero", stream.position());
            left /= right;
            token = stream.get();
            break;
        }
        case Token::DivisionRemainder:
        {
            double right = primary(stream);
            if (right == 0.0)
                throw ParseError("Division by zero", stream.position());
            left = fmod(left, right);
            token = stream.get();
            break;
        }
        case Token::Variable:
            left *= token.value();
            token = stream.get();
            break;
        case Token::UndefinedVariable:
            throw ParseError("Undefined variable", stream.position() - token.size() + 1);
        default:
            stream.unget(token);
            return left;
        }
    }
}

double expression(TokenStream &stream)
{
    double left = term(stream);
    Token token = stream.get();

    while (true) {
        switch (token.type()) {
        case Token::Plus:
            left += term(stream);
            token = stream.get();
            break;
        case Token::Minus:
            left -= term(stream);
            token = stream.get();
            break;
        default:
            stream.unget(token);
            return left;
        }
    }
}

double statement(TokenStream &stream) {
    Token token = stream.get();

    switch (token.type()) {
    case Token::UndefinedVariable:
    {
        const Token nextToken = stream.get();
        if (nextToken.type() != Token::Assignment) {
            if (nextToken.type() == Token::Null)
                throw ParseError("Excepted assignment", stream.position() + 1);
            throw ParseError("Excepted assignment", stream.position());
        }

        const double value = expression(stream);
        stream.setVariable(token.name(), value);
        return value;
    }
    case Token::Variable:
    {
        // Try to reassign variable
        const Token nextToken = stream.get();
        if (nextToken.type() == Token::Assignment) {
            const double value = expression(stream);
            stream.setVariable(token.name(), value);
            return value;
        }

        stream.unget(nextToken);
        [[fallthrough]];
    }
    default:
        stream.unget(token);
        return expression(stream);
    }
}

vector<double> command(TokenStream &stream) {
    vector<double> answers;
    answers.push_back(statement(stream)); // Parse first expression

    // Parse other commands
    Token token = stream.get();
    while (token.type() != Token::Null) {
        if (token.type() != Token::Delimeter)
            throw ParseError("Unexcepted symbol", stream.position());

        answers.push_back(statement(stream));
        token = stream.get();
    }

    return answers;
}
