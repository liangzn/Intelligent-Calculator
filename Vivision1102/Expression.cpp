
#include "Expression.h"

float ConstantExpression::evaluate()
{
	return value;
}

BinaryExpression::BinaryExpression()
:	left(0),
	right(0)
{
}

BinaryExpression::~BinaryExpression()
{
	delete left;
	delete right;
}

float BinaryPlus::evaluate()
{
    return left->evaluate() + right->evaluate();
}

float BinaryMinus::evaluate()
{
    return left->evaluate() - right->evaluate();
}

float BinaryMultiply::evaluate()
{
    return left->evaluate() * right->evaluate();
}

float BinaryDivide::evaluate()
{
    return left->evaluate() / right->evaluate();
}