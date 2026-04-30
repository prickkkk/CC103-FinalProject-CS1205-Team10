#include <iostream>
#include<iomanip>
#include <string>
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

struct TimeNode{
    int code;
    int hour;
    int pc;
    TimeNode* next;
};

ReserveNode* res_head = nullptr;
LogNode* log_head = nullptr;
TimeNode* time_priority_head = nullptr;
const int PC_NUM = 4;
int pc_unit[PC_NUM] = {-1,-1,-1,-1};
int user_code = 100;

void addCustomer(); //noah
void passResCustomer(); //rosceth
void displayResQueue(); // cyv
void displayPcTime();// noah
void removeCustomer(); //cyv
void viewLogRecord(); //rosceth
void addResQueue(string res_code);
int checkNumberUnits();
void pcOccupancy();



int main(){

    while (true){
        cout << endl;
        cout << "=============== MAIN MENU ===============" << endl;
        cout << "[1] add customer" << endl;
        cout << "[2] add customer from reservation queue" << endl;
        cout << "[3] display reservation queue" << endl;
        cout << "[4] display pc and remaining time" << endl;
        cout << "[5] remove customer in pc" << endl;
        cout << "[6] display log record" << endl;
        cout << "[x] exit" << endl;
        cout << "-----------------------------------------" << endl;
        char choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl << "=========================================" << endl;
        cout << endl;
        char menu_choice;
        switch (choice) {
            case '1': {
                int check = checkNumberUnits();
                if (res_head == nullptr && check > 0){
                    cout << ">> The reservation queue is empty <<" << endl;
                    cout << "Do you want to add a customer into a desktop unit?" << endl;
                    if (check != -1){
                        cout << "(" << check << " units are unoccupied" << " )" << endl;
                    }
                    cout << "------------------" << endl;
                    cout << "[o]yes [x]no  : ";
                    cin >> menu_choice;
                    cout << "------------------" << endl;

                    if (menu_choice == 'o') {
                        pcOccupancy();
                        addCustomer();
                    }
                }
                if (check == -1){
                    cout << ">> All desktop units are occupied <<" << endl;
                    cout << "Do you want to add customer in the reservation queue?" << endl;
                    cout << "---------------" << endl;
                    cout << "[o] yes [x]no: ";
                    cin >> menu_choice;
                    cout << "---------------" << endl;


                    if (menu_choice == 'o') {
                        string code;
                        cout << endl << "Enter the customer's reservation code: ";
                        cin >> code;
                        cout << endl;
                        addResQueue(code);
                        cout << ">> Customer with code #" << code << " added in the reservation queue <<" << endl << endl;
                    }
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
                pcOccupancy();
                displayPcTime();
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
    int hour;
    cout << "\n<--INPUT DETAILS-->" << endl;
    cout << left << setw(12) << "Name" << ":";
    getline(cin, name);
    cout << left << setw(12) << "time" << ":";
    cin >> hour;
    cout << left << setw(12) << "unit number" << ":";
    cin >> pc_num;
    while (pc_unit[pc_num-1] != -1) {
        cout << "Unit occupied, please try again" << endl;
        cout << "Unit number: ";
        cin >> pc_num;
    }
    cout << "code: " << user_code + 1 << endl;
    user_code++;

    pc_unit[pc_num - 1] = user_code;
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

    TimeNode* newTimeNode = new TimeNode();
    newTimeNode->code = user_code;
    newTimeNode->hour = hour;
    newTimeNode->pc = pc_num;
    newTimeNode->next = nullptr;

    if(time_priority_head == nullptr || hour <=  time_priority_head->hour){
        newTimeNode->next = time_priority_head;
        time_priority_head = newTimeNode;

    }
    else {
        TimeNode* temp = time_priority_head;
        while (temp->next != nullptr && temp->next->hour <= hour) {
            temp = temp->next;
        }
        newTimeNode->next = temp->next;
        temp->next = newTimeNode;
    }

    cout << endl;

    cout << ">> Customer " << user_code << " has been successfully assigned to desktop #" << pc_num << " <<" << endl << endl;

}
void passResCustomer(){
    int check = checkNumberUnits();
    if (res_head == nullptr) {
        cout << ">> Reservation queue is empty <<" << endl;
        return;
    }
    char choice;
    cout << "What do you want to do with " << res_head->code << endl;
    cout << "[o] assign to a pc [x] remove: ";
    cin >> choice;


    if (choice == 'o') {
        if( check != -1){
            ReserveNode* temp = res_head;
            string reserved_code = res_head->code;
            res_head = res_head->next;
            delete temp;
            cout << ">> " << reserved_code << " has been removed from reservation line <<" << endl;
            cout << "Now input your details." << endl;
            pcOccupancy();
            addCustomer();
        }
        else{
            cout <<  "All units are occupied!" << endl;
            return;
        }
    }
    else if (choice == 'x') {
        ReserveNode* temp = res_head;
        string reserved_code = res_head->code;
        res_head = res_head->next;
        delete temp;
        cout << ">> " << reserved_code << " has been deleted to reservation line <<" << endl;
    }
    else {
        cout << "Invalid Input!" << endl;
    }

    }

void addResQueue(string res_code){
    ReserveNode* newNode = new ReserveNode();
    newNode->code = res_code;
    newNode->next = nullptr;

    if(res_head == nullptr){
        res_head = newNode;
    }
    else{
        ReserveNode* temp = res_head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void displayResQueue() {

    if (res_head == nullptr) {
        cout << "Reservation queue is empty\n";
        return;
    }
    ReserveNode* temp = res_head;

    while (temp != nullptr) {
        cout << "["<< temp->code << "] <- ";
        temp = temp->next;
    }
    cout << "[end of queue]" << endl << endl;
}
void displayPcTime(){
    cout << "<--Sorted base on remaining time-->" << endl;
    if (time_priority_head == nullptr) {
        cout << "All desktop units are empty" << endl;
    }
    TimeNode* temp = time_priority_head;
    while (temp != nullptr){
        cout << "| ";
        cout << "[" << temp->pc << "]" << " " << temp->code << " - " << temp->hour << " hrs | <- ";
        temp = temp->next;
    }
    cout << "[end of queue]" << endl << endl;
}
void removeCustomer(){
    char choice;
    cout << "[1]Remove a specific customer  [2]Remove a customer that runs out of time" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == '1') {
        pcOccupancy();
        int code_to_remove;
        cout << "Enter the user code to remove: ";
        cin >> code_to_remove;
        bool not_found = true;
        for(int  i = 0; i  < PC_NUM; i++){
            if(pc_unit[i] == code_to_remove){
                pc_unit[i] = -1;
                not_found = false;
            }
        }
        if (not_found){
            cout << ">> User code not found <<" << endl;
        }
        else {
            TimeNode* temp = time_priority_head;
            if (temp->code == code_to_remove) {
                time_priority_head = temp->next;
                delete temp;
            }
            else{
                while (temp->next->code != code_to_remove) {
                    temp = temp->next;
                }
                TimeNode* toDelete = temp->next;
                temp->next = toDelete->next;
                delete toDelete;

            }
            cout << ">> User code #" << code_to_remove << " successfully removed <<" << endl;
        }
        cout << endl << endl;
    }
    else if (choice == '2') {
        displayPcTime();
        cout << "Do you want to remove customer " << time_priority_head->code << " with " << time_priority_head->hour << " remaining hour/hours?: " << endl;
        cout << "[o]yes [x]no: ";
        cin >> choice;
        if (choice == 'o') {
            TimeNode* temp = time_priority_head;
            time_priority_head = temp->next;
            delete temp;

            for (int i = 0; i < PC_NUM; i++) {
                if (pc_unit[i] == time_priority_head->code) {
                    pc_unit[i] = -1;
                }
            }
            cout << ">> User code #" << time_priority_head->code << " successfully removed <<" << endl;
        }
        else {
            return;
        }
    }

}
void viewLogRecord(){
    if (log_head == nullptr) {
        cout << ">> No log records available <<" << endl << endl;
        return;
    }

    cout << "\n=====================LOG RECORDS=====================" << endl << endl;
    LogNode* temp = log_head;
    int record_num = 1;

    while (temp != nullptr) {
        cout << "[Record " << record_num << "] ";
        temp->data.display();
        temp = temp->next;
        record_num++;
    }

    cout << "\n--------------------------------------------------" << endl << endl;
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
    cout <<  endl << endl;
    cout << "=====================PC UNITS=====================" << endl << endl;
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
    cout << endl <<  endl << "--------------------------------------------------" << endl;
}
