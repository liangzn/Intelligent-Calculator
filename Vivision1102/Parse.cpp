
#include "Parse.h"

#include "Expression.h"

using namespace std;

// We love our operators.  Order here determines precedence.
const string operators = "+-*/";

// Clean those dirty tokens
string clean(const string& token)
{
	string result;
	string whitespace = " \n\t";
	for (int i = 0; i < token.length(); i++)
	{
		if (whitespace.find(token[i]) == string::npos)
		{
			result.push_back(token[i]);
		}
	}

	return result;
}

// Takes a string and splits it into tokens
vector<string> lex(const string& input)
{
	vector<string> tokens;
    
    if (input == "")
        return tokens;

	string token;
	for (int i = 0; i < input.length(); i++)
	{
        // Search brackets and extract chars inside as a token (like "5+4").
        if (input[i] == '(')
        {
            // Count the numbers of left and right brackets.
            int num_left = 0;
            int num_right = 0;
            ++i;
            while (i < input.length())
            {
                if (input[i] == ')')
                {
                    // It means a complete expression.
                    if (num_left == num_right)
                    {
                        tokens.push_back(token);
                        token.clear();
                        break;
                    }
                    else
                    {
                        num_right++;
                        token.push_back(input[i]);
                    }
                }
                else if (input[i] == '(')
                {
                    num_left++;
                    token.push_back(input[i]);
                }
                else
                {
                    token.push_back(input[i]);
                }
                i++;
            }
            continue;
        }
        
        
		if (operators.find(input[i]) != string::npos)
		{
			// Add any token we've created so far
			if (token.length())
			{
				tokens.push_back(token);
				token.clear();
			}
            
            // Add this operator as a separate token
            token.push_back(input[i]);
            tokens.push_back(token);
            token.clear();
		}
		else
		{
			// Grow the current token
			token.push_back(input[i]);
		}
	}

	// Any stragglers?
	if (token.length())
	{
		tokens.push_back(token);
	}
    
    //Check whether M is a store command.
    string last = tokens[tokens.size()-1];
    if (last[last.size()-1] == 'M' && last.length() > 1 && last[last.size()-2] >= '0' && last[last.size()-2] <= '9')
    {
        tokens[tokens.size()-1].pop_back();
        store_enable = true;
    }
    
    string se_last = tokens[tokens.size()-2];
    if (last == "M" && se_last[se_last.size()-1] >= '0' && se_last[se_last.size()-1] <= '9') {
        tokens.pop_back();
        store_enable = true;
    }
    if (last == "M" && se_last[se_last.size()-1] == ')') {
        tokens.pop_back();
        store_enable = true;
    }

	return tokens;
}

// Constants
Expression* constantExpression(float rValue)
{
	ConstantExpression* result = new ConstantExpression;
	result->value = rValue;
	return result;
}

// Parse given a left, right, and op
Expression* parseBinary(const vector<string>& tokens, string op, int begin, int index , int end)
{
	BinaryExpression* result = 0;
	if (op == "+")
	{
		result = new BinaryPlus;
	}
    if (op == "-")
    {
        result = new BinaryMinus;
    }
    if (op == "*")
    {
        result = new BinaryMultiply;
    }
	else if (op == "/")
	{
		result = new BinaryDivide;
	}

	result->left = parse(tokens, begin, index-1);
	result->right = parse(tokens, index+1, end);
	return result;
}

// Parse using a given subdivision operator
Expression* splitAndParseBinary(const vector<string>& tokens, string op, int begin, int end)
{
	for (int i = end; i >= begin; i--)  // Traverse reversely because of First-In-Last-Calculate
	{
		if (tokens[i] == op)
		{
			return parseBinary(tokens, op, begin, i, end);
		}
	}

	return 0;
}

// Takes a list of tokens and returns the expression tree
Expression* parse(const vector<string>& tokens, int begin, int end)
{
    // Check whether it is a constant.
    if (begin > end)
    {
        return constantExpression(0.0f);
    }
    else if (begin == end)
    {
        string temp = tokens[begin];
        
        // Check whether it is an expression.
        for (int i = 0; i < temp.size()-1; i++)
        {
            if (operators.find(temp[i]) != string::npos)  // Check whether temp is an expression
            {
                vector<string> t_tokens = lex(temp);
                return parse (t_tokens, 0, (int)t_tokens.size()-1);
            }
        }
        
        if (temp == "M")
            return constantExpression(MValue);
        else
            return constantExpression((float)stof(temp));
    }
    
	// The order of these operators determines the precedence
	for (int i = 0; i < operators.length(); i++)
	{
		string op;
		op.push_back(operators[i]);
		Expression* result = splitAndParseBinary(tokens, op, begin, end);
		if (result)
		{
			return result;
		}
	}
    
    return 0;
}

Expression* myParse(const string& input)
{
    // Clean first.
    string clean_input = clean(input);
    
    // Start to split.
    vector<string> tokens = lex(clean_input);
    
    // Parse, and split recursively if a token is an expression.
    Expression* result = parse (tokens, 0, (int)tokens.size()-1);
    
    return result;
}
