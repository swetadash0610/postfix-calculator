#include<iostream>
#include <stack>
#include <string>
#include<cctype>
#include<cmath>

using namespace std;

// Class declaration
class Calculate{
    string infix;

    public:
    void setinfix();
    int precedence(char ch);
    string convert_postfix();
    bool IsOperator(char C);
    float operation(char operation, float operand1, float operand2);
    float evaluate();  
};

// Function to get the infix expression
void Calculate:: setinfix(){
       cout<<"Enter your arithmetic expression :\n";
       getline(cin, infix);
    }

// Function to decide the precedence of operators

int Calculate:: precedence(char ch) {
   if(ch == '+' || ch == '-') {
      return 1;
   }else if(ch == '*' || ch == '/') {
      return 2;            
   }else if(ch == '^') {
      return 3;            
   }else {
      return 0;
   }
}

// Function to convert infix expression into postfix

string Calculate::convert_postfix(){
    stack<char> stk;
        stk.push('#'); 
        string postfix = "";
      
   for(int i = 0; i<infix.length(); i++) {
      if(isdigit(infix[i])){
         int operand = 0; 
         while(i<infix.length() && !IsOperator(infix[i])){
            operand = (operand*10) + (infix[i] - '0'); 
            i++;
         }
         i--;
         postfix +=to_string(operand);  
         postfix += " ";  
      }
      else if(infix[i] == '(')
         stk.push('(');
      else if(infix[i] == '^')
         stk.push('^');
      else if(infix[i] == ')') {
         while(stk.top() != '#' && stk.top() != '(') {
            postfix += stk.top(); 
            postfix += " "; 
            stk.pop();
         }
         stk.pop();    
      }else {
         if(precedence(infix[i]) > precedence(stk.top()))
            stk.push(infix[i]); 
         else {
            while(stk.top() != '#' && precedence(infix[i]) <= precedence(stk.top())) {
               postfix += stk.top();      
               postfix += " "; 
               stk.pop();
            }
            stk.push(infix[i]);
         }
      }
   }

   while(stk.top() != '#') {
      postfix += stk.top();     
      postfix += " ";        
      stk.pop();
   }

   return postfix;

}

// Function to verify whether a character is operation symbol or not. 
bool Calculate:: IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '^')
		return true;
	return false;

}

// Function to perform an operation and return output. 
float Calculate:: operation(char operation, float operand1, float operand2)
{
	if(operation == '+') return operand1 +operand2;
	else if(operation == '-') return operand1 - operand2;
	else if(operation == '*') return operand1 * operand2;
	else if(operation == '/') return operand1 / operand2;
	else if(operation == '^') return pow(operand1,operand2);

	else cout<<"Unexpected Error \n";
	return -1; 
}

// Function to evaluate Postfix expression and return output
float Calculate:: evaluate()
{   string expression= convert_postfix(); 
	stack<float> S;

	for(int i = 0;i< expression.length();i++) {
      if(expression[i] == ' ') continue; 
		
		if(IsOperator(expression[i])) {
   
			float operand2 = S.top(); S.pop();
			float operand1 = S.top(); S.pop();
	
			float result = operation(expression[i], operand1, operand2);
			S.push(result);
		}
		else if(isdigit(expression[i])){
         
			float operand = 0; 
			while(i<expression.length() && isdigit(expression[i])) {
			
				operand = (operand*10) + (expression[i] - '0'); 
				i++;
			}
			i--; 
			S.push(operand);
		}
	}
	return S.top();
}  

// Main function
int main() {
   Calculate exp;
   exp.setinfix();
   float result = exp.evaluate();
	cout<<"\nOutput = "<<result<<"\n";
}
