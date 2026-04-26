#include <iostream>
#include<iomanip>
using namespace std;

class Customer {
private:
    int code;
    string name;
    int hours;
    int pcNumber;

public:
    Customer(int c, string n, int h, int pc) {
        code = c;
        name = n;
        hours = h;
        pcNumber = pc;
    }

    int getCode() { return code; }
    string getName() { return name; }
    int getHours() { return hours; }
    int getPcNumber() { return pcNumber; }

    void display() {
        cout << "Code: " << code
             << " | Name: " << name
             << " | Hours: " << hours
             << " | PC: " << pcNumber
             << endl;
    }
};

struct ReserveNode{
    string code;
    ReserveNode* next;
};

struct LogNode{
    Customer data;
    LogNode* next;
};

ReserveNode* res_head = nullptr;
LogNode* log_head = nullptr;
const int PC_NUM = 8;
int pc_unit[PC_NUM] = {-1,-1,-1,-1,-1,-1,-1,-1};

void addCustomer(); //noah
void passResCustomer(); //rosceth
void displayResQueue(); // cyv
void displayPC();// noah
void removeCustomer(); //cyv
void viewLogRecord(); //rosceth
int checkNumberUnits();
void pcOccupancy();



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
        char menu_choice;
        switch (choice) {
            case '1': {
                int check = checkNumberUnits();
                if (res_head == nullptr){
                    cout << "The reservation queue is empty" << endl;
                    cout << "Do you want to add a customer into a desktop unit" << endl;
                    if (check != -1){
                        cout << check << " units are unoccupied" << endl;
                    }
                    cout << "[o]yes [x]no" << endl;
                    cin >> menu_choice;
                    if (menu_choice == 'o') {
                        pcOccupancy();
                        addCustomer();
                    }
                }
                if (check == -1){
                    cout << "All desktop units are occupied" << endl;
                    cout << "Do you want to add customer in the reservation queue" << endl;
                    cout << "[o] yes [x]no" << endl;
                    cin >> menu_choice;
                }
                break;
            }
            case '2': {
                passResCustomer();
                break;
            }
            case '3': {
                displayResQueue();
                break;
            }
            case '4':{
                displayPC();
                break;
            }
            case '5': {
                removeCustomer();
                break;
            }
            case '6': {
                viewLogRecord();
                break;
            }
            case 'x':
                return 0;

            default:
                cout << "Input Error!" << endl;
        }
    }

    return 0;
}

void addCustomer(){
    cin.ignore();
    string name;
    int pc_num;
    int user_code;
    int hour;
    cout << "\nInput details" << endl;
    cout << "Name: ";
    getline(cin, name);
    cout << "code: ";
    cin >> user_code;
    cout << "hour: ";
    cin >> hour;
    cout << "Unit number: ";
    cin >> pc_num;

    while (pc_unit[pc_num-1] != -1) {
        cout << "Unit occupied, please try again" << endl;
        cout << "Unit number: ";
        cin >> pc_num;
    }
    Customer c(user_code, name, hour, pc_num);

    LogNode* newNode = new LogNode{c, nullptr};
    

    if (log_head == nullptr) {
        log_head = newNode;
    }
    else {
        LogNode* temp = log_head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }


    cout << endl;
    pc_unit[pc_num - 1] = user_code;
    cout << "User " << user_code << " has been successfully assigned to desktop #" << pc_num << endl << endl;

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

int checkNumberUnits(){
    int count = 0;
    for (int i = 0; i < PC_NUM; i++){
        if (pc_unit[i] == -1){
            count++;
        }
    }
    if (count > 0){
        return count;
    }
    else{
        return -1;
    }
}

void pcOccupancy(){
    cout << "| ";
    for (int i = 0; i < PC_NUM; i++) {
        cout << "[" << i + 1 << "] ";
        if (pc_unit[i] == -1) {
            cout << "empty | ";
        }
        else {
            cout << pc_unit[i] << " | ";
        }
    }
    cout << endl;
}