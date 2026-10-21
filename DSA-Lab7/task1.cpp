#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

//Node of the (character) binary tree
struct Node {
    char data;
    Node *left, *right;
    Node(char c) : data(c), left(nullptr), right(nullptr) {}
};

//BUILD TREE FROM STRING(recursive descent parser)
Node* buildTree(const string& s, int& i) {
    // empty subtree  (the left child in "c(,f(g,))")
    if (i >= (int)s.size() || s[i] == ',' || s[i] == ')')
        return nullptr;

    Node* root = new Node(s[i++]);          // read the label

    if (i < (int)s.size() && s[i] == '(') { // has children
        i++;                                // skip '('
        root->left = buildTree(s, i);       // left subtree
        if (i < (int)s.size() && s[i] == ',') i++;  // skip ','
        root->right = buildTree(s, i);      // right subtree
        if (i < (int)s.size() && s[i] == ')') i++;  // skip ')'
    }
    return root;
}

//PREORDER (RECURSIVE)
//plain preorder sequence  
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
//preorder in string form
void preorderString(Node* root) {
    if (!root) return;
    cout << root->data;
    if (root->left || root->right) {        // print brackets only if children exist
        cout << "(";
        preorderString(root->left);
        cout << ",";
        preorderString(root->right);
        cout << ")";
    }
}

//INORDER (ITERATIVE, USING STACK)
void inorderIterative(Node* root) {
    stack<Node*> st;
    Node* cur = root;
    while (cur || !st.empty()) {
        while (cur) {               // go as far left as possible
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top(); st.pop();   // visit
        cout << cur->data << " ";
        cur = cur->right;           // then go right
    }
}

//POSTORDER (ITERATIVE, USING STACK)
//    Uses 'lastVisited' to know when the right subtree is done
void postorderIterative(Node* root) {
    stack<Node*> st;
    Node *cur = root, *lastVisited = nullptr;
    while (cur || !st.empty()) {
        if (cur) {
            st.push(cur);
            cur = cur->left;
        } else {
            Node* top = st.top();
            if (top->right && lastVisited != top->right) {
                cur = top->right;            // right subtree not yet processed
            } else {
                cout << top->data << " ";    // visit node
                lastVisited = top;
                st.pop();
            }
        }
    }
}

//VALIDATE STRING WITHOUT BUILDING THE TREE
//balanced parentheses using a stack
bool balancedParentheses(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') st.push(c);
        else if (c == ')') {
            if (st.empty()) return false;
            st.pop();
        }
    }
    return st.empty();
}
//correct child placement (exactly two slots separated by ',')
// recursive checker: only moves an index, creates no nodes
bool checkTree(const string& s, int& i) {
    // empty slot is allowed (handled by caller), here a label is required
    if (i >= (int)s.size() || !isalnum((unsigned char)s[i])) return false;
    i++;                                         // consume label
    if (i < (int)s.size() && s[i] == '(') {
        i++;
        // left child: may be empty
        if (i < (int)s.size() && s[i] != ',')
            if (!checkTree(s, i)) return false;
        if (i >= (int)s.size() || s[i] != ',') return false;   // need ','
        i++;
        // right child: may be empty
        if (i < (int)s.size() && s[i] != ')')
            if (!checkTree(s, i)) return false;
        if (i >= (int)s.size() || s[i] != ')') return false;   // need ')'
        i++;
    }
    return true;
}

bool validateString(const string& s) {
    if (s.empty() || !balancedParentheses(s)) return false;
    int i = 0;
    return checkTree(s, i) && i == (int)s.size();   // whole string consumed
}

//HEIGHT AND DEPTH (RECURSIVE)
//    Height of a leaf = 0 (counted in edges), depth of root = 0
int height(Node* root) {
    if (!root) return -1;
    return 1 + max(height(root->left), height(root->right));
}

void printDepths(Node* root, int depth = 0) {
    if (!root) return;
    cout << "   Node " << root->data << "  ->  depth = " << depth << "\n";
    printDepths(root->left,  depth + 1);
    printDepths(root->right, depth + 1);
}

//Node of the integer BST
struct BSTNode {
    int data;
    BSTNode *left, *right;
    BSTNode(int v) : data(v), left(nullptr), right(nullptr) {}
};

//BST FROM A SEQUENCE OF INTEGERS
BSTNode* insertBST(BSTNode* root, int v) {
    if (!root) return new BSTNode(v);
    if (v < root->data)      root->left  = insertBST(root->left, v);
    else if (v > root->data) root->right = insertBST(root->right, v);
    return root;                                   // duplicates ignored
}

BSTNode* buildBST(const vector<int>& seq) {
    BSTNode* root = nullptr;                       // first element becomes root
    for (int v : seq) root = insertBST(root, v);
    return root;
}

void inorderBST(BSTNode* root) {
    if (!root) return;
    inorderBST(root->left);
    cout << root->data << " ";
    inorderBST(root->right);
}

//free memory
void freeTree(Node* r)    { if (r) { freeTree(r->left); freeTree(r->right); delete r; } }
void freeBST(BSTNode* r)  { if (r) { freeBST(r->left);  freeBST(r->right);  delete r; } }


// MAIN
int main() {
    string s = "a(b(d,e),c(,f(g,)))";
    cout << "Given string : " << s << "\n\n";

    //Validation first (no tree built)
    cout << "[5] Validate string (without building tree)\n";
    cout << "   \"" << s << "\"        -> " << (validateString(s) ? "VALID" : "INVALID") << "\n";
    vector<string> bad = {"a(b(d,e),c(,f(g,))", "a(b,c,d)", "a(b(d,e)c)", "a(b,c))"};
    for (auto& t : bad)
        cout << "   \"" << t << "\"  -> " << (validateString(t) ? "VALID" : "INVALID") << "\n";

    //Build
    int idx = 0;
    Node* root = buildTree(s, idx);
    cout << "\n[1] Tree built successfully. Root = " << root->data << "\n";

    cout << "\n[2] Preorder (recursive)\n   Sequence : ";
    preorder(root);
    cout << "\n   String   : ";
    preorderString(root);

    cout << "\n\n[3] Inorder (iterative, stack)\n   ";
    inorderIterative(root);

    cout << "\n\n[4] Postorder (iterative, stack)\n   ";
    postorderIterative(root);

    cout << "\n\n[6] Height and depth\n   Height of tree = " << height(root) << "\n";
    printDepths(root);

    cout << "\n[7] BST from [50, 30, 70, 20, 40, 60, 80]\n   Inorder : ";
    BSTNode* bst = buildBST({50, 30, 70, 20, 40, 60, 80});
    inorderBST(bst);
    cout << "\n";

    freeTree(root);
    freeBST(bst);
    return 0;
}