#ifndef INCLUDED_EXPRESSION_H
#define INCLUDED_EXPRESSION_H

#include <list>

class Expression
{
public:
	virtual ~Expression() {};

	virtual float evaluate() = 0;
};

class ConstantExpression : public Expression
{
public:
	float evaluate();

	float value;
};

class BinaryExpression : public Expression
{
public:
	BinaryExpression();
	~BinaryExpression();

	Expression* left;
	Expression* right;
};

class BinaryPlus : public BinaryExpression
{
public:
    float evaluate();
};

class BinaryMinus : public BinaryExpression
{
public:
    float evaluate();
};

class BinaryMultiply : public BinaryExpression
{
public:
    float evaluate();
};

class BinaryDivide : public BinaryExpression
{
public:
    float evaluate();
};

#endif
