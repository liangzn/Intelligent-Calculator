#ifndef INCLUDED_PARSE_H
#define INCLUDED_PARSE_H

#include <string>
#include <vector>

class Expression;

extern float MValue;
extern bool store_enable;

std::vector<std::string> lex(const std::string& input);
Expression* parse(const std::vector<std::string>& tokens, int begin, int end);
Expression* myParse(const std::string& input);

#endif
