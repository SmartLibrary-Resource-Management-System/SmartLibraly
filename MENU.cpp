#include "MenuUI.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;

MenuUI::MenuUI(int menuWidth) : width(menuWidth) {}

void MenuUI::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MenuUI::pauseScreen() const {
    cout << "\n  [Nhan Enter de tiep tuc...]";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void MenuUI::printBorderLine(char left, char middle, char right) const {
    cout << "  " << left;
    for (int i = 0; i < width - 2; ++i) {
        cout << middle;
    }
    cout << right << "\n";
}

void MenuUI::printCenteredText(const std::string& text) const {
    int padding = (width - 2 - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;
    
    int rightPadding = width - 2 - padding - static_cast<int>(text.length());
    if (rightPadding < 0) rightPadding = 0;

    cout << "  |" << string(padding, ' ') << text << string(rightPadding, ' ') << "|\n";
}

void MenuUI::printLeftAlignedText(const std::string& text, int paddingLeft) const {
    int textLen = static_cast<int>(text.length());
    int paddingRight = width - 2 - paddingLeft - textLen;
    if (paddingRight < 0) paddingRight = 0;

    cout << "  |" << string(paddingLeft, ' ') << text << string(paddingRight, ' ') << "|\n";
}

void MenuUI::drawHeader(const std::string& title) const {
    printBorderLine('+', '=', '+');
    printCenteredText(title);
    printBorderLine('+', '=', '+');
}

void MenuUI::drawMenu(const std::string& title, const std::vector<std::string>& options) const {
    clearScreen();
    cout << "\n";
    
    printBorderLine('+', '=', '+');
    printCenteredText(title);
    printBorderLine('+', '-', '+');
    
    for (size_t i = 0; i < options.size(); ++i) {
        string item = to_string(i + 1) + ". " + options[i];
        printLeftAlignedText(item, 6);
    }
    
    printBorderLine('+', '=', '+');
}

int MenuUI::getUserChoice(int minOption, int maxOption) const {
    int choice;
    while (true) {
        cout << "\n  >> Lua chon cua ban [" << minOption << " - " << maxOption << "]: ";
        if (cin >> choice && choice >= minOption && choice <= maxOption) {
            return choice;
        }
        
        cout << "  [!] Lua chon khong hop le. Vui long nhap lai!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void MenuUI::displayMainMenu() const {
    vector<string> options = {
        "Quan ly thong tin sinh vien",
        "Tra cuu & Tim kiem du lieu",
        "Bao cao & Thong ke he thong",
        "Cai dat he thong",
        "Thoat chuong trinh"
    };

    drawMenu("HE THONG QUAN LY CONSOLE MENU", options);
}
