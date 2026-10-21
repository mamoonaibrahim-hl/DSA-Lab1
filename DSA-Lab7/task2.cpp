#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;
    Student(int id, string n, float g)
        : studentID(id), name(n), GPA(g), left(nullptr), right(nullptr) {}
};

//display helper
void printStudent(const Student* s) {
    cout << "   ID: " << setw(5) << s->studentID
         << " | Name: " << setw(12) << left << s->name << right
         << " | GPA: " << fixed << setprecision(2) << s->GPA << "\n";
}

// INSERT :smaller IDs go left, larger go right
Student* insert(Student* root, int id, const string& name, float gpa) {
    if (!root) return new Student(id, name, gpa);
    if (id < root->studentID)      root->left  = insert(root->left, id, name, gpa);
    else if (id > root->studentID) root->right = insert(root->right, id, name, gpa);
    else cout << "   [!] ID " << id << " already exists. Insert skipped.\n";
    return root;
}

// SEARCH :returns node or nullptr
Student* search(Student* root, int id) {
    if (!root || root->studentID == id) return root;
    return (id < root->studentID) ? search(root->left, id)
                                  : search(root->right, id);
}

// DELETE :handles 3 cases: leaf, one child, two children
Student* findMin(Student* root) {
    while (root && root->left) root = root->left;
    return root;
}

Student* deleteStudent(Student* root, int id, bool& found) {
    if (!root) return nullptr;
    if (id < root->studentID)      root->left  = deleteStudent(root->left, id, found);
    else if (id > root->studentID) root->right = deleteStudent(root->right, id, found);
    else {
        found = true;
        // Case 1 & 2 : zero or one child
        if (!root->left)  { Student* t = root->right; delete root; return t; }
        if (!root->right) { Student* t = root->left;  delete root; return t; }
        // Case 3 : two children -> copy inorder successor, then delete it
        Student* succ = findMin(root->right);
        root->studentID = succ->studentID;
        root->name      = succ->name;
        root->GPA       = succ->GPA;
        bool dummy;
        root->right = deleteStudent(root->right, succ->studentID, dummy);
    }
    return root;
}

// INORDER TRAVERSAL :lists students sorted by ID
void inorder(Student* root) {
    if (!root) return;
    inorder(root->left);
    printStudent(root);
    inorder(root->right);
}

// ANALYTICS
int countStudents(Student* root) {
    if (!root) return 0;
    return 1 + countStudents(root->left) + countStudents(root->right);
}

// GPA is not the BST key, so the whole tree must be scanned
void findExtremes(Student* root, Student*& hi, Student*& lo) {
    if (!root) return;
    if (!hi || root->GPA > hi->GPA) hi = root;
    if (!lo || root->GPA < lo->GPA) lo = root;
    findExtremes(root->left, hi, lo);
    findExtremes(root->right, hi, lo);
}

void displayAboveThreshold(Student* root, float th, int& cnt) {
    if (!root) return;
    displayAboveThreshold(root->left, th, cnt);
    if (root->GPA > th) { printStudent(root); cnt++; }
    displayAboveThreshold(root->right, th, cnt);
}

void freeTree(Student* r) { if (r) { freeTree(r->left); freeTree(r->right); delete r; } }

// MENU
void menu() {
    cout << "\nSTUDENT RECORD MANAGEMENT (BST)\n"
         << " 1. Insert student\n 2. Search student by ID\n 3. Delete student by ID\n"
         << " 4. Display all students (Inorder)\n 5. Total number of students\n"
         << " 6. Highest & lowest GPA\n 7. Students above GPA threshold\n 0. Exit\n"
         << "Choice: ";
}

int main() {
    Student* root = nullptr;

    // Pre-loaded sample records
    root = insert(root, 50, "Ali",     3.40f);
    root = insert(root, 30, "Sara",    3.85f);
    root = insert(root, 70, "Hamza",   2.60f);
    root = insert(root, 20, "Ayesha",  3.10f);
    root = insert(root, 40, "Bilal",   2.95f);
    root = insert(root, 60, "Fatima",  3.70f);
    root = insert(root, 80, "Usman",   2.30f);

    int choice;
    do {
        menu();
        if (!(cin >> choice)) break;

        if (choice == 1) {
            int id; string name; float gpa;
            cout << "Enter ID, Name, GPA: ";
            cin >> id >> name >> gpa;
            root = insert(root, id, name, gpa);
        }
        else if (choice == 2) {
            int id; cout << "Enter ID to search: "; cin >> id;
            Student* s = search(root, id);
            if (s) { cout << "   Record found:\n"; printStudent(s); }
            else   cout << "   Student with ID " << id << " not found.\n";
        }
        else if (choice == 3) {
            int id; cout << "Enter ID to delete: "; cin >> id;
            bool found = false;
            root = deleteStudent(root, id, found);
            cout << (found ? "   Record deleted.\n" : "   ID not found.\n");
        }
        else if (choice == 4) {
            cout << "Students sorted by ID\n";
            if (!root) cout << "   (no records)\n"; else inorder(root);
        }
        else if (choice == 5) {
            cout << "   Total students: " << countStudents(root) << "\n";
        }
        else if (choice == 6) {
            Student *hi = nullptr, *lo = nullptr;
            findExtremes(root, hi, lo);
            if (!hi) cout << "   (no records)\n";
            else {
                cout << "   Highest GPA:\n"; printStudent(hi);
                cout << "   Lowest GPA:\n";  printStudent(lo);
            }
        }
        else if (choice == 7) {
            float th; cout << "Enter GPA threshold: "; cin >> th;
            int cnt = 0;
            cout << "   --- Students with GPA above " << th << " ---\n";
            displayAboveThreshold(root, th, cnt);
            if (!cnt) cout << "   None.\n";
        }
        else if (choice != 0) cout << "   Invalid choice.\n";

    } while (choice != 0);

    freeTree(root);
    cout << "Program ended.\n";
    return 0;
}