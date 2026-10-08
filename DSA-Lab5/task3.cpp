#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


struct Node {
    int data;          // holds an operator 
    Node* next;
};

class Stack {
private:
    Node* topPtr;

public:
    Stack() { topPtr = NULL; }
    ~Stack() { clear(); }

    bool isEmpty() { return topPtr == NULL; }

    void push(int v) {
        Node* n = new Node;
        n->data = v;
        n->next = topPtr;
        topPtr = n;
    }

    bool pop() {
        if (isEmpty()) return false;
        Node* temp = topPtr;
        topPtr = topPtr->next;
        delete temp;
        return true;
    }

    bool top(int& v) {
        if (isEmpty()) return false;
        v = topPtr->data;
        return true;
    }

    void clear() {
        while (!isEmpty()) pop();
    }
};

Stack opStack;     // used while converting (holds operators and '(')
Stack valStack;    // used while evaluating (holds numbers)

//Helper functions
bool isDigit(char c)    { return c >= '0' && c <= '9'; }
bool isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '%'; }

int precedence(char op) {
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;                       // '(' is lowest
}

//Infix -> Postfix
bool infixToPostfix(string infix, string& postfix) {
    opStack.clear();
    postfix = "";
    int t;
    int len = infix.length();
    int i = 0;

    while (i < len) {
        char ch = infix[i];

        if (ch == ' ') {
            i++;
        }
        else if (isDigit(ch)) {                       // operand: copy the whole number
            while (i < len && isDigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
        }
        else if (ch == '(') {
            opStack.push(ch);
            i++;
        }
        else if (ch == ')') {
            bool found = false;
            while (opStack.top(t)) {
                if (t == '(') { found = true; break; }
                postfix += (char)t;
                postfix += ' ';
                opStack.pop();
            }
            if (!found) { cout << "Error: mismatched parentheses\n"; return false; }
            opStack.pop();                            // remove the '('
            i++;
        }
        else if (isOperator(ch)) {
            while (opStack.top(t) && t != '(' && precedence(t) >= precedence(ch)) {
                postfix += (char)t;
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(ch);
            i++;
        }
        else {
            cout << "Error: invalid character '" << ch << "'\n";
            return false;
        }
    }

    while (opStack.top(t)) {                          // empty the stack
        if (t == '(') { cout << "Error: mismatched parentheses\n"; return false; }
        postfix += (char)t;
        postfix += ' ';
        opStack.pop();
    }

    if (postfix == "") { cout << "Error: empty expression\n"; return false; }
    return true;
}

//Evaluate Postfix
bool evaluatePostfix(string postfix, int& result) {
    valStack.clear();
    int len = postfix.length();
    int i = 0;

    while (i < len) {
        char ch = postfix[i];

        if (ch == ' ') {
            i++;
        }
        else if (isDigit(ch)) {                       // build the number, then push it
            int num = 0;
            while (i < len && isDigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            valStack.push(num);
        }
        else {                                        // operator: pop two numbers
            int a, b;
            if (!valStack.top(b)) { cout << "Error: invalid expression\n"; return false; }
            valStack.pop();
            if (!valStack.top(a)) { cout << "Error: invalid expression\n"; return false; }
            valStack.pop();

            int r = 0;
            if (ch == '+') r = a + b;
            else if (ch == '-') r = a - b;
            else if (ch == '*') r = a * b;
            else {                                    // '/' or '%'
                if (b == 0) { cout << "Error: division by zero\n"; return false; }
                if (ch == '/') r = a / b;
                else r = a % b;
            }
            valStack.push(r);
            i++;
        }
    }

    valStack.top(result);
    valStack.pop();
    if (!valStack.isEmpty()) { cout << "Error: invalid expression\n"; return false; }
    return true;
}

// ---------- Check Operators ----------
void checkOperators(string expr) {
    string operands = "", operators = "", others = "";
    int len = expr.length();
    int i = 0;
    while (i < len) {
        char ch = expr[i];
        if (isDigit(ch)) {
            while (i < len && isDigit(expr[i])) { operands += expr[i]; i++; }
            operands += ' ';
        }
        else {
            if (isOperator(ch)) { operators += ch; operators += ' '; }
            else if (ch != ' ' && ch != '(' && ch != ')') { others += ch; others += ' '; }
            i++;
        }
    }
    cout << "Operands  : " << operands << endl;
    cout << "Operators : " << operators << endl;
    if (others != "") cout << "Invalid characters: " << others << endl;
}

void showPrecedence() {
    cout << "Precedence:\n"
         << "  2 : *  /  %\n"
         << "  1 : +  -\n"
         << "  0 : (\n";
}

// ---------- Run one full test ----------
void runTest(string expr) {
    string postfix;
    int result;
    cout << "Infix   : \"" << expr << "\"\n";
    if (infixToPostfix(expr, postfix)) {
        cout << "Postfix : " << postfix << endl;
        if (evaluatePostfix(postfix, result))
            cout << "Result  : " << result << endl;
    }
    cout << endl;
}

int readInt(string prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        bool ok = !line.empty();
        for (size_t i = 0; i < line.length(); i++)
            if (!isDigit(line[i])) ok = false;
        if (ok) return atoi(line.c_str());
        cout << "Invalid input. Enter a number.\n";
    }
}

//Menu
int main() {
    string expr = "", postfix = "";
    bool converted = false;
    int choice;

    do {
        cout << "\nINFIX TO POSTFIX\n"
             << "1. Read Expression\n"
             << "2. Check Operators\n"
             << "3. Determine Precedence\n"
             << "4. Convert Infix to Postfix\n"
             << "5. Display Postfix Expression\n"
             << "6. Evaluate Postfix Expression\n"
             << "7. Clear Stack\n"
             << "8. Run all test cases\n"
             << "0. Exit\n";
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            cout << "Enter expression: ";
            getline(cin, expr);
            converted = false;
        }
        else if (choice == 2) {
            checkOperators(expr);
        }
        else if (choice == 3) {
            showPrecedence();
        }
        else if (choice == 4) {
            converted = infixToPostfix(expr, postfix);
            if (converted) cout << "Postfix: " << postfix << endl;
        }
        else if (choice == 5) {
            if (converted) cout << "Postfix: " << postfix << endl;
            else cout << "Convert the expression first (option 4).\n";
        }
        else if (choice == 6) {
            int result;
            if (!converted) cout << "Convert the expression first (option 4).\n";
            else if (evaluatePostfix(postfix, result)) cout << "Result = " << result << endl;
        }
        else if (choice == 7) {
            opStack.clear();
            valStack.clear();
            cout << "Stacks cleared.\n";
        }
        else if (choice == 8) {
            string tests[] = { "2 + 3 * 4", "(2 + 3) * 4", "10 + 2 * 6",
                               "(10 + 2) * (6 - 3)", "20 / 5 + 3",
                               "((2 + 3) * (4 - 1)) % 4", "100 - 20 - 5 * 2",
                               "", "(2 + 3", "2 + 3)", "10 / (5 - 5)", "2 +" };
            int n = sizeof(tests) / sizeof(tests[0]);
            for (int i = 0; i < n; i++) runTest(tests[i]);
        }
        else if (choice != 0) {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}