#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<stack>

using namespace std;

inline double calc(double a, double b, string opt) {
    if (opt == "+") return a + b;
    if (opt == "-") return a - b;
    if (opt == "*") return a * b;
    if (opt == "/") return a / b;
    if (opt == "^") return pow(a, b);
    return 0;
}

inline double calc(double x, string opt) {
    if (opt == "sin(")  return sin(x);
    if (opt == "cos(")  return cos(x);
    if (opt == "-(")    return -x;
    if (opt == "+(")    return x;
    return 0;
}

inline int getRank(string opt) {
    if (opt == "+") return 1;
    if (opt == "-") return 1;
    if (opt == "*") return 2;
    if (opt == "/") return 2;
    if (opt == "^") return 3;
    if (opt == "sin(" || opt == "cos(" || opt == "-(" || opt == "+(") return -11;
    if (opt == "(") return -99;
    return 0;
}

inline void errorExit() {
    cout << "Invalid Input" << endl;
    exit(0);
}
    
inline double parseDouble(string &inputStr, int &pos) {
    bool isStart = true, mode = true;
    double res = 0, base = 1, flg = 1;
    while (isdigit(inputStr[pos]) || inputStr[pos] == '.' || (isStart && (inputStr[pos] == '-' || inputStr[pos] == '+'))) {
        isStart = false;
        switch (inputStr[pos]) {
            case '+':
                break;
            case '-':
                flg = -1;
                break;
            case '.':
                if (!mode) {
                    return (-pos, 0);
                }
                mode = false;
                break;
            default:
                if (mode) {
                    (res *= 10) += inputStr[pos] - '0';
                } else {
                    res += (inputStr[pos] - '0') * (base /= 10);
                }
                break;
        }
        ++ pos;
    }
    return res * flg;
}

inline string parseOprator(string &inputStr, int &pos) {
    
    string tmp = inputStr.substr(pos, 1);
    if (tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^") {
        ++ pos;
        return tmp;
    }
    errorExit();
    return "?";
}

inline void getOprand(string &inputStr, int &pos, stack<double> &oprandStack, stack<string> &opratorStack) {
    bool flg = true;
    while (flg) {
        flg = false;
        string tmpOprtr = inputStr.substr(pos, 4);
        while (pos < inputStr.size() && tmpOprtr == "sin(" || tmpOprtr == "cos(") {
            opratorStack.push(tmpOprtr);
            pos += 4;
            tmpOprtr = inputStr.substr(pos, 4);
            flg = true;
        }
        tmpOprtr = inputStr.substr(pos, 2);
        while (pos < inputStr.size() && tmpOprtr == "-(" || tmpOprtr == "+(") {
            opratorStack.push(tmpOprtr);
            pos += 2;
            tmpOprtr = inputStr.substr(pos, 2);
            flg = true;
        }
        while (pos < inputStr.size() && inputStr[pos] == '(') {
            opratorStack.push("(");
            ++ pos;
            flg = true;
        }
    }
    double tmp = parseDouble(inputStr, pos);
    if (pos < 0) {
        errorExit();
    }
    oprandStack.push(tmp);
    while (inputStr[pos] == ')') {
        ++ pos;
        while (!opratorStack.empty() && getRank(opratorStack.top()) > 0) {
            double oprand2 = oprandStack.top();
            oprandStack.pop();

            double oprand1 = oprandStack.top();
            oprandStack.pop();
            
            double res = calc(oprand1, oprand2, opratorStack.top());
            
            cerr << oprand1 << " " << opratorStack.top() << " " << oprand2 << " = " << res << endl;
            
            oprandStack.push(res);
            opratorStack.pop(); 
        }
        if (opratorStack.empty() || getRank(opratorStack.top()) > 0) {
            errorExit();
        }
        if (getRank(opratorStack.top()) == -11) {
            double oprand = oprandStack.top();
            oprandStack.pop();
            double res = calc(oprand, opratorStack.top());
            cerr << opratorStack.top() << " " << oprand << " ) = " << res << endl;
            oprandStack.push(res);
        }
        opratorStack.pop();
    }
}

inline void eraseSpace(string &s) {
    if (!s.empty()) {
        int pos = 0;
        while((pos = s.find(' ', pos)) != string::npos) {
            s.erase(pos, 1);
        }
        while((pos = s.find('\n', pos)) != string::npos) {
            s.erase(pos, 1);
        }
        while((pos = s.find('\r', pos)) != string::npos) {
            s.erase(pos, 1);
        }
    }
}

inline void work(string inputStr) {
    stack<double> oprandStack;
    stack<string> opratorStack;
    
    if (inputStr == "DEBUGMODE") {
        getline(cin, inputStr);
    }
    
    if (inputStr.size() == 0) {
        cout << 0 << endl;
        return ;
    }
    eraseSpace(inputStr);
    
    if (inputStr[0] == '-' || inputStr[0] == '+') {
        inputStr = "0" + inputStr;
    }
    
    cerr << inputStr << endl;
    
    int len = inputStr.size(), pos = 0, dep = 0;
    
    getOprand(inputStr, pos, oprandStack, opratorStack);
    
    while (pos >= 0 && pos < len) {
        
        string oprator = parseOprator(inputStr, pos);
        if (pos < 0) {
            errorExit();
        }
        
        while (!opratorStack.empty() && getRank(oprator) <= getRank(opratorStack.top())) {
            double oprand2 = oprandStack.top();
            oprandStack.pop();

            double oprand1 = oprandStack.top();
            oprandStack.pop();
                
            double res = calc(oprand1, oprand2, opratorStack.top());
            
            cerr << oprand1 << " " << opratorStack.top() << " " << oprand2 << " = " << res << endl;
            
            oprandStack.push(res);
            opratorStack.pop();
        }
        
        opratorStack.push(oprator);

        getOprand(inputStr, pos, oprandStack, opratorStack);
    }
    
    while (!opratorStack.empty()) {
        if (opratorStack.top() == "(") {
            errorExit();
        }
        double oprand2 = oprandStack.top();
        oprandStack.pop();
        
        double oprand1 = oprandStack.top();
        oprandStack.pop();
        
        double res = calc(oprand1, oprand2, opratorStack.top());
        
        cerr << oprand1 << " " << opratorStack.top() << " " << oprand2 << " = " << res << endl;
        oprandStack.push(res);
        opratorStack.pop();
    }
    
    cout << oprandStack.top();
}

inline void set_file_IO(string name) {
    freopen((name + ".in" ).c_str(), "r", stdin );
    freopen((name + ".out").c_str(), "w", stdout);
}

inline void close_IO(void) {
    fclose(stdin);
    fclose(stdout);
}

int main(int argc, char* argv[]) {
    work(argc>1? string(argv[1]): "notDEBUGMODE");
    return 0;
}

