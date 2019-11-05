/*
实现功能：输入命题公式的合式公式，求出公式的真值表，并输出该公式的主合取范式和主析取范式。

输入：命题公式的合式公式

输出：公式的主析取范式和主析取范式，输出形式为：“ mi ∨ mj ; Mi ∧ Mj” ，极小项和 ∨ 符号之间有一个空格，极大项和 ∧ 符号之间有一个空格；
主析取范式和主合取范式之间用“ ; ”隔开，“ ; ”前后各有一个空格。 永真式的主合取范式为 1 ，永假式的主析取范式为 0 。

输入公式的符号说明：

! 非，相当于书面符号中的 “ ¬ ”

& 与，相当于书面符号中的 “ ∧ ”

| 或，相当于书面符号中的 “ ∨ ”

- 蕴含联结词，相当于书面符号中的 “ → ”

+ 等价联结词，相当于书面符号中的 “ ↔ ”

( 前括号

) 后括号


输入：
    a&b
输出：
    m3 ; M0 ∧ M1 ∧ M2

//*/

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <math.h>
#include <map>
#include <vector>
#include <set>

using namespace std;
class Calculate
{
    map<char, int> optPriority;
    string expression;
    string expression_tmp;
    int num_of_variables;
    vector<string> variables;
    map<string, int> dict; //存储变量以及其所代表的值
    int error;             //error == 1, divided by 0; error == 2, expression is wrong
    stack<int> numStack;
    stack<char> optStack;

    int sTOi(int firstindex, int lastindex); //transport expression to number
    string iTOs(int num);                    //translate number to string
    void changeMinus();                      //find '-' and judge if it means minus, if so, change it into '#'

    void pushINTOstack();
    void pushOPT(int index); //push the operation at index into optStack and calculate value if necessary

    void computeAB(char opt); //comput 'a opt b'

    void Error(); //do when error occurs
    int cal();

    void countVariable();
    void assigement(string input);
    void dfs(int level);
    void kernel(string inpug);

public:
    vector<int> output;

    Calculate();
    int start(string expression);
};
Calculate::Calculate()
{
    //this->expression = expression;
    //value = 0;
    error = 0;
    optPriority['('] = 0;
    optPriority['&'] = 1;
    optPriority['|'] = 2;
    optPriority['-'] = 3;
    optPriority['+'] = 4;
    optPriority['!'] = 5;
}
int Calculate::sTOi(int firstindex, int lastindex)
{
    string tmp = expression.substr(firstindex, lastindex - firstindex);
    int num_tmp = 0;
    for (int i = 0; i < (int)tmp.size(); i++)
    {
        num_tmp *= 10;
        num_tmp += tmp[i] - '0';
    }
    return num_tmp;
}
string Calculate::iTOs(int num)
{
    ostringstream s;
    s << num;
    string tmp = s.str();
    return tmp;
}
void Calculate::changeMinus()
{
    if (expression[0] == '-')
        expression[0] = '#';
    for (int i = 1; i < (int)expression.size(); ++i)
    {
        if (expression[i] == '-')
        {
            if (expression[i - 1] == ')')
                continue;
            if (expression[i - 1] >= '0' && expression[i - 1] <= '9')
                continue;
            expression[i] = '#';
        }
    }
    return;
}

void Calculate::computeAB(char opt)
{
    if (numStack.empty()) //not enough number
    {
        if (!error)
            error = 2;
        return;
    }
    if (opt == '!')
    {
        int b = numStack.top();
        numStack.pop();
        if (b == 0)
            b = 1;
        else
            b = 0;
        numStack.push(b);
        return;
    }

    int b = numStack.top();
    numStack.pop();
    if (numStack.empty()) //not enough number
    {
        if (!error)
            error = 2;
        return;
    }
    int a = numStack.top();
    numStack.pop();
    int c = 0;
    switch (opt)
    {
    case '&':
        c = a * b;
        break;
    case '|':
        c = a + b;
        if (c > 1)
            c = 1;
        break;
    case '-':
        if (a == 1 && b == 0)
            c = 0;
        else
            c = 1;
        break;
    case '+':
        if (a == b)
            c = 1;
        else
        {
            c = 0;
        }

        break;
    }
    numStack.push(c);
    return;
}

void Calculate::Error()
{
    if (error == 1)
    {
        cout << "Divide 0.\n";
    }
    else
    {
        cout << "error.\n";
    }
    return;
}

void Calculate::pushOPT(int index)
{
    char opt = expression[index];
    if (opt == '(' || opt == '!')
    {
        optStack.push(opt);
        return;
    }
    else
    {
        if (opt == ')')
        {
            int flag = 1; //mark expression is wrong for there is no '('
            while (!optStack.empty())
            {
                char opt_tmp = optStack.top();
                optStack.pop();
                if (opt_tmp == '(')
                {
                    flag = 0;
                    break;
                }
                computeAB(opt_tmp);
                if (error)
                    return;
            }
            if (flag) //there is no '('
            {
                if (!error)
                    error = 2;
                return;
            }
        }
        else
        {
            if (index)
            {
                if (expression[index - 1] == '(')
                {
                    error = 2;
                    return;
                }
            }
            while (!optStack.empty())
            {
                char opt_tmp = optStack.top();
                optStack.pop();
                if (optPriority[opt] >= optPriority[opt_tmp])
                {
                    if (opt == '^')
                    {
                        optStack.push(opt_tmp);
                        break;
                    }
                    else
                    {
                        if (optPriority[opt] > optPriority[opt_tmp])
                        {
                            optStack.push(opt_tmp);
                            break;
                        }
                    }
                }
                computeAB(opt_tmp);
                if (error)
                {
                    return;
                }
            }
            optStack.push(opt);
        }
    }
    return;
}
void Calculate::pushINTOstack()
{
    for (int i = 0; i < (int)expression.size(); ++i)
    {
        if (expression[i] >= '0' && expression[i] <= '9')
        {
            int j = i;
            for (; expression[j] >= '0' && expression[j] <= '9'; j++)
                ;
            numStack.push(sTOi(i, j));
            i = j - 1;
        }
        else
        {
            pushOPT(i);
        }
        if (error)
            return;
    }
    return;
}
int Calculate::cal()
{
    // changeMinus();
    pushINTOstack();
    while (!optStack.empty())
    {
        if (error)
            break;
        char opt_tmp = optStack.top();
        optStack.pop();
        if (opt_tmp == '(')
        {
            if (!error)
                error = 2;
        }
        computeAB(opt_tmp);
    }
    if ((int)numStack.size() != 1)
    {
        if (!error)
            error = 2;
    }

    if (error)
    {
        Error();
        return 0;
    }
    int value = numStack.top();
    while (!numStack.empty())
    {
        numStack.pop();
    }
    while (!optStack.empty())
    {
        optStack.pop();
    }
    return value;
}

void Calculate::assigement(string input)
{
    int index = input.find('=');
    string tmp = input.substr(0, index);
    if (*(input.end() - 1) == '0')
        dict[tmp] = 0;
    else
        dict[tmp] = 1;
}

void Calculate::dfs(int level)
{
    if (level == this->num_of_variables)
    {
        //计算操作
        kernel(this->expression_tmp);
        return;
    }
    //赋值
    assigement(variables[level] + "=0");
    dfs(level + 1);
    assigement(variables[level] + "=1");
    dfs(level + 1);
    return;
}

void Calculate::kernel(string s)
{
    this->expression = "";
    for (int i = 0; i < (int)s.size(); ++i)
    {
        int j = i;
        while (s[j] >= 'a' && s[j] <= 'z')
        {
            j++;
        }
        string tmp = s.substr(i, j - i);
        if (tmp[0] >= 'a' && tmp[0] <= 'z')
            this->expression += iTOs(dict[tmp]);
        else
            this->expression += tmp;
        if (j < (int)s.size())
            this->expression += s[j];
        i = j;
    }
    output.push_back(cal());
    // cout << *output.end() << endl;
}

int Calculate::start(string s)
{
    this->expression_tmp = s;
    countVariable();
    dfs(0);
    return 0;
}

void Calculate::countVariable()
{
    // cout << this->expression_tmp << endl;
    set<string> variables;
    for (int i = 0, j = 0; i < (int)this->expression_tmp.size(); i = j)
    {
        while (i < this->expression_tmp.size())
        {
            if ((int)this->expression_tmp[i] >= 'a' && this->expression_tmp[i] <= 'z')
                break;
            i++;
        }
        j = i;
        if (i >= this->expression_tmp.size())
            break;
        while (j < (int)this->expression_tmp.size() && (int)this->expression_tmp[j] >= 'a' && this->expression_tmp[j] <= 'z')
        {
            j++;
        }
        string tmp = this->expression_tmp.substr(i, j - i);
        // cout << "i=" << i << ";j=" << j << endl;
        // cout << tmp << endl;
        variables.insert(tmp);
    }
    for (auto it = variables.begin(); it != variables.end(); it++)
    {
        this->variables.push_back(*it);
        // cout << *it << endl;
    }
    this->num_of_variables = variables.size();
    // cout << num_of_variables << endl;
}

int main()
{
    Calculate calculator;
    string input;
    cin >> input;

    if(input.find('1') != input.npos)
    {
        cout << "1" << endl;
        return 0;
    }
    if(input.find('0') != input.npos)
    {
        cout << "0" << endl;
        return 0;
    }

    calculator.start(input);
    string xiqu, hequ;

    for (int i = 0; i < (int)calculator.output.size(); i++)
    {
        // cout << calculator.output[i] << endl;
        if (calculator.output[i] == 0)
        {
            hequ += "M" + to_string(i) + " ∧ ";
        }
        else
        {
            xiqu += "m" + to_string(i) + " ∨ ";
        }
    }
    if (hequ.size() > 0)
        for (int i = 0; i < (int)xiqu.size() - 5; i++)
        {
            cout << xiqu[i];
        }
    else
        cout << "1";
    if ((int)hequ.size() > 0)
    {
        if (xiqu.size() > 0)
        {
            cout << " ; ";
            for (int i = 0; i < (int)hequ.size() - 5; i++)
            {
                cout << hequ[i];
            }
        }
        else
            cout << "0";
    }
    cout << endl;
    return 0;
}