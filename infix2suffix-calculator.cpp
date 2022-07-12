#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Ari's Group Code

int Operator(char opt) { // A Function which return the priority of the Operator
	if (opt == '^')
		return 3;
	else if ((opt == '/' || opt == '*') || opt == '%')
		return 2;
	else if (opt == '+' || opt == '-')
		return 1;
	else
		return -1;
}
string delspace(string n){ //A Function for removing all whitespaces
  string nospace;
  for(int i = 0; i < n.length(); i++){
    char num = n[i];
    if (!isspace(num)){
      nospace += num;
    }
    else{
      continue; 
    }
  }
  return nospace;
}
string infix2suffix(string n){ //A Function that convert Infix to Suffix
  stack<char> formula;
  string ans;
  string space = " ";
  for(int i = 0 ; i < n.length() ; i++){
    char num = n[i];
    if(isdigit(num) || num == '.'){
      if (isdigit(n[i+1]) || n[i+1] == '.'){     
        ans += num;
      }
      else{
        ans += num + space; 
      }
    }
    else if(num == '('){
      formula.push('('); 
    }
    else if(num == ')') {
      while(formula.top() != '('){
				ans += formula.top() + space;
				formula.pop();
			}
			formula.pop();
		}
    else{
			while(!formula.empty() && Operator(num) <= Operator(formula.top())) {
				ans += formula.top() + space;
				formula.pop();
			}
			formula.push(num);
		}
  }
  while(!formula.empty()) {
		ans += formula.top() + space;
		formula.pop();
	}
  return ans;
}

double evaluate(string n){ //A Function that evaluate the Suffix
  double op1, op2, ans;
  stack<double> calcu;
  int i = 0;
  
  while(i < n.length()){
    char num = n[i];
    if(isspace(num)){
    }
    else if(isdigit(num)){
      double val, front = 0, dec = 0;
      while(isdigit(n[i])){
        front = front * 10 + (n[i] - '0');
        i++;
        if(n[i] == '.'){
          stack<double> Decimal;
          i++;
          while(isdigit(n[i])){
            Decimal.push(n[i]);
            i++;   
          }
          while(!Decimal.empty()){
            dec = (dec + (Decimal.top() - '0')) / 10;
            Decimal.pop();
          }
        }
      }
      val = front + dec;
      calcu.push(val);
    }
    else{ //to calculate
      op2 = calcu.top();
      calcu.pop();
      op1 = calcu.top();
      calcu.pop();
      switch(num){
        case('+'): 
          ans = op1 + op2; 
          calcu.push(ans);
        break;
        
        case('-'): 
          ans = op1 - op2;
          calcu.push(ans);
        break;
        
        case('*'): 
          ans = op1 * op2;
          calcu.push(ans);
        break;
        
        case('/'): 
          ans = op1 / op2;
          calcu.push(ans);
        break;

        case('%'):
          ans = fmod(op1, op2);
          calcu.push(ans);
        break;
        
        case('^'):
          ans = pow(op1, op2);
          calcu.push(ans);
        break;
      }
    }
    i++;
  }
  return ans;
}
int main() {
  string formula;
  char retry;
  
  cout << "Welcome to Infix to Suffix Converter and Calculator" << endl;
  do{   
    cout << "-----------------------------------\n" << endl;
    cout << "Please input the Infix :" << endl; 
    cin >> ws;
    getline(cin, formula);
    formula = delspace(formula); 
    cout << formula << endl;
    cout << "The Suffix/Postfix :" << endl;
    formula = infix2suffix(formula);
    cout << formula << endl;
    cout << "Evaluate :" << endl;
    cout << evaluate(formula) << endl;
    cout << "\nRetry? (y/n) : \t"; 
    cin >> retry;
    cout << endl;
  }while(retry == 'y'|| retry == 'Y');
  cout << "------------ Thank you ------------" << endl;
  
  return 0;
}
