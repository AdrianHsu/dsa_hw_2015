#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <stack>
#include <queue>
#include <string>

using namespace std;

//http://en.cppreference.com/w/c/language/operator_precedence
int op_precedence(string);
bool is_digit(char);
bool is_operator(string);
bool right_associate(string);
bool is_unary_op(string);
double string2Double(const string& );
string double2String(const double& );

void compare(queue< string >&, stack< string >&, const string);
bool input_queue(queue< string > &, const string);
double result(queue< string >);

int main()
{
    //*****the output on those three cases is in the written part*****
    //testcase 1: log( 0.88563 +-0.51537 +-0.17578 + +1.3168+ 0.55399 + 0.58713 -0.59019 - -0.059599* +0.89103)     
    //testcase 2: exp(0.20286 *-0.37746+ -(0.53997) )* log(1.1245 + sin(1.2)) 
    //testcase 3: 2.2568-0.063917+ (( 0.35176- +-1.6603- ( sin( -1.8392+0.16571 + 0.74056- -0.79852* + (sqrt(( 1.1172)+0.66085 +0.066148)* -1.1648+ -0.2666 +-1.309 ) ) ) +( -0.12087 *0.20923* 1.0198 +-0.38495+ -0.85675 ))-1.3074)

    //printf("%lf\n",  log( 0.88563 +-0.51537 +-0.17578 + +1.3168+ 0.55399 + 0.58713 -0.59019 - -0.059599* +0.89103));
    //printf("%lf\n", exp(0.20286 *-0.37746+ -(0.53997) )* log(1.1245 + sin(1.2)) );
    //printf("%lf\n", 2.2568-0.063917+ (( 0.35176- +-1.6603- ( sin( -1.8392+0.16571 + 0.74056- -0.79852* + (sqrt(( 1.1172)+0.66085 +0.066148)* -1.1648+ -0.2666 +-1.309 ) ) ) +( -0.12087 *0.20923* 1.0198 +-0.38495+ -0.85675 ))-1.3074) );

    string input;
    while( getline(cin, input))
    {
        queue< string > my_queue;
        if( input_queue(my_queue, input) )
        {
            printf("Postfix Exp: ");
            queue< string > p_queue = my_queue; //p for print out
            while(!p_queue.empty())
            {
                if( p_queue.front() == "+u")
                    printf("+");
                else if( p_queue.front() == "-u")
                    printf("-");
                else if(is_operator( p_queue.front()))
                    printf("%s", p_queue.front().c_str());
                else
                {
                    double _d = string2Double(p_queue.front());
                    cout << fixed << setprecision(6) << _d;
                }
                p_queue.pop();
                if(!p_queue.empty())
                    printf(" ");
            }
            printf("\n");
            printf("RESULT: %lf\n", result(my_queue));
        }
    }
    return 0;
}
int op_precedence(string str)
{
    if(str == "+u" || str == "-u")
        return 2;

    char op = str[0];
    switch(op)  {

        case '*':
            return 3;
            break;
        case '+': case '-':
            return 4;
            break;
        case '(':
            return 99;
            break;
        default:
            return op - 'A';
            break;
    }
    return 0; //error
}
bool is_digit(char d)
{
    if(d >= '0' && d <= '9')
        return true;
    else
        return false;
}
bool is_operator(string str)
{
    if(str.size() > 1)
    {
        if(str == "+u" || str == "-u" || str == "sin" || str == "cos" ||
                str == "exp" || str == "log" || str == "pow" || str == "sqrt" || str == "fabs")
            return true;
        else
            return false;
    }
    else if(str.size() == 1)
    {
        char op = str[0];
        if(op == '*' ||op == '+' || op == '-')
            return true;
        else
            return false;
    }
    return false;
}
bool right_associate(string op)
{
    if(op == "+u" || op == "-u")
        return true;
    else
        return false;
}
bool is_unary_op(string str)
{
    if(str == "+u" || str == "-u" || str == "sin" || str == "cos" 
            || str == "log" || str == "sqrt" || str == "fabs" || str == "exp")
        return true;
    else
        return false;
}
string double2String(const double& d)
{
    string s;
    stringstream ss(s);
    ss << d;

    return ss.str();
}
double string2Double(const string& str)
{
    istringstream ss(str);
    double d;
    ss >> d;

    return d;
}
void compare(queue< string >& my_queue, stack< string >& op_stack, const string _op) // compare input op with my_queue
{
    if(right_associate(_op))
    {
        while(op_precedence(_op) > op_precedence(op_stack.top()))
        {
            my_queue.push(op_stack.top());
            op_stack.pop();
            if(op_stack.empty())
                break;
        } 
    }
    else
    {    
        while(op_precedence(_op) >= op_precedence(op_stack.top()))
        {
            my_queue.push(op_stack.top());
            op_stack.pop();
            if(op_stack.empty())
                break;
        } 
    }
    return;
}
bool input_queue(queue< string > & my_queue, const string in)
{
    unsigned int i = 0;
    stack < string > op_stack;
    while(i < in.length() )
    {
        //ignore space
        if(in[i] == ' ')
        {
            i++;
            continue;
        }
        //push digit or dot directly
        if(is_digit(in[i]) || in[i] == '.')
        {
            string _double;
            while( (is_digit(in[i]) || in[i] == '.')&& i < in.length())
            {
                _double += in[i];
                i++;
            }
            i--;
            my_queue.push(_double);
        }
        string _op;
        _op += in[i];
        if( _op == "c" || _op == "e" || _op == "l" || _op == "p")
        {
            if(_op == "c")
                op_stack.push("cos");
            else if(_op == "e")
                op_stack.push("exp");
            else if(_op == "l")
                op_stack.push("log");
            else if(_op == "p")
            {
                op_stack.push("pow");
                op_stack.push("(");
            }
            i += 3;
        }
        else if(_op == "s")
        {
            if(in[i + 1] == 'i')
            {
                op_stack.push("sin");
                i += 3;
            }
            else if(in[i + 1] == 'q')
            {
                op_stack.push("sqrt");
                i += 4;
            }
            else
            {
                printf("ERROR\n");
                //return false;
            }
        }else if(_op == "f")
        {
            op_stack.push("fabs");
            i+= 4;
        }        
        if(in[i] == '(')
            op_stack.push("(");
        if(is_operator(_op))
        {
            bool _is_binary = 1;
            if(_op == "+" || _op == "-") //unary
            {   
                if(i == 0) // in[i - 1] might be -1
                {
                    op_stack.push(_op + "u"); 
                    _is_binary = 0;
                }
                else
                {
                    int j = i - 1;
                    while(in[j] == ' ' && j > 0)
                        j--;
                    string tmp; //is_operator receives string, thus not use in[j]
                    tmp += in[j];
                    if(is_operator(tmp) || in[j] == '(' || in[j] == ',') //not consider more tha 1 char operator
                    {   
                        _op += "u"; //to differentiate from binary +, -
                        if(!op_stack.empty())
                            compare(my_queue, op_stack, _op);
                        op_stack.push(_op);
                        _is_binary = 0;
                    }
                }
            }
            if(_is_binary)//binary
            {  
                if(!op_stack.empty())
                    compare(my_queue, op_stack, _op);
                op_stack.push(_op);
            }
        }
        if(in[i] == ',')
        {
            bool flag = 1;
            while(flag)
            {
                if(op_stack.empty())
                {
                    //printf("Error: comma mismatched\n");
                    //return false;
                }
                if(op_stack.top() != "(")
                {
                    my_queue.push(op_stack.top());
                    op_stack.pop();
                }
                else
                {
                    flag = 0;
                    op_stack.pop();
                    if(!op_stack.empty())
                    {
                        string str = op_stack.top();
                        if(str == "pow") //trivial
                        {
                            my_queue.push(op_stack.top());
                            op_stack.pop();
                            op_stack.push("(");
                        }
                    }
                }
            }
        }
        if(in[i] == ')')
        {
            bool flag = 1;
            while(flag)
            {
                if(op_stack.empty())
                {
                    //printf("Error: parentheses mismatched\n");
                    //return false;
                }
                if(op_stack.top() != "(")
                {
                    my_queue.push(op_stack.top());
                    op_stack.pop();
                }
                else
                {
                    flag = 0;
                    op_stack.pop();
                    if(!op_stack.empty())
                    {
                        string str = op_stack.top();
                        if( str == "sin" || str == "cos" || str == "exp" || str == "log" 
                                || str == "pow" || str == "sqrt" || str == "fabs")
                        {
                            my_queue.push(op_stack.top());
                            op_stack.pop();
                        }
                    }
                }
            } 
        }
        i++;
    }
    while(!op_stack.empty())
    {
        //if(op_stack.top() == "(" || op_stack.top() == ")")
        //return false;
        my_queue.push(op_stack.top());
        op_stack.pop();
    } 
    return true;
}
double result(queue< string > my_queue)
{
    stack < double > my_stack;
    while(!my_queue.empty())
    {
        string op = my_queue.front();
        if(is_operator(op))
        {
            my_queue.pop();
            double r_val = my_stack.top();

            my_stack.pop();
            if(is_unary_op(op))
            {
                double result = 0;
                if(op == "+u")
                    result = r_val * (+1);
                else if(op == "-u")
                    result = r_val * (-1);
                else if(op == "sin")
                    result = sin(r_val);
                else if(op == "cos")
                    result = cos(r_val);
                else if(op == "log")
                    result = log(r_val);
                else if(op == "sqrt")
                    result = sqrt(r_val);
                else if(op == "fabs")
                    result = fabs(r_val);
                else if(op == "exp")
                    result = exp(r_val);    
                //else
                //printf("ERROR#1\n");

                my_stack.push(result);
            }
            else //is binary op
            {
                double l_val = my_stack.top();
                double result = 0;
                my_stack.pop();

                if(op == "pow")
                    result = pow(l_val, r_val);
                else
                {
                    switch(op[0])  {
                        case '*':
                            result = l_val * r_val;
                            break;
                        case '+':
                            result = l_val + r_val;
                            break;
                        case '-':
                            result = l_val - r_val;
                            break;
                        default:
                            //printf("ERROR#2\n");
                            break;
                    }
                }
                my_stack.push(result);
            }
        }
        else
        {
            my_stack.push( string2Double( my_queue.front() ) );
            my_queue.pop();
        }
    }
    return my_stack.top();
}
