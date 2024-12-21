#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

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

// calculates expression
double calculate(string eq) {
    double ans = 0.0;
    vector<string> parts;
    queue<string> operation;

    if(eq.size() != 0){
        parts = collectParts(eq);
    }

    for (string part : parts) {
        if(part == "+" || part == "-" || part == "*" || part == "/") {
            operation.push(part);
        }
        else {
            if(ans == 0.0){
                ans += stod(part);
            }
            else {
                 string op = operation.front();
                operation.pop();
                if(op == "+"){ ans += stod(part); }
                else if (op == "-"){ ans -= stod(part); }
                else if (op == "*"){ ans *= stod(part); }
                else if (op == "/"){ ans /= stod(part); }
                else { cout << "erm" << endl; }
            }
        }

    }
    return ans;
}



int main() {

    string input;

    cout << "Enter equation" << endl;
    cin >> input;

    cout << "Answer: " << calculate(input) << endl;


    return 0;
}