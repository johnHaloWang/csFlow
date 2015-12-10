#ifndef STOKENIZER_H
#define STOKENIZER_H
#include <token.h>
#include <cctype>

using namespace std;

class STokenize
{
public:
    STokenize();

    STokenize(const string& s);    

    string NextString(); //gets the next string and not a Token object. moves _pos OF STokenizer the same way as NextToken()

    Token NextToken();  //returns next token from _s

    bool Fail(); //returns !_more

    bool More();    //returns _more

    int Pos();

    friend STokenize& operator >>(STokenize& s, Token& t);

private:
    int GetTokenType(char ch);

    string _s;  //a string to tokenize
    int _pos;  //current position in _s
    int _more;  //true if _pos is less than the length of _s    
};

STokenize::STokenize():_pos(0), _more(true)
{

}

STokenize::STokenize(const string& s):_s(s), _pos(0)
{
    if (!_s.empty())
    {
        _more = true;
    }
    else
    {
        _more = false;
    }
}

int STokenize::GetTokenType(char ch)
{
    enum TYPE {ALPHABET = 1, DIGIT = 2, PUNCTUATION = 3, SPACE = 4, CARRIAGE_RETURN = 5, MYSTERY = 6};

    if(isalpha(ch))
    {
        return ALPHABET; //alphabet
    }

    if (isdigit(ch))
    {
        return DIGIT; //number
    }

    if(ch == '\n')
    {
        return CARRIAGE_RETURN; //carriage return (end of line)
    }

    if (isspace(ch))
    {
        return SPACE;  //space
    }

    if (ispunct(ch))
    {
        return PUNCTUATION; //punctuation
    }

    return MYSTERY; //unknown type
}

string STokenize::NextString()
{
    Token temp = NextToken();

    return temp.TokenString();
}

Token STokenize::NextToken()
{
    string temp;
    int type = 6, len = _s.length();

    if (_more)
    {
        type = GetTokenType(_s[_pos]); //check for the type of the first character

        if (type == 1 || type == 2)
        {
            while ((GetTokenType(_s[_pos]) == type) && (_pos < len)) //if alpha or digit, grab an entire "group" of the same types
            {
                temp.push_back(_s[_pos]);
                _pos++;
            }
        }
        else
        {
            temp.push_back(_s[_pos]); //if not alpha or digit, grab a single character
            _pos++;
        }        
    }

    if (_pos == len)  //check if end of _s has been reached
    {
        _more = false;
    }
    return Token(temp, type);
}

bool STokenize::Fail()
{
    return !(_more);
}

bool STokenize::More()
{
    return _more;
}

int STokenize::Pos()
{
    return _pos;
}

STokenize& operator >>(STokenize& s, Token& t)
{
    t = s.NextToken();
    return s;
}

#endif // STOKENIZER_H
