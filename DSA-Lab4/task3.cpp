#include <iostream>
#include <vector>
using namespace std;

struct BitNode {
    int bit;
    BitNode* next;
    BitNode* prev;
    BitNode(int b) { bit = b; next = prev = nullptr; }
};

class BinaryDLL {
    BitNode* head;
public:
    BinaryDLL() { head = nullptr; }

    // Store binary number in 8-bit blocks
    void storeBinary(vector<int> bits) {
        int pad = (8 - (bits.size() % 8)) % 8;
        for (int i = 0; i < pad; i++) bits.insert(bits.begin(), 0);

        for (int b : bits) {
            BitNode* newNode = new BitNode(b);
            if (!head) { head = newNode; }
            else {
                BitNode* temp = head;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
                newNode->prev = temp;
            }
        }
    }

    void display() {
        BitNode* temp = head;
        int count = 0;
        while (temp) {
            cout << temp->bit;
            count++;
            if (count % 8 == 0) cout << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void onesComplement() {
        BitNode* temp = head;
        while (temp) {
            temp->bit = (temp->bit == 0 ? 1 : 0);
            temp = temp->next;
        }
    }

    void twosComplement() {
        onesComplement();
        BitNode* temp = getTail();
        int carry = 1;
        while (temp && carry) {
            int sum = temp->bit + carry;
            temp->bit = sum % 2;
            carry = sum / 2;
            temp = temp->prev;
        }
    }

    int toDecimal() {
        BitNode* temp = head;
        int result = 0;
        while (temp) {
            result = result * 2 + temp->bit;
            temp = temp->next;
        }
        return result;
    }

    static BinaryDLL add(BinaryDLL& a, BinaryDLL& b) {
        BinaryDLL result;
        BitNode* p = a.getTail();
        BitNode* q = b.getTail();
        int carry = 0;
        vector<int> sumBits;

        while (p || q || carry) {
            int bit1 = p ? p->bit : 0;
            int bit2 = q ? q->bit : 0;
            int sum = bit1 + bit2 + carry;
            sumBits.insert(sumBits.begin(), sum % 2);
            carry = sum / 2;
            if (p) p = p->prev;
            if (q) q = q->prev;
        }
        result.storeBinary(sumBits);
        return result;
    }

    static BinaryDLL multiply(BinaryDLL& a, BinaryDLL& b) {
        BinaryDLL result;
        result.storeBinary({0});

        BitNode* q = b.getTail();
        int shift = 0;
        while (q) {
            if (q->bit == 1) {
                vector<int> shifted;
                for (int i = 0; i < shift; i++) shifted.push_back(0);
                BitNode* p = a.head;
                while (p) { shifted.push_back(p->bit); p = p->next; }
                BinaryDLL temp;
                temp.storeBinary(shifted);
                result = add(result, temp);
            }
            shift++;
            q = q->prev;
        }
        return result;
    }

    BitNode* getTail() {
        BitNode* temp = head;
        while (temp && temp->next) temp = temp->next;
        return temp;
    }
};

int main() {
    BinaryDLL b1, b2;
    int choice;
    vector<int> bits;

    do {
        cout << "\n--- Binary DLL Menu ---\n";
        cout << "1. Enter Binary Number 1\n";
        cout << "2. Enter Binary Number 2\n";
        cout << "3. Display Numbers\n";
        cout << "4. 1's Complement of Number 1\n";
        cout << "5. 2's Complement of Number 1\n";
        cout << "6. Convert Number 1 to Decimal\n";
        cout << "7. Add Number 1 and Number 2\n";
        cout << "8. Multiply Number 1 and Number 2\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string s;
            cout << "Enter binary string (e.g. 1011): ";
            cin >> s;
            bits.clear();
            for (char c : s) bits.push_back(c - '0');
            b1 = BinaryDLL();
            b1.storeBinary(bits);
            break;
        }
        case 2: {
            string s;
            cout << "Enter binary string (e.g. 1101): ";
            cin >> s;
            bits.clear();
            for (char c : s) bits.push_back(c - '0');
            b2 = BinaryDLL();
            b2.storeBinary(bits);
            break;
        }
        case 3:
            cout << "Number 1: "; b1.display();
            cout << "Number 2: "; b2.display();
            break;
        case 4:
            b1.onesComplement();
            cout << "1's Complement of Number 1: "; b1.display();
            break;
        case 5:
            b1.twosComplement();
            cout << "2's Complement of Number 1: "; b1.display();
            break;
        case 6:
            cout << "Decimal Value of Number 1: " << b1.toDecimal() << endl;
            break;
        case 7: {
            BinaryDLL sum = BinaryDLL::add(b1, b2);
            cout << "Addition Result: "; sum.display();
            break;
        }
        case 8: {
            BinaryDLL product = BinaryDLL::multiply(b1, b2);
            cout << "Multiplication Result: "; product.display();
            break;
        }
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
