/*
    文件名称：calculator-end
    项目名称：calculator
    创建者：黄剑锋 3180102762 
    创建时间：2019.10.17
    最后修改时间：2019.10.23
    程序目的：从命令行中获取表达式，进行计算，将答案输出至命令行
    使用的主要数据结构：栈 
*/

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<stack>

using namespace std;

/*
    函数名称：calc
    函数功能描述：返回用给定二元算子opt对两操作数a, b进行运算的结果，包括 + - * / ^ 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：运算结果 res = a opt b 
    函数的输入参数： 操作数a, b，算子opt 
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/

inline double calc(double a, double b, const string &opt) {
    if (opt == "+") return a + b;
    if (opt == "-") return a - b;
    if (opt == "*") return a * b;
    if (opt == "/") return a / b;
    if (opt == "^") return pow(a, b);
    return 0;
}

/*
    函数名称：calc
    函数功能描述：返回用给定一元算子opt对操作数x进行运算的结果，包括 sin( cos( -( +( 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：运算结果 res = opt x 
    函数的输入参数： 操作数x，算子opt 
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/

inline double calc(double x, const string &opt) {
    if (opt == "sin(")  return sin(x);
    if (opt == "cos(")  return cos(x);
    if (opt == "-(")    return -x;
    if (opt == "+(")    return x;
    return 0;
}

/*
    函数名称：getRank 
    函数功能描述：获取算子opt的优先级，包括 + - * / ^ sin( cos( -( +( ( 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：算子opt的优先级
    函数的输入参数：算子opt 
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

inline int getRank(const string &opt) {
    if (opt == "+") return 1;
    if (opt == "-") return 1;
    if (opt == "*") return 2;
    if (opt == "/") return 2;
    if (opt == "^") return 3;
    if (opt == "sin(" || opt == "cos(" || opt == "-(" || opt == "+(") return -11;
    if (opt == "(") return -99;
    return 0;
}

/*
    函数名称：errorExit 
    函数功能描述：当输入无效时，在命令行中输出 "Invalid Input"，并退出程序。 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：
    函数的输入参数：
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

inline void errorExit() {
    cout << "Invalid Input" << endl;
    exit(0);
}
    
/*
    函数名称：parseDouble
    函数功能描述：解析字符串inputStr从第pos位开始的第一个数字，格式为 ( [0-9]*\.?[0.9]* )，同时将pos修改到数字后一位。 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：字符串inputStr从第pos位开始的第一个数字
    函数的输入参数：字符串inputStr，位置pos
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

inline double parseDouble(const string &inputStr, int &pos) {
    bool mode = true;
    double res = 0, base = 1;
    while (isdigit(inputStr[pos]) || inputStr[pos] == '.') {
        switch (inputStr[pos]) {
            case '.':
                if (!mode) {
                    return 0;
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
    return res;
}

/*
    函数名称：parseOperator
    函数功能描述：解析字符串inputStr从第pos位开始的第一个二元算子，包括 + - * / ^，同时将pos修改到算子后一位。 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：字符串inputStr从第pos位开始的第一个算子 
    函数的输入参数：字符串inputStr，位置pos
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

inline string parseOperator(const string &inputStr, int &pos) {
    string tmp = inputStr.substr(pos, 1);
    if (tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^") {
        ++ pos;
        return tmp;
    }
    errorExit();
    return "?";
}

/*
    函数名称：getOperand 
    函数功能描述：解析字符串inputStr从pos位置开始的操作数或一元算子+操作数，并将其入栈到operandStack与operatorStack 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：
    函数的输入参数：字符串inputStr，位置pos，栈operandStack与operatorStack
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

inline void getOperand(const string &inputStr, int &pos, stack<double> &operandStack, stack<string> &operatorStack) {
    bool flg = true;
    while (flg) {
        flg = false;
        string tmpOprtr = inputStr.substr(pos, 4);
        while (pos < inputStr.size() && tmpOprtr == "sin(" || tmpOprtr == "cos(") {
            operatorStack.push(tmpOprtr);
            pos += 4;
            tmpOprtr = inputStr.substr(pos, 4);
            flg = true;
        }
        tmpOprtr = inputStr.substr(pos, 2);
        while (pos < inputStr.size() && tmpOprtr == "-(" || tmpOprtr == "+(") {
            operatorStack.push(tmpOprtr);
            pos += 2;
            tmpOprtr = inputStr.substr(pos, 2);
            flg = true;
        }
        while (pos < inputStr.size() && inputStr[pos] == '(') {
            operatorStack.push("(");
            ++ pos;
            flg = true;
        }
    }
    double tmp = parseDouble(inputStr, pos);
    if (pos < 0) {
        errorExit();
    }
    operandStack.push(tmp);
    while (inputStr[pos] == ')') {
        ++ pos;
        while (!operatorStack.empty() && getRank(operatorStack.top()) > 0) {
            double operand2 = operandStack.top();
            operandStack.pop();

            double operand1 = operandStack.top();
            operandStack.pop();
            
            double res = calc(operand1, operand2, operatorStack.top());
            
            //cerr << operand1 << " " << operatorStack.top() << " " << operand2 << " = " << res << endl;
            
            operandStack.push(res);
            operatorStack.pop(); 
        }
        if (operatorStack.empty() || getRank(operatorStack.top()) > 0) {
            errorExit();
        }
        if (getRank(operatorStack.top()) == -11) {
            double operand = operandStack.top();
            operandStack.pop();
            double res = calc(operand, operatorStack.top());
            //cerr << operatorStack.top() << " " << operand << " ) = " << res << endl;
            operandStack.push(res);
        }
        operatorStack.pop();
    }
}

/*
    函数名称：eraseSpace
    函数功能描述：就地删去字符串s中所有空字符，包括\r \n与空格 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：
    函数的输入参数：字符串s 
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

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

/*
    函数名称：work 
    函数功能描述：求解表达式字符串inputStr并在命令行中输出答案 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：
    函数的输入参数：字符串inputStr 
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

inline void work(string inputStr) {
    stack<double> operandStack;
    stack<string> operatorStack;
    
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
    
    //cerr << inputStr << endl;
    
    int len = inputStr.size(), pos = 0;
    
    getOperand(inputStr, pos, operandStack, operatorStack);
    
    while (pos >= 0 && pos < len) {
        
        string curOperator = parseOperator(inputStr, pos);
        if (pos < 0) {
            errorExit();
        }
        
        while (!operatorStack.empty() && getRank(curOperator) <= getRank(operatorStack.top())) {
            double operand2 = operandStack.top();
            operandStack.pop();

            double operand1 = operandStack.top();
            operandStack.pop();
                
            double res = calc(operand1, operand2, operatorStack.top());
            
            //cerr << operand1 << " " << operatorStack.top() << " " << operand2 << " = " << res << endl;
            
            operandStack.push(res);
            operatorStack.pop();
        }
        
        operatorStack.push(curOperator);

        getOperand(inputStr, pos, operandStack, operatorStack);
    }
    
    while (!operatorStack.empty()) {
        if (operatorStack.top() == "(") {
            errorExit();
        }
        double operand2 = operandStack.top();
        operandStack.pop();
        
        double operand1 = operandStack.top();
        operandStack.pop();
        
        double res = calc(operand1, operand2, operatorStack.top());
        
        //cerr << operand1 << " " << operatorStack.top() << " " << operand2 << " = " << res << endl;
        operandStack.push(res);
        operatorStack.pop();
    }
    
    cout << operandStack.top();
}

/*
    函数名称：main 
    函数功能描述：从命令行参数获取待求值表达式，调用work()求解 
    函数调用之前的预备条件：
    返回后的处理：
    返回值（如果有的话）：
    函数的输入参数：表达式（作为命令行参数） 
    函数的输出参数：
    函数的算法：
    函数与其他对象中函数的调用和被调用关系：
*/ 

int main(int argc, char* argv[]) {
    work(argc>1? string(argv[1]): "notDEBUGMODE");
    return 0;
}

