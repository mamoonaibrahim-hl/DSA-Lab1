#include <iostream>
#include <string>
using namespace std;
//Doubly Linked List Node
struct Song {
    int id;
    string name;
    string duration;
    Song* next;
    Song* prev;
    Song(int i, string n, string d) {
        id = i; name = n; duration = d;
        next = prev = nullptr;
    }
};

//Playlist class
class Playlist {
    Song* head;
public:
    Playlist() { head = nullptr; }

    //Add song at end
    void addSong(int id, string name, string duration) {
        Song* newSong = new Song(id, name, duration);
        if (!head) { head = newSong;
             return; }
        Song* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newSong;
        newSong->prev = temp;
    }

    //Delete song by ID
    void deleteSong(int id) {
        Song* temp = head;
        while (temp && temp->id != id) temp = temp->next;
        if (!temp) { cout << "Song not found!\n"; return; }
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        if (temp == head) head = temp->next;
        delete temp;
    }

    //Display forward
    void displayForward() {
        Song* temp = head;
        while (temp) {
            cout << temp->id << " - " << temp->name << " (" << temp->duration << ")\n";
            temp = temp->next;
        }
    }

    //Display backward
    void displayBackward() {
        Song* temp = head;
        while (temp && temp->next) temp = temp->next;
        while (temp) {
            cout << temp->id << " - " << temp->name << " (" << temp->duration << ")\n";
            temp = temp->prev;
        }
    }

    //Search song
    void searchSong(int id) {
        Song* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Found: " << temp->name << " (" << temp->duration << ")\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found!\n";
    }

    //Reverse playlist
    void reversePlaylist() {
        Song* temp = nullptr;
        Song* current = head;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp) head = temp->prev;
    }
};


//Main
int main() {
    Playlist pl;
    int choice, id;
    string name, duration;

    //menu-driven interface

    do {
        cout << "\n--- Playlist Menu ---\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Reverse Playlist\n";
        cout << "0. Exit\n";
         cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Song ID: "; cin >> id;
            cout << "Enter Song Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Duration (mm:ss): "; getline(cin, duration);
            pl.addSong(id, name, duration);
            break;
        case 2:
            cout << "Enter Song ID to delete: "; cin >> id;
            pl.deleteSong(id);
            break;
        case 3:
            pl.displayForward();
            break;
        case 4:
            pl.displayBackward();
            break;
        case 5:
            cout << "Enter Song ID to search: "; cin >> id;
            pl.searchSong(id);
            break;
        case 6:
            pl.reversePlaylist();
            cout << "Playlist reversed!\n";
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);


    return 0;
}
