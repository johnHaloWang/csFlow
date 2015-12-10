#include "mystring.h"

mString::mString():str_(0),len_(0)
{

}

mString::mString(char* str)
{
    str_=NULL;
    Assign(str);
    len_=strLen(str_);
}

//3*************************************************
mString::mString(const mString& toCopy)
{
    len_=toCopy.len_;
    str_=0;
    Assign(toCopy.str_);
}

mString::~mString()  //?
{
    if(str_)
        delete [] str_;
        str_=0; //justin case :P
}

mString& mString::operator =(const mString& RHS)
{
    if(&RHS==this)
    {
        return *this;
    }

    len_=RHS.len_; //set len_
    delete[] str_; //clear str_ pointer
    str_=NULL; //make sure it's NULL
    Assign(RHS.str_);
    return *this; //return pointer to main
}
//3*************************************************

void mString::shrToFit()
{
    len_=Length();
    if(str_){
        delete[] str_;
    }

    str_=new char[len_+1];
}

int mString::Length() const
{
    int len=0;
    len=strLen(str_);
    return len;
}

void mString::Clear(size_t len)
{
    if(str_){
        delete[] str_;
    }
    str_=new char[len+1];
    len_=len;
}

bool mString::Empty() const
{
    if(str_)
    {
        return false;
    }
    return true;
}

char mString::At(int loc) const //return char at loc
{
    char* pos=str_+loc;
    return *pos;
}

char mString::End() const //return char @ end of str
{
    char* end=str_+len_;
    return *end;
}

int mString::getLen() const
{
    return len_;
}

char* mString::getStr() const
{
    return str_;
}

void mString::Append(mString str, int len) //strncpy
{
    mString hold;
    hold.Assign(str_);
    Clear(len_+len);
    strCpy(str_,hold.str_);
    strnCat(str_,str.str_,len);
}

void mString::pushBack(char ch)
{
    char* ugh=&ch;
    mString chr(ugh);
    Append(chr,1);
}

void mString::Assign(char* str) //strcpy
{
    Clear(strLen(str));
    strCpy(str_,str);
}

void mString::Assign(char* str, int len) //strcpy
{
    Clear(len);
    char* hold=subStr(str,0,len);
    strCpy(str_,hold);
}

void mString::Insert(mString str, int pos)
{
    char* hold=str_;
    Clear(len_+str.len_);

    strnCpy(str_,hold,pos+1);
    strCat(str_,str.str_);
    strCat(str_,hold+pos+1);
}

void mString::Erase(size_t pos, size_t len)
{
    char* hold=str_;
    Clear(len_-len);

    strnCpy(str_,hold,pos);
    strCat(str_,hold+len+1);
}

void mString::Replace(mString &str, int pos, int len)
{
    char* hold=str_;
    Clear(len_);

    strnCpy(str_,hold,pos);
    strnCat(str_,str.str_,len);
    strCat(str_,hold+pos+len);
}

void mString::Swap(mString& str)
{
    mString hold(str_);
    Clear(str.len_);

    Assign(str.str_);
    str.Clear(hold.len_);
    str.Assign(hold.str_);
}

int mString::whatType() const
{
    int type=charType(str_);
    return type;
}

char* mString::cStr()
{
    char *str=NULL;
    strCpy(str,str_);
    return str;
}

mString mString::Copy(size_t pos, size_t len) const
{
    mString copy;
    copy.str_=subStr(str_,pos,len); //the fuck you mean too few arguments?
    copy.len_=copy.Length();
    return copy;
}

char* mString::Find(char ch) const
{
    char* loc=strChr(str_,ch);
    return loc;
}

char* mString::revFind(char ch) const
{
    char* loc=strnChr(str_,ch);
    return loc;
}

char* mString::firstOfS(char* str) const
{
    char *loc=firstOf(str_,str);
    return loc;
}

char* mString::firstNotOfS(char *str) const
{
    char* loc=firstNotOf(str_,str);
    return loc;
}

char* mString::firstNotOfS(int type) const
{
    char *loc=firstNotOf(str_,type);
    return loc;
}

mString mString::Sub(int start, int len) const
{
    char* sub=subStr(str_,start,len);
    return mString(sub);
}


/****************************************
 *
 *  OPERATORS AND FRIENDS
 *
 ****************************************/

//char mString::opertor [](int pos) const
//{
//    char ch=At(pos);
//    return ch;
//}

mString& mString::operator +=(mString str)
{

}

mString& mString::operator ++()
{
    str_++;
    len_=strLen(str_);
    return *this;
}

mString& mString::operator ++(int unused)
{
    str_++;
    len_=strLen(str_);
    return *this;
}

ostream& operator <<(ostream& outs, const mString& str)
{
    outs<<str.str_;
    return outs;
}

istream& operator >>(istream& ins, mString& str)
{
    char hold[100];
    ins>>hold;
    str.Assign(hold); //so doesn't weite over if
            //new is longer than old
    return ins;
}

mString& operator >>(mString& str, char* ch)
{

}






















