#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Book {
    string id;
    string title;
    string author;
    int publishYear;
    bool isAvailable;
};

string toLower(const string& str) {
    string res = str;
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

void searchBooksByAuthor(const vector<Book>& library) {
    cout << "\n=========================================\n";
    cout << "      TIM SACH THEO TAC GIA             \n";
    cout << "=========================================\n";
    
    string keyword;
    cout << "Nhap ten tac gia can tim: ";
    cin.ignore();
    getline(cin, keyword);

    if (keyword.empty()) {
        cout << "--> Ten tac gia khong duoc de rong!\n";
        return;
    }

    string keywordLower = toLower(keyword);
    bool found = false;

    cout << "\n-----------------------------------------------------------------\n";
    cout << "DANH SACH SACH CUA TAC GIA: \"" << keyword << "\"\n";
    cout << "-----------------------------------------------------------------\n";

    for (const auto& book : library) {
        if (toLower(book.author).find(keywordLower) != string::npos) {
            found = true;
            cout << "ID           : " << book.id << "\n"
                 << "Ten sach     : " << book.title << "\n"
                 << "Tac gia      : " << book.author << "\n"
                 << "Nam xuat ban : " << book.publishYear << "\n"
                 << "Trang thai   : " << (book.isAvailable ? "Co sang trong kho" : "Da duoc muon") << "\n";
            cout << "-----------------------------------------------------------------\n";
        }
    }

    if (!found) {
        cout << "--> Khong tim thay cuon sach nao cua tac gia \"" << keyword << "\".\n";
    }
}

int main() {
    vector<Book> library = {
        {"B001", "Lap trinh C++ Nang cao", "Nguyen Van A", 2021, true},
        {"B002", "Giai thuat va Cau truc du lieu", "Nguyen Van A", 2019, false},
        {"B003", "Thiet ke He thong Smart Library", "Dang Bao Ngoc", 2023, true},
        {"B004", "Huong dan Lap trinh Game C++", "Le Thanh Binh", 2022, true}
    };

    int choice;
    do {
        cout << "\n=== SMART LIBRARY MENU ===\n";
        cout << "1. Tim sach theo tac gia\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchBooksByAuthor(library);
                break;
            case 0:
                cout << "Da thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long nhap lai.\n";
        }
    } while (choice != 0);

    return 0;
}