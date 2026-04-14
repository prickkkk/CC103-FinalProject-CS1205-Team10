#include <iostream>
using namespace std;

void addCustomer(); //noah
void passResCustomer(); //rosceth
void displayResQueue(); // cyv
void displayPC();// noah
void removeCustomer(); //cyv
void viewLogRecord(); //rosceth


int main(){


    while (true){
        cout << "<----MAIN MENU---->" << endl;
        cout << "[1] add customer" << endl;
        cout << "[2] add customer from reservation queue" << endl;
        cout << "[3] display reservation queue" << endl;
        cout << "[4] display pc and remaining time" << endl;
        cout << "[5] remove customer in pc" << endl;
        cout << "[6] display log record" << endl;
        cout << "[x] exit" << endl;
        char choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice){
            case '1':
                addCustomer();
                break;
            case '2':
                passResCustomer();
                break;
            case '3':
                displayResQueue();
                break;
            case '4':
                displayPC();
                break;
            case '5':
                removeCustomer();
                break;
            case '6':
                viewLogRecord();
                break;
            case 'x':
                return 0;
            default:
                cout << "Input Error!" << endl;
        }
    }

    return 0;
}

void addCustomer(){

}
void passResCustomer(){

}
void displayResQueue(){

}
void displayPC(){

}
void removeCustomer(){

}
void viewLogRecord(){

}