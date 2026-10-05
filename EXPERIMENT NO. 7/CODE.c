#include <stdio.h>
#define size 80

struct stack
{
    double s[size];
    int top;
} st;

void push(double);
double pop(void);
double post(char []);

int main()
{
    char expr[size];
    int len;
    double result;

    printf("\nEnter a postfix expression : ");
    scanf("%s", expr);

    len = strlen(expr);
    expr[len] = '$';
    expr[len + 1] = '\0';

    result = post(expr);
    printf("\nThe value of the expression is %f\n", result);
    return 0;
}

double post(char expr[])
{
    char ch;
    char *type = "";
    double result = 0, val, op1, op2;
    int i;

    st.top = -1;
    i = 0;
    ch = expr[i];

    while (ch != '$')
    {
        type = "";
        if (ch >= '0' && ch <= '9')
            type = "operand";
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
            type = "operator";

        if (strcmp(type, "operand") == 0)
        {
            val = ch - 48;
            push(val);
        }
        else if (strcmp(type, "operator") == 0)
        {
            op2 = pop();
            op1 = pop();

            switch (ch)
            {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': result = pow(op1, op2); break;
            }
            push(result);
        }
        i++;
        ch = expr[i];
    }
    result = pop();
    return result;
}

void push(double val)
{
    if (st.top >= size - 1)
    {
        printf("\n Stack full");
        return;
    }
    st.top++;
    st.s[st.top] = val;
}

double pop(void)
{
    double val;
    if (st.top == -1)
    {
        printf("\n Stack is empty");
        return 0;
    }
    val = st.s[st.top];
    st.top--;
    return val;
}
