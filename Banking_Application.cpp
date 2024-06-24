#include <bits/stdc++.h>
using namespace std;

// Struct to represent a Bank account
struct Bank {
    string name;
    int acc_number;
    float balance;
    stack<long int> trans_history;  // Stack to keep track of transaction history
};

// Struct to represent a node in a linked list
struct ListNode {
    Bank* obj;       // Pointer to a Bank object
    ListNode* next;  // Pointer to the next node in the list
};

ListNode* head = nullptr;  // Head of the linked list

// Function to insert a new Bank object into the linked list
void insert(Bank* b) {
    ListNode* newNode = new ListNode();
    newNode->obj = b;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        ListNode* ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}

// Function to create a new bank account
void createAcc() {
    Bank* b = new Bank();
    cout << "Enter Name: ";
    cin >> b->name;
    cout << "Enter Account No.: ";
    cin >> b->acc_number;
    b->balance = 1000.0;  // Initial balance
    b->trans_history.push(b->balance);  // Initial transaction

    insert(b);
    cout << "Account has been initially credited with bonus 1000" << endl;
}

// Function to print bank details for a specific account
void printBankDetails() {
    cout << "Enter Account No.: ";
    int num;
    cin >> num;
    ListNode* ptr = head;
    while (ptr != nullptr) {
        Bank* cust = ptr->obj;
        if (cust->acc_number == num) {
            cout << cust->name << endl;
            cout << cust->balance << endl;
            stack<long int> s = cust->trans_history;
            cout << "---Transaction history---" << endl;
            while (!s.empty()) {
                long int stt = s.top();
                if (stt < 0)
                    cout << "Amount Debited: " << (stt * -1) << endl;
                else
                    cout << "Amount Credited: " << stt << endl;
                s.pop();
            }
            cout << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "Account doesn't exist" << endl;
}

// Function to withdraw money from an account
void withdraw() {
    cout << "Enter Account No.: ";
    int acc;
    cin >> acc;
    ListNode* ptr = head;
    while (ptr != nullptr) {
        Bank* cust = ptr->obj;
        if (cust->acc_number == acc) {
            cout << "Enter Amount to Withdraw: ";
            int amt;
            cin >> amt;
            if (cust->balance < amt) {
                cout << "No Enough Balance" << endl;
            } else {
                cust->balance -= amt;
                cust->trans_history.push(amt * -1);
            }
            return;
        }
        ptr = ptr->next;
    }
    cout << "Account doesn't exist" << endl;
}

// Function to deposit money into an account
void deposit() {
    cout << "Enter Account No.: ";
    int acc;
    cin >> acc;
    ListNode* ptr = head;
    while (ptr != nullptr) {
        Bank* cust = ptr->obj;
        if (cust->acc_number == acc) {
            cout << "Amount to deposit: ";
            int amt;
            cin >> amt;
            cust->balance += amt;
            cust->trans_history.push(amt);
            return;
        }
        ptr = ptr->next;
    }
    cout << "Account doesn't exist" << endl;
}

// Function to transfer money from one account to another
void transfer() {
    cout << "Enter Account No.: ";
    int acc;
    cin >> acc;
    ListNode* ptr = head;
    while (ptr != nullptr) {
        Bank* cust = ptr->obj;
        if (cust->acc_number == acc) {
            cout << "Account number to transfer to: ";
            int a;
            cin >> a;
            ListNode* p = head;
            while (p != nullptr) {
                Bank* cust2 = p->obj;
                if (cust2->acc_number == a) {
                    cout << "Enter Amount: ";
                    int amt;
                    cin >> amt;
                    if (cust->balance < amt) {
                        cout << "Not Enough Balance" << endl;
                    } else {
                        cust->balance -= amt;
                        cust2->balance += amt;
                        cust2->trans_history.push(amt);
                        cust->trans_history.push(amt * -1);
                    }
                    return;
                }
                p = p->next;
            }
            cout << "Target account doesn't exist" << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "Account doesn't exist" << endl;
}

// Function to remove an account
void removeAcc() {
    cout << "Enter Account No.: ";
    int acc;
    cin >> acc;
    ListNode* ptr = head;
    ListNode* prev = nullptr;
    while (ptr != nullptr) {
        Bank* cust = ptr->obj;
        if (cust->acc_number == acc) {
            if (prev == nullptr) {
                head = ptr->next;
            } else {
                prev->next = ptr->next;
            }
            delete ptr->obj;
            delete ptr;
            cout << "Account removed successfully" << endl;
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    cout << "Account doesn't exist" << endl;
}

// Function to print details of all customers
void allCustomersDetails() {
    ListNode* ptr = head;
    while (ptr != nullptr) {
        Bank* cust = ptr->obj;
        cout << cust->name << endl;
        cout << cust->balance << endl;
        stack<long int> s = cust->trans_history;
        cout << "---Transaction history---" << endl;
        while (!s.empty()) {
            long int stt = s.top();
            if (stt < 0)
                cout << "Amount Debited: " << (stt * -1) << endl;
            else
                cout << "Amount Credited: " << stt << endl;
            s.pop();
        }
        cout << endl;
        ptr = ptr->next;
    }
}

// Function to print a queue of strings
void print(queue<string> q) {
    while (!q.empty()) {
        cout << q.front() << endl;
        q.pop();
    }
}

// Main function to provide menu and handle user inputs
int main() {
    queue<string> q;  // Queue to keep track of service requests
    int temp = 0;  // Counter to keep track of number of accounts
    do {
        cout << "Select any operation!" << endl;
        cout << "1. Account Creation" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Service Requests" << endl;
        cout << "6. Print Your Account Details" << endl;
        cout << "7. Print All Customers Details" << endl;
        cout << "8. Remove Account" << endl;
        cout << "9. End" << endl;
        int k;
        cin >> k;
        switch (k) {
            case 1:
                createAcc();
                q.push("Account Created");
                temp++;
                break;
            case 2:
                if (temp >= 1) {
                    deposit();
                    q.push("Amount Deposited");
                } else {
                    cout << "Input not valid" << endl;
                }
                break;
            case 3:
                if (temp >= 1) {
                    withdraw();
                    q.push("Amount Withdrawn");
                } else {
                    cout << "Input not valid" << endl;
                }
                break;
            case 4:
                if (temp >= 2) {
                    transfer();
                    q.push("Amount Transferred");
                } else {
                    cout << "Input not valid" << endl;
                }
                break;
            case 5:
                if (temp >= 1) {
                    print(q);
                } else {
                    cout << "Input not valid" << endl;
                }
                break;
            case 6:
                if (temp >= 1) {
                    printBankDetails();
                    q.push("Account Details Displayed");
                } else {
                    cout << "Input not valid" << endl;
                }
                break;
            case 7:
                if (temp >= 1) {
                    allCustomersDetails();
                } else {
                    cout << "Input not valid" << endl;
                }
                break;
            case 8:
                if (temp >= 1) {
                    temp--;
                    removeAcc();
                } else {
                    cout << "Input not valid" << endl;
                }
                break;
            case 9:
                exit(0);
            default:
                cout << "Enter valid option" << endl;
        }
    } while (1);
}
