#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

class CharStack {
private:
    Node* topPtr;

public:
    CharStack() { topPtr = NULL; }
    ~CharStack() { clear(); }

    bool isEmpty() { return topPtr == NULL; }

    void push(char c) {
        Node* n = new Node;
        n->data = c;
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

    bool top(char& c) {
        if (isEmpty()) return false;
        c = topPtr->data;
        return true;
    }

    void display() {
        if (isEmpty()) { cout << "Stack is empty\n"; return; }
        cout << "Stack (top -> bottom): ";
        for (Node* p = topPtr; p != NULL; p = p->next)
            cout << p->data << " ";
        cout << endl;
    }

    void clear() {
        while (!isEmpty()) pop();
    }
};

bool isOpening(char c) { return c == '(' || c == '[' || c == '{'; }
bool isClosing(char c) { return c == ')' || c == ']' || c == '}'; }
bool matches(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool checkBalance(const string& exp, CharStack& s) {
    s.clear();
    for (size_t i = 0; i < exp.length(); i++) {
        char ch = exp[i];
        if (isOpening(ch)) {
            s.push(ch);
        } else if (isClosing(ch)) {
            char t;
            if (!s.top(t)) {
                cout << "extra closing bracket '" << ch << "'\n";
                return false;
            }
            if (!matches(t, ch)) {
                cout<<"mismatch: '" << t << "' closed by '" << ch << "'\n";
                return false;
            }
            s.pop();
        }
    }
    if (!s.isEmpty()) {
        cout << "extra opening bracket(s) left unclosed\n";
        return false;
    }
    cout << "All brackets are balanced\n";
    return true;
}


void runExpression(CharStack& s, const string& exp) {
  
    bool ok = checkBalance(exp, s);
    cout << "Expression: \"" << exp << "\"  ->  "
         << (ok ? "Balanced" : "Not Balanced") <<"\n";
}

int main() {
    CharStack s;
    int choice;
    do {
        cout << "\nSTACK: PARENTHESES CHECKER\n"
             << "1. Push\n"
             << "2. Pop\n"
             << "3. Top\n"
             << "4. IsEmpty\n"
             << "5. Check Balance (enter an expression)\n"
             << "6. Display Stack\n"
             << "7. Clear Stack\n"
             << "8. Run all lab test cases\n"
             << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character

        if (choice == 1) {
            cout << "Enter a character: ";
            string in; getline(cin, in);
            if (in.empty()) cout << "Nothing entered.\n";
            else { s.push(in[0]); cout << "Pushed '" << in[0] << "'\n"; }
        }
        else if (choice == 2) {
            char t;
            if (s.top(t)) { s.pop(); cout << "Popped '" << t << "'\n"; }
            else cout << "Cannot pop: stack is empty.\n";
        }
        else if (choice == 3) {
            char t;
            if (s.top(t)) cout << "Top = '" << t << "'\n";
            else cout << "Stack is empty.\n";
        }
        else if (choice == 4) {
            cout << (s.isEmpty() ? "Stack is empty.\n" : "Stack is NOT empty.\n");
        }
        else if (choice == 5) {
            cout << "Enter expression: ";
            string expr; getline(cin, expr);
            runExpression(s, expr);
        }
        else if (choice == 6) {
            s.display();
        }
        else if (choice == 7) {
            s.clear();
            cout << "Stack cleared.\n";
        }
        else if (choice == 8) {
            string tests[] = { "(A+B)", "{A+[B*C]}", "(A+B]", "((A+B)",
                               "{[()]}", "A+B*C", "([A+B])", "" };
            int n = sizeof(tests) / sizeof(tests[0]);
            for (int i = 0; i < n; i++){

             runExpression(s, tests[i]);
             cout<<endl;
            }
        }
        else if (choice != 0) {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}