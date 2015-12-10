#ifndef TOKEN_H
#define TOKEN_H
#include <string.h>
#include <iostream>
#include <vector>

class Token
{
public:
    Token();

    Token(std::string s, int type);

    Token(const Token& copyMe); //copy constructor

    friend std::ostream& operator <<(std::ostream& outs, const Token& printMe);

    Token& operator =(const Token& copyMe);  //assignment operator

    int& Type();  //returns token type

    virtual int SubType();

    std::string& TokenString();  //returns the string, _token

private:
    std::string _token;
    int _type;
};


/****************************************************************************************************
*****************************************************************************************************/

class Declaration : public Token
{
public:
    Declaration(const std::string& s, int type);

    virtual int SubType();

private:
    int getType();
    int _declarType;
};

/****************************************************************************************************
*****************************************************************************************************/

class Value : public Token
{
public:
    Value(const std::string& s, int type);

    virtual int SubType();

private:
    int _valueType;
};

/****************************************************************************************************
*****************************************************************************************************/


class Key_Word : public Token
{
public:
    Key_Word(const std::string& s, int type);

    virtual int SubType();
private:
    int getType();
    int _keyWordType;
};



/****************************************************************************************************
*****************************************************************************************************/

class VarName : public Token
{
public:
    VarName(const std::string& s, int type);

    virtual int SubType();

private:
    int _varNameType;
};


/****************************************************************************************************
*****************************************************************************************************/

class Operator : public Token
{
public:
    Operator(const std::string& s, int type);

    virtual int SubType();

private:
    int getType();
    int _operatorType;
};


/****************************************************************************************************
*****************************************************************************************************/


//TYPE KEY: LEFT PARENTHESIS = 1, RIGHT PARENTHESIS = 2

class Parenthesis : public Token
{
public:
    Parenthesis(const std::string& s, int type);

    virtual int SubType();

private:
    int getType();
    int _parenthesisType;
};


/****************************************************************************************************
*****************************************************************************************************/

//TYPE KEY: LEFT BRACES = 1, RIGHT BRACES = 2

class Braces : public Token
{
public:
    Braces(const std::string& s, int type);

    virtual int SubType();

private:
    int getType();
    int _bracesType;
};


/****************************************************************************************************
*****************************************************************************************************/


class EndStatement : public Token
{
public:
    EndStatement(const std::string& s, int type);

    virtual int SubType();

private:
    int _endStType;
};

#endif // TOKEN_H
