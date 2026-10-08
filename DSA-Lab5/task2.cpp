#include <iostream>
#include <string>
using namespace std;

struct Job {
    int id;
    string name;
    int pages;
    Job* next;
};

class PrintQueue {
private:
    Job* front;
    Job* rear;
    int count;

public:
    PrintQueue() { front = rear = NULL; count = 0; }
    ~PrintQueue() { clear(); }
    
    void clear() {
        while (!isEmpty()) {
            Job* temp = front;
            front = front->next;
            delete temp;
        }
        rear = NULL;
        count = 0;
    }

    bool isEmpty() { return front == NULL; }
    int countJobs() { return count; }


    void addJob(int id, string name, int pages) {
        Job* n = new Job;
        n->id = id; n->name = name; n->pages = pages; n->next = NULL;
        if (isEmpty()) front = rear = n;
        else { rear->next = n; rear = n; }
        count++;
        cout << "Added job " << id << " (" << name << ", " << pages << " pages)\n";
    }

        void processJob() {
        if (isEmpty()) { cout << "Cannot process: queue is empty\n"; return; }
        Job* temp = front;
        cout << "Processing job " << temp->id << " (" << temp->name
             << ", " << temp->pages << " pages)\n";
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        count--;
    }

    void viewNext() {
        if (isEmpty()) { cout << "No next job: queue is empty\n"; return; }
        cout << "Next job: " << front->id << " (" << front->name
             << ", " << front->pages << " pages)\n";
    }
    
    void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }
        cout << "Waiting jobs (front -> rear):\n";
        for (Job* p = front; p != NULL; p = p->next)
            cout << "  [" << p->id << "] " << p->name << " - " << p->pages << " pages\n";
    }

};

int main() {
    PrintQueue q;
    int choice;
    do {
        cout << "\nPRINTER JOB QUEUE\n"
             << "1. Add Job\n"
             << "2. Process Job\n"
             << "3. View Next Job\n"
             << "4. Display Queue\n"
             << "5. Count Jobs\n"
             << "6. IsEmpty\n"
             << "7. Clear Queue\n"
             << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character

        if (choice == 1) {
            cout << "Job ID: ";
            int id; cin >> id;
            cin.ignore(); // Ignore the newline character
            cout << "Document name: ";
            string name; getline(cin, name);
            cout << "Number of pages: ";
            int pages; cin >> pages;
            cin.ignore(); // Ignore the newline character
            q.addJob(id, name, pages);
        }
        else if (choice == 2) q.processJob();
        else if (choice == 3) q.viewNext();
        else if (choice == 4) q.display();
        else if (choice == 5) cout << "Jobs waiting: " << q.countJobs() << endl;
        else if (choice == 6) cout << (q.isEmpty() ? "Queue is empty.\n" : "Queue is NOT empty.\n");
        else if (choice == 7) {
            q.clear();
            cout << "Queue cleared.\n";
        }
    
    } while (choice != 0);

    cout << "END!\n";
    return 0;
}