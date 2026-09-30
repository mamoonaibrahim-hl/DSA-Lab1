#include <iostream>
using namespace std;

struct Person {
    int id;
    Person* next;
    Person(int i) { id = i; next = nullptr; }
};

class Josephus {
    Person* tail; // tail pointer for circular list
public:
    // Create Circle
    Josephus(int n) {
        tail = new Person(1);
        tail->next = tail; // single node circle
        for (int i = 2; i <= n; i++) {
            Person* newNode = new Person(i);
            newNode->next = tail->next; // point to head
            tail->next = newNode;
            tail = newNode; // move tail forward
        }
    }

    // Elimination Process
    void eliminate(int k) {
        Person* temp = tail->next; // start from head
        Person* prev = tail;       // previous is tail

        cout << "\nElimination Order:\n";
        while (temp->next != temp) { // until one survivor
            for (int i = 1; i < k; i++) {
                prev = temp;
                temp = temp->next;
            }
            cout << "Eliminated: " << temp->id << endl;
            prev->next = temp->next;
            if (temp == tail) tail = prev; // update tail if needed
            delete temp;
            temp = prev->next;
        }
        cout << "\nSurvivor: " << temp->id << endl;
    }
};

int main() {
    int n, k;
    cout << "Enter number of people (N): ";
    cin >> n;
    cout << "Enter step count (k): ";
    cin >> k;

    Josephus j(n);
    j.eliminate(k);

    return 0;
}
