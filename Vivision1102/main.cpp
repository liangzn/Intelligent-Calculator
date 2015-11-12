
#include "Expression.h"
#include "Parse.h"

#include <iostream>
#include <string>

using namespace std;

float MValue = 0.0f;
bool store_enable = false;

int main(int argc, const char * argv[]) {
    string input;
    
    while (getline(cin, input))
    {
        Expression* expression = myParse(input);
        float rValue = expression->evaluate();
        if (store_enable) {
            MValue = rValue;
            store_enable = false;
        }
        
        printf("%f\n", rValue);
        delete expression;
    }
    
    return 0;
}
