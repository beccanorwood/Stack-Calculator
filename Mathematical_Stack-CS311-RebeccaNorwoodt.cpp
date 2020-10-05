//Name: Rebecca Norwood
//Student ID: 200430599
//Email: norwo009@cougars.csusm.edu

//Program: Implement Stacks to evaluate a mathematical expression
//Create two stacks: one for numbers(positive only) and the second for operators
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#define SIZE 100 

using namespace std; 
  
class num_Stack { 
    int top; 
  
public: 
	double a[SIZE];
    num_Stack() { top = -1; } 
    bool push(double x); 
    double pop(); 
    double peek(); 
    bool isEmpty(); 
}; 
  
bool num_Stack::push(double x) 
{ 
    if (top >= (SIZE - 1)) { 
        cout << "Stack Overflow"; 
        return false; 
    } 
    else { 
        a[++top] = x; 
        //cout <<"\n" <<  x << " pushed into number stack\n"; 
        return true; 
    } 
} 
  
double num_Stack::pop() 
{ 
    if (top < 0) { 
        cout << "Number Stack Underflow"; 
        return 0; 
    } 
    else { 
        double x = a[top--]; 
        //cout << "\n" << x << " popped from number stack\n";
        return x; 
    } 
} 
double num_Stack::peek() 
{ 
    if (top < 0) { 
        cout << "Number Stack is Empty"; 
        return 0; 
    } 
    else { 
        double x = a[top]; 
        return x; 
    } 
} 

bool num_Stack::isEmpty() 
{ 
    return (top < 0); 
} 


//===================================================================================================

class operator_Stack { 
    int top; 
  
public: 
    char b[SIZE]; // Maximum size of Stack 
  
    operator_Stack() { top = -1; } 
    bool push(char y); 
    char pop(); 
    char peek(); 
    bool isEmpty(); 
}; 
  
bool operator_Stack::push(char y) 
{ 
    if (top >= (SIZE - 1)) { 
        cout << "Operator Stack Overflow"; 
        return false; 
    } 
    else { 
        b[++top] = y; 
        //cout << "\n" <<  y << " pushed into operator stack\n"; 
        return true; 
    } 
} 
  
char operator_Stack::pop() 
{ 
    if (top < 0) { 
        cout << "Operator Stack Underflow"; 
        return 0; 
    } 
    else { 
        char y = b[top--]; 
        //cout << "\n" << y << " popped from operator stack\n"; 
        return y; 
    } 
} 
char operator_Stack::peek() 
{ 
    if (top < 0) { 
        cout << "\nOperator Stack is Empty"; 
        return 0; 
    } 
    else { 
        char y = b[top]; 
        return y; 
    } 
}

bool operator_Stack::isEmpty() 
{ 
    return (top < 0); 
} 

//=========================================================================================================

//Methods for checking math expression 

int priority(char symbol)
{
	if(symbol == '+' || symbol == '-')
		return 1; 
	if(symbol == '*' || symbol == '/')
		return 2; 
}

double operations(double numA, double numB, char symbol)  
{
	 //return number that organizes operators in order from 1-3
	 //the lower the number, the lower the priority
	 //higher the number, higher priority 
	 
	 switch (symbol){
	 	case('+'):
	 		return numA+numB; 
	 	case('-'):
	 		return numA-numB; 
	 	case('*'):
	 		return numA*numB;
		case('/'):
			return numA/numB;  
		}

}

bool isoperator(char x)
{
	if(x == '+' || x == '-' || x == '/' || x == '*' || x == '(' || x == ')'){
		return true; 
	}
	return false; 
}

bool isNum(char y)
{
	if(y >= '0' && y <= '9'){
		return true; 
	}
	return false; 
}

int expressionSize(const char* exp)
{
	int size = 0;
	
	while (exp[size] != '\0')
		size++; 
		
	return size; 
	
}

bool valid(const char* exp)
{
	string temp_equation(exp); 
	//Loop through each character, if paranthesis aren't matched, there are unrecognized operators, and there 
	// is a zero after the divisor symbol, return false 
	int p_open = 0; 
	int p_closed = 0; 
	
	for(int i = 0; i < temp_equation.length(); i++){
		//Check for mismatched operator and rule out spacing 
		if(!isoperator(temp_equation[i]) && !isNum(temp_equation[i]) && 
			temp_equation[i] != ' ' && temp_equation[i] != '.'){
			cout << "Error: Unrecognized Operator!" << endl; 
			return false; 
		}
		if(isoperator(temp_equation[i])){ //Paranthesis mismatched is based upon equality 
			if(temp_equation[i] == '('){
				p_open++; 
			}
			if(temp_equation[i] == ')'){
				p_closed++; 
			}
			if(temp_equation[i] == '/'){
				int position = i + 1; 
				if(temp_equation[position] == '0'){
					cout << "Error! Division by Zero" << endl; 
					return false; 
				}
			}
		}
	}
	
	if(p_open != p_closed){
		cout << "Error: Mismatched Paranthesis!" << endl; 
		return false; 
	}
	
	return true; 
	
}

double evalExpression(const char* exp)
{

	string temp(exp); 
	//cout << "Size: " <<  equation_size << endl; 
	
	
	operator_Stack operators; //Operators Stack
	num_Stack numbers; //Numbers Stack 
	
	//Need to check each character of equation that has been entered to see if it should be pushed to the number stack or the operator stack
	//Need to check if the expression has been correctly formatted
	//If format is correct, then check order of operands to ensure answer follows mathematical rules: PEMDAS 
	
	//===========================================================
	for(int i = 0; i < temp.length(); i++){ 
		 cout << temp[i]; 
      }
      
      cout << "\n"; 
      
    //===========================================================

	//Check for expression validity      
	if(!valid(exp)){
		return 0; 
	} 
	
	else{
	
	    for(int j = 0; j < temp.length(); j++){
	    	if(isNum(temp[j])){
	    		int number = 0; 
	    		int deci_num = 0; 
	    		//int index = 0; 
	    		while(j < temp.length() && isdigit(temp[j])){
		    			number = (number * 10) + (temp[j] - '0'); 
		    			if(temp[j+1] == '.'){
		    				//Want to continue to next position and check if it's a number 
		    				//index = j + 1; //position of decimal point 
		    				j+=2; //Skip decimal point
		    				while(j < temp.length() && isdigit(temp[j])){
		    					deci_num = (deci_num * 10) + (temp[j] - '0'); 
		    					j++; 
		    					
							}
							string concat = (to_string(number) + "." + to_string(deci_num)); 
							double value = stod(concat); 
							numbers.push(value); 
						}
						if(deci_num == 0){
		    				j++; 
						}

				}
				if(deci_num == 0){
					numbers.push(number);
				}
			}
			else if(isoperator(temp[j])){
					operators.push(temp[j]); 
			}
			else if(temp[j] == '('){
					operators.push(temp[j]); 
				}
			else if(temp[j] == ')'){
					while(operators.peek() != '('){
						double numB = numbers.peek(); 
						numbers.pop(); 
						
						double numA = numbers.peek(); 
						numbers.pop(); 
						
						char op_AB = operators.peek(); 
						operators.pop(); 
						
						numbers.push(operations(numA, numB, op_AB)); 
					}
				}
			}
	}
	
	while(!operators.isEmpty()){
		double numB = numbers.peek(); 
		numbers.pop(); 
		
		double numA = numbers.peek(); 
		numbers.pop(); 
		
		char op_AB = operators.peek(); 
		operators.pop(); 
		
		numbers.push(operations(numA, numB, op_AB));
	}

    return numbers.peek();
    

} 


int main() 
{ 
	//cout << evalExpression("(6+2)*5") << "\n"; 
	cout << "This program evaluates mathematical expressions with positive numbers and includes spacing between characters\n" << endl; 
	
	cout << "Result: " << evalExpression("240.23 + 2 * 6") << "\n" << endl;
	cout << "Result: " << evalExpression("100 + 12.5 * 4") << "\n" << endl;
	cout << "Result: " << evalExpression("3 + 20 / 4") << "\n" << endl;
	cout << evalExpression("(3 + 4") << "\n" << endl; 
	cout << evalExpression("(6-31)/(2+8))") << "\n" << endl; 
	cout << evalExpression("5/0") << "\n" << endl; 
	cout << evalExpression("4^2") << "\n" << endl; 
	
	
    return 0; 
} 

