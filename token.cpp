#include "token.h"

Token::Token():_token(""), _type(6)
{

}

Token::Token(std::string s, int type):_token(s), _type(type)
{

}

Token::Token(const Token& copyMe):_token(copyMe._token), _type(copyMe._type)
{

}

Token& Token::operator =(const Token& copyMe)
{
    if (&copyMe != this)  //check if object is itself
    {
        _token = copyMe._token;
        _type = copyMe._type;
    }

    return *this;
}

std::ostream& operator <<(std::ostream& outs, const Token& printMe)
{
    outs << "[" << printMe._token << " : " << printMe._type << "]";
    return outs;
}

int& Token::Type()
{
    return _type;
}

int Token::SubType()
{
    return -1;
}

std::string& Token::TokenString()
{
    return _token;
}



/****************************************************************************************************
*****************************************************************************************************/

Declaration::Declaration(const std::string& s, int type): Token(s, type)
{
    _declarType = getType();
}

int Declaration::getType()
{
    std::vector<std::string> types = {"int", "double", "char", "string"};
    int size = types.size();

    for (int i = 0; i < size; i++)
    {
        if (TokenString() == types[i])
        {
            return i + 1;
        }
    }
    return -1;
}

int Declaration::SubType()
{
    return _declarType;
}



/****************************************************************************************************
*****************************************************************************************************/


Value::Value(const std::string& s, int type): Token(s, type), _valueType(0)
{

}

int Value::SubType()
{
    return _valueType;
}



/****************************************************************************************************
*****************************************************************************************************/


VarName::VarName(const std::string& s, int type): Token(s, type), _varNameType(0)
{

}

int VarName::SubType()
{
    return _varNameType;
}


/****************************************************************************************************
*****************************************************************************************************/


Key_Word::Key_Word(const std::string& s, int type): Token(s, type)
{
    _keyWordType = getType();
}

int Key_Word::SubType()
{
    return _keyWordType;
}

int Key_Word::getType()
{
    std::vector<std::string> types = {"if", "else", "return", "while", "do", "for", "exit"};
    int size = types.size();

    for (int i = 0; i < size; i++)
    {
        if (TokenString() == types[i])
        {
            return i + 1;
        }
    }
    return -1;
}


/****************************************************************************************************
*****************************************************************************************************/


Operator::Operator(const std::string& s, int type): Token(s, type)
{
    _operatorType = getType();
}

int Operator::SubType()
{
    return _operatorType;
}

int Operator::getType()
{
    std::vector<std::string> types = {"+", "-", "*", "/", "=", "<", ">", ".", "!"};
    int size = types.size();

    for (int i = 0; i < size; i++)
    {
        if (TokenString() == types[i])
        {
            return i + 1;
        }
    }
    return -1;
}


/****************************************************************************************************
*****************************************************************************************************/


Parenthesis::Parenthesis(const std::string& s, int type): Token(s, type)
{
    _parenthesisType = getType();
}

int Parenthesis::SubType()
{
    return _parenthesisType;
}

int Parenthesis::getType()
{
    if(TokenString() == "(")
    {
        return 1;
    }
    return 2;
}


/****************************************************************************************************
*****************************************************************************************************/


Braces::Braces(const std::string& s, int type): Token(s, type)
{
    _bracesType = getType();
}

int Braces::SubType()
{
    return _bracesType;
}

int Braces::getType()
{
    if(TokenString() == "{")
    {
        return 1;
    }
    return 2;
}


/****************************************************************************************************
*****************************************************************************************************/


EndStatement::EndStatement(const std::string& s, int type): Token(s, type), _endStType(0)
{

}

int EndStatement::SubType()
{
    return _endStType;
}
