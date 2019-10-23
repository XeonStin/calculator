/*
    �ļ����ƣ�calculator-end
    ��Ŀ���ƣ�calculator
    �����ߣ��ƽ��� 3180102762 
    ����ʱ�䣺2019.10.17
    ����޸�ʱ�䣺2019.10.23
    ����Ŀ�ģ����������л�ȡ���ʽ�����м��㣬���������������
    ʹ�õ���Ҫ���ݽṹ��ջ 
*/

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<stack>

using namespace std;

/*
    �������ƣ�calc
    �������������������ø�����Ԫ����opt����������a, b��������Ľ�������� + - * / ^ 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ����������� res = a opt b 
    ��������������� ������a, b������opt 
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
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
    �������ƣ�calc
    �������������������ø���һԪ����opt�Բ�����x��������Ľ�������� sin( cos( -( +( 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ����������� res = opt x 
    ��������������� ������x������opt 
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
*/

inline double calc(double x, const string &opt) {
    if (opt == "sin(")  return sin(x);
    if (opt == "cos(")  return cos(x);
    if (opt == "-(")    return -x;
    if (opt == "+(")    return x;
    return 0;
}

/*
    �������ƣ�getRank 
    ����������������ȡ����opt�����ȼ������� + - * / ^ sin( cos( -( +( ( 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ���������opt�����ȼ�
    �������������������opt 
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
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
    �������ƣ�errorExit 
    ����������������������Чʱ��������������� "Invalid Input"�����˳����� 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ�����
    ���������������
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
*/ 

inline void errorExit() {
    cout << "Invalid Input" << endl;
    exit(0);
}
    
/*
    �������ƣ�parseDouble
    �������������������ַ���inputStr�ӵ�posλ��ʼ�ĵ�һ�����֣���ʽΪ ( [0-9]*\.?[0.9]* )��ͬʱ��pos�޸ĵ����ֺ�һλ�� 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ������ַ���inputStr�ӵ�posλ��ʼ�ĵ�һ������
    ����������������ַ���inputStr��λ��pos
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
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
    �������ƣ�parseOperator
    �������������������ַ���inputStr�ӵ�posλ��ʼ�ĵ�һ����Ԫ���ӣ����� + - * / ^��ͬʱ��pos�޸ĵ����Ӻ�һλ�� 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ������ַ���inputStr�ӵ�posλ��ʼ�ĵ�һ������ 
    ����������������ַ���inputStr��λ��pos
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
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
    �������ƣ�getOperand 
    �������������������ַ���inputStr��posλ�ÿ�ʼ�Ĳ�������һԪ����+����������������ջ��operandStack��operatorStack 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ�����
    ����������������ַ���inputStr��λ��pos��ջoperandStack��operatorStack
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
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
    �������ƣ�eraseSpace
    ���������������͵�ɾȥ�ַ���s�����п��ַ�������\r \n��ո� 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ�����
    ����������������ַ���s 
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
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
    �������ƣ�work 
    �������������������ʽ�ַ���inputStr����������������� 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ�����
    ����������������ַ���inputStr 
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
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
    �������ƣ�main 
    ���������������������в�����ȡ����ֵ���ʽ������work()��� 
    ��������֮ǰ��Ԥ��������
    ���غ�Ĵ���
    ����ֵ������еĻ�����
    ������������������ʽ����Ϊ�����в����� 
    ���������������
    �������㷨��
    ���������������к����ĵ��úͱ����ù�ϵ��
*/ 

int main(int argc, char* argv[]) {
    work(argc>1? string(argv[1]): "notDEBUGMODE");
    return 0;
}

