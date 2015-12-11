//
//  Statement.h
//  Final
//
//  Created by Chris Villegas on 12/10/15.
//  Copyright © 2015 Chris Villegas. All rights reserved.
//

#ifndef Statement_h
#define Statement_h
#include "token.h"

class Statement
{
public:
    Statement(std::vector<Token *> stm);
    Token at(int i);
    int stmSize();
    virtual int SubType();
private:
    int _sType;
    std::vector<Token *> theStatement;
};

// DEFINITIONS
Statement::Statement(std::vector<Token *> stm): theStatement(stm)
{
}

Token Statement::at(int i)
{
    return *(theStatement[i]);
}

int Statement::stmSize()
{
    return theStatement.size();
}

int Statement::SubType()// shell
{
    return -1;
}

/****************************************************************************************************
 *****************************************************************************************************/

class Declaration: public Statement // int/double/char/string
{
public:
    Declaration(std::vector<Token *> stm);
    virtual int SubType();
private:
    int getType();
    int declarationType;
};

// DEFINITIONS
Declaration::Declaration(std::vector<Token *> stm): theStatement(stm)
{
    _sType = 1;
    declarationType = getType();
}

int Declaration::getType()// need 4 types int/double/char/string
{
    /*Chris Sy: assigns the subtype of the first token inserted into the vector which should
     * automatically correspond to this key:
     *                                       "int"    = 1
     *                                       "double" = 2
     *                                       "char"   = 3
     *                                       "string  = 4                                   */
    return at(0).SubType();
}

int Declaration::SubType()
{
    return declarationType;
}

/****************************************************************************************************
 *****************************************************************************************************/

class Assignment: public Statement // var = exp
{
public:
    Assignment(std::vector<Token *> stm);
    virtual int SubType();
private:
    int getType();
    int assignmentType;
};

// DEFINITIONS
Assignment::Assignment(std::vector<Token *> stm): theStatement(stm)
{
    _sType = 2;
    assignmentType = getType();
}

int Assignment::getType()// only one type
{
    return 1;
}

int Assignment::SubType()
{
    return assignmentType;
}

/****************************************************************************************************
 *****************************************************************************************************/

class Selection: public Statement // if/else if/else
{
public:
    Selection(std::vector<Token *> stm);
    virtual int SubType();
private:
    int getType();
    int selectionType;
};

// DEFINITIONS
Selection::Selection(std::vector<Token *> stm): theStatement(stm)
{
    _sType = 3;
    selectionType = getType();
}

int Selection::getType()// needs 3 if/else if/else
{
    /*Chris Sy: Unclear if you mean (if), (else), and (else if). This checks the token in index [0]
     * if it's a subtype "else" then the token in index [1] if it's a subtype "if". If true,
     * then returns type 3 for an "else if" type.
     * Key:
     *      "if" = 1
     *      "else" = 2
     *      "else if" = 3                                                                        */
    if (at(0).SubType() == 2 || at(1).SubType())
    {
        return 3;
    }
    return at(0).SubType();
}

int Selection::SubType()
{
    return selectionType;
}

/****************************************************************************************************
 *****************************************************************************************************/

class Iteration: public Statement // for/while/do
{
public:
    Iteration(std::vector<Token *> stm);
    virtual int SubType();
private:
    int getType();
    int statementType;
};

// DEFINITIONS
Iteration::Iteration(std::vector<Token *> stm): theStatement(stm)
{
    _sType = 4;
    statementType = getType();
}

int Iteration::getType()//needs 3 types for/while/do
{
    /*Chris Sy: assigns the (subtype - 3) of the first token inserted into the vector which should
     * automatically correspond to this key:
     *                                        "while"  = 1
     *                                        "do"     = 2
     *                                        "for"    = 3                                      */
    return (at(0).SubType() - 3);
}

int Iteration::SubType()
{
    return statementType;
}





#endif /* Statement_h */
