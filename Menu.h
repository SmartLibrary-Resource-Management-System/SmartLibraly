#ifndef MENU_UI_H
#define MENU_UI_H

#include <string>
#include <vector>

class MenuUI {
private:
    int width;
    
    void printBorderLine(char left, char middle, char right) const;
    void printCenteredText(const std::string& text) const;
    void printLeftAlignedText(const std::string& text, int paddingLeft = 4) const;

public:
    MenuUI(int menuWidth = 60);

    void clearScreen() const;
    void pauseScreen() const;

    void drawHeader(const std::string& title) const;
    void drawMenu(const std::string& title, const std::vector<std::string>& options) const;
    
    int getUserChoice(int minOption, int maxOption) const;
    void displayMainMenu() const;
};

#endif // MENU_UI_H
