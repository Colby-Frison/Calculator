#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <stack>

using namespace std;

// creates vector of the numbers and operators
vector<string> collectParts(string eq) {
    vector<string> parts;
    string num = "";

    for (char c : eq) {
        if(isdigit(c)){
            num += c;
        }
        else {
            parts.push_back(num);
            string s(1,c);
            parts.push_back(s);
            num.clear();
        }
    }
    parts.push_back(num);

    return parts;
}

// apply operation
double eval(double a, double b, string op){
    if(op == "+"){ a += b; }
    else if (op == "-"){ a -= b; }
    else if (op == "*"){ a *= b; }
    else if (op == "/"){ a /= b; }
    return a;
}

// designates priority
int priority(string op){
    if(op == "+"||op == "-")
        return 1;
    if(op == "*"||op == "/")
        return 2;
    return 0;
}

// calculates expression
double calc(string eq) {
    double ans = 0.0;

    // expression to evaluate
    vector<string> parts;

    // stuff for infix evaluation
    stack<string> nums, ops;

    if(eq.size() != 0){
        parts = collectParts(eq);
    }

    for (string part : parts) {
        
        if(part == "(") { // if open par
            ops.push(part);
        }
        else if(isdigit(part[0])) { // if number
            nums.push(part);
        }
        else if(part == ")") { // if closing par
            while(!ops.empty() && (ops.top() != "()"))
            {
                // issue is a null is top is null so when stod is called for a null value a segmentation error is thrown
                // to fix just do a null check 
                double val2 = stod(nums.top());
                nums.pop();
                 
                double val1 = stod(nums.top());
                nums.pop();
                 
                string op = ops.top();
                ops.pop();
                 
                nums.push(to_string(eval(val1, val2, op)));
            }
 
            if(!ops.empty()){
                ops.pop(); // pop parenthesis
            }
        }
        else { // if is operator
            while(!ops.empty() && priority(ops.top()) >= priority(part)){
                double val2 = stod(nums.top());
                nums.pop();
                 
                double val1 = stod(nums.top());
                nums.pop();
                 
                string op = ops.top();
                ops.pop();
                 
                nums.push(to_string(eval(val1, val2, op)));
            }
             
            // Push current token to 'ops'.
            ops.push(part);
        }
    }

    while(!ops.empty()){
        double val2 = stod(nums.top());
        nums.pop();
                 
        double val1 = stod(nums.top());
        nums.pop();
                 
        string op = ops.top();
        ops.pop();
                 
        nums.push(to_string(eval(val1, val2, op)));
    }
     
    return stod(nums.top());
}



int main() {

    string input;

    cout << "Enter equation" << endl;
    cin >> input;

    cout << "Answer: " << calc(input) << endl;


    return 0;
}