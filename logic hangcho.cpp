#include <iostream>
#include <queue>
#include <string>

using namespace std;

class ReservationManager {
private:
    queue<string> hangDoiCho; 

public:
    
    void enqueue(string userID) {
        hangDoiCho.push(userID);
        cout << "[ENQUEUE] Thanh vien " << userID << " da duoc them vao hang cho dat truoc do sach da het.\n";
    }
    
    string dequeue() {
        if (!hangDoiCho.empty()) {
            string userNhanSach = hangDoiCho.front();
            hangDoiCho.pop();
            cout << "[DEQUEUE] Thanh vien " << userNhanSach << " da duoc lay ra khoi hang cho de nhan sach.\n";
            return userNhanSach;
        }
        cout << "[DEQUEUE] Hang cho hien tai dang trong.\n";
        return "";
    }

    bool isEmpty() {
        return hangDoiCho.empty();
    }
};