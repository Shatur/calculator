#include "token.h"
#include "tokenstream.h"

#include <iostream>
#include <limits>
#include <cmath>
#include <vector>

using namespace std;

// Grammar
double primary(TokenStream *stream);
double term(TokenStream *stream);
double expression(TokenStream *stream);

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
            vector<double> answers;
            answers.push_back(expression(&stream));

            while (stream.position() != -1) {
                // Get delimeter
                if (stream.get().type() != Token::Delimeter) {
                    stream.unget();
                    throw runtime_error("Unexcepted symbol");
                }

                answers.push_back(expression(&stream));
            }

            cout << "= " << answers.at(0);
            for (unsigned i = 1; i < answers.size(); ++i)
                cout << ", " << answers.at(i);
            cout << endl;
        } catch (exception& error) {
            long position = stream.position();

            // Check for end of expression
            if (position == -1)
                position = static_cast<long>(input.size());

            // Mark error position
            for (int i = 0; i < position + 2; ++i)
                cerr << " ";
            cerr << "^" << endl;

            // Show description
            cerr << error.what() << " at position: " << position + 1 << endl;
        }
    }
}

double primary(TokenStream *stream)
{
    Token token = stream->get();

    switch (token.type()) {
    case Token::LeftBrace:
    {
        double braceExpression = expression(stream);
        token = stream->get();
        if (token.type() != Token::RightBrace)
            throw runtime_error("Excepted brace");
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
    default:
        stream->unget();
        throw runtime_error("Expected number");
    }
}

double term(TokenStream *stream)
{
    double left = primary(stream);
    Token token = stream->get();

    while (true) {
        switch (token.type()) {
        case Token::LeftBrace:
        {
            double braceExpression = expression(stream);
            token = stream->get();
            if (token.type() != Token::RightBrace)
                throw runtime_error("Excepted brace");
            return left * braceExpression;
        }
        case Token::Sin:
            left *= sin(primary(stream));
            token = stream->get();
            break;
        case Token::Cos:
            left *= cos(primary(stream));
            token = stream->get();
            break;
        case Token::Tg:
            left *= tan(primary(stream));
            token = stream->get();
            break;
        case Token::Ctg:
            left *= 1 / tan(primary(stream));
            token = stream->get();
            break;
        case Token::Sec:
            left *= 1 / cos(primary(stream));
            token = stream->get();
            break;
        case Token::Cosec:
            left *= 1 / sin(primary(stream));
            token = stream->get();
            break;
        case Token::Multiplication:
            left *= primary(stream);
            token = stream->get();
            break;
        case Token::Division:
        {
            double right = primary(stream);
            if (right == 0.0)
                throw runtime_error("Division by zero");
            left /= right;
            token = stream->get();
            break;
        }
        case Token::DivisionRemainder:
        {
            double right = primary(stream);
            if (right == 0.0)
                throw runtime_error("Division by zero");
            left = fmod(left, right);
            token = stream->get();
            break;
        }
        case Token::Variable:
            left *= token.value();
            token = stream->get();
            break;
        default:
            stream->unget();
            return left;
        }
    }
}

double expression(TokenStream *stream)
{
    double left = term(stream);
    Token token = stream->get();

    while (true) {
        switch (token.type()) {
        case Token::Plus:
            left += term(stream);
            token = stream->get();
            break;
        case Token::Minus:
            left -= term(stream);
            token = stream->get();
            break;
        default:
            stream->unget();
            return left;
        }
    }
}
