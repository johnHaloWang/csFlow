#ifndef CTOKENIZE_H
#define CTOKENIZE_H
#include <stokenizer.h>

//TYPE KEY: TYPE DECLARATION = 1, KEYWORD = 2, VARNAME = 3, VALUE = 4
//**** OPERATOR = 5, PARENTHESIS = 6, BRACE = 7, END STATEMENT = 8

/*SUB-TYPE KEY:
 *OPERATORS: "+" = 1
 *           "-" = 2
 *           "*" = 3
 *           "/" = 4
 *           "=" = 5
 *           "<" = 6
 *           ">" = 7
 *           "." = 8
 *           "!" = 9
 *
 * KEY WORDS: "if"     = 1
 *            "else"   = 2
 *            "return" = 3
 *            "while"  = 4
 *            "do"     = 5
 *            "for"    = 6
 *            "exit"   = 7
 *
 * PARENTHESIS: "(" = 1
 *              ")" = 2
 *
 * BRACE:       "{" = 1
 *              "}" = 2
 *
 * TYPE DECLAR: "int" = 1
 *              "double" = 2
 *              "char" = 3
 *              "string = 4
*/

class CTokenize
{
public:
    CTokenize();

    CTokenize(const string& s);

    Token* NextToken();

    bool More();

private:
    Token* assessToken(Token& tkn);
    Token* handleAlpha(Token& tkn);
    Token* handleDigit(Token& tkn);
    Token* handleSymbol(Token& tkn);
    bool isDesiredBaseType(Token& tkn);
    bool endOfLine(Token& tkn);
    void initVector();
    bool compareToken(Token& tkn, int vectorRow);

    int _more;
    STokenize _sTkn;    
    std::vector<vector<string>> _charList;
};

CTokenize::CTokenize(const string& s):_sTkn(s)
{
    initVector();
}


Token* CTokenize::NextToken()
{
    Token* returnThis = NULL;
    if (_sTkn.More())
    {
        Token peek = _sTkn.NextToken();

        while(!isDesiredBaseType(peek) && _sTkn.More())
        {
            peek = _sTkn.NextToken();
        }

        if(!_sTkn.More())
        {
            _more = false;
        }
        returnThis = assessToken(peek);
    }
    return returnThis;
}


Token* CTokenize::assessToken(Token& tkn)
{
    enum TYPE {ALPHA = 1, DIGIT = 2, SYMBOL = 3};

    if(tkn.Type() == ALPHA)
    {
        return handleAlpha(tkn);
    }

    if(tkn.Type() == DIGIT)
    {
        return handleDigit(tkn);
    }

    return handleSymbol(tkn);

}

bool CTokenize::isDesiredBaseType(Token& tkn)
{
    enum TYPE {ALPHA = 1, DIGIT = 2, SYMBOL = 3};

    if (tkn.Type() == ALPHA || tkn.Type() == DIGIT || tkn.Type() == SYMBOL)
    {
        return true;
    }
    return false;
}

void CTokenize::initVector()
{
    _charList.push_back(vector<string> {"int", "double", "char", "string"});  //row 0
    _charList.push_back(vector<string> {"if", "else", "return", "while", "do", "for", "exit"}); //row 1
    _charList.push_back(vector<string> {"+", "-", "*", "/", "=", "<", ">", ".", "!"}); //row 2
}

bool CTokenize::compareToken(Token& tkn, int vectorRow)
{
    int size = _charList[vectorRow].size();

    for (int j = 0; j < size; j++)
    {
        if (tkn.TokenString() == _charList[vectorRow][j])
        {
            return true;
        }
    }
    return false;
}

Token* CTokenize::handleAlpha(Token& tkn)
{
    enum TYPE {DECL = 1, KEYWORD = 2, VARNAME = 3};

    if (compareToken(tkn, 0)) //check for declaration
    {
        Declaration* temp = new Declaration(tkn.TokenString(), DECL);
        return temp;
    }
    else if (compareToken(tkn, 1)) //check for key words
    {
        Key_Word* temp = new Key_Word(tkn.TokenString(), KEYWORD);
        return temp;
    }

    VarName* temp = new VarName(tkn.TokenString(), VARNAME);
    return temp;
}

Token* CTokenize::handleDigit(Token& tkn)
{
    enum TYPE {VALUE = 4};

    Value* temp = new Value(tkn.TokenString(), VALUE);
    return temp;
}

Token* CTokenize::handleSymbol(Token& tkn)
{
    enum TYPE {OPERATOR = 5, PARENTH = 6, BRACE = 7, END_STATE = 8};

    if(compareToken(tkn, 2))
    {
        Operator* temp = new Operator(tkn.TokenString(), OPERATOR);
        return temp;
    }
    else if(tkn.TokenString() == "(" || tkn.TokenString() == ")")
    {
        Parenthesis* temp = new Parenthesis(tkn.TokenString(), PARENTH);
        return temp;
    }
    else if(tkn.TokenString() == "{" || tkn.TokenString() == "}")
    {
        Braces* temp = new Braces(tkn.TokenString(), BRACE);
        return temp;
    }
    else if(tkn.TokenString() == ";")
    {
        EndStatement* temp = new EndStatement(tkn.TokenString(), END_STATE);
        return temp;
    }
    return NULL;
}

bool CTokenize::More()
{
    return _more;
}

#endif // CTOKENIZE_H
