#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <iostream>
#include <string>
#include <vector>

enum class SearchCriteria {
    BY_TITLE = 1,
    BY_ISBN,
    BY_AUTHOR,
    BY_CATEGORY,
    BY_ID,
    EXIT = 0
};

class SearchEngine {
public:
    SearchEngine() = default;
    ~SearchEngine() = default;

    void searchByTitle(const std::string& title) const {
        std::cout << "\n[SearchEngine] Dang tim kiếm theo Tieu de: \"" << title << "\"...\n";
    }

    void searchByISBN(const std::string& isbn) const {
        std::cout << "\n[SearchEngine] Dang tim kiếm theo ISBN: \"" << isbn << "\"...\n";
    }

    void searchByAuthor(const std::string& author) const {
        std::cout << "\n[SearchEngine] Dang tim kiếm theo Tac gia: \"" << author << "\"...\n";
    }

    void searchByCategory(const std::string& category) const {
        std::cout << "\n[SearchEngine] Dang tim kiếm theo The loai: \"" << category << "\"...\n";
    }

    void searchByID(int id) const {
        std::cout << "\n[SearchEngine] Dang tim kiếm theo Ma ID: " << id << "...\n";
    }

    void displaySearchMenu() {
        int choice = -1;
        
        do {
            std::cout << "\n==================================================\n";
            std::cout << "         DANH SÁCH CÔNG CỤ TÌM KIẾM THƯ VIỆN      \n";
            std::cout << "==================================================\n";
            std::cout << "  1. Tìm kiếm theo Tiêu đề (Search by Title)\n";
            std::cout << "  2. Tìm kiếm theo Mã ISBN (Search by ISBN)\n";
            std::cout << "  3. Tìm kiếm theo Tác giả (Search by Author)\n";
            std::cout << "  4. Tìm kiếm theo Thể loại (Search by Category)\n";
            std::cout << "  5. Tìm kiếm theo Mã ID (Search by ID)\n";
            std::cout << "  0. Quay lại / Thoát menu tìm kiếm\n";
            std::cout << "--------------------------------------------------\n";
            std::cout << "Vui lòng nhập lựa chọn của bạn [0 - 5]: ";

            if (!(std::cin >> choice)) {
                std::cout << "Loi: Nhap khong hợp le! Vui long nhap so.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            std::cin.ignore(10000, '\n');

            switch (static_cast<SearchCriteria>(choice)) {
                case SearchCriteria::BY_TITLE: {
                    std::string title;
                    std::cout << "--> Nhap tieu de sach/tai nguyen can tim: ";
                    std::getline(std::cin, title);
                    searchByTitle(title);
                    break;
                }
                case SearchCriteria::BY_ISBN: {
                    std::string isbn;
                    std::cout << "--> Nhap ma ISBN can tim: ";
                    std::getline(std::cin, isbn);
                    searchByISBN(isbn);
                    break;
                }
                case SearchCriteria::BY_AUTHOR: {
                    std::string author;
                    std::cout << "--> Nhap ten tac gia: ";
                    std::getline(std::cin, author);
                    searchByAuthor(author);
                    break;
                }
                case SearchCriteria::BY_CATEGORY: {
                    std::string category;
                    std::cout << "--> Nhap the loai / danh muc: ";
                    std::getline(std::cin, category);
                    searchByCategory(category);
                    break;
                }
                case SearchCriteria::BY_ID: {
                    int id;
                    std::cout << "--> Nhap ma ID tai nguyen: ";
                    if (std::cin >> id) {
                        searchByID(id);
                    } else {
                        std::cout << "Loi: ID phai la so nguyen!\n";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    break;
                }
                case SearchCriteria::EXIT:
                    std::cout << "\nThoat khoi Menu Tim Kiem.\n";
                    break;
                default:
                    std::cout << "\nLua chon khong hop le! Vui long chon tu 0 den 5.\n";
                    break;
            }

        } while (static_cast<SearchCriteria>(choice) != SearchCriteria::EXIT);
    }
};

#endif

int main() {
    SearchEngine engine;
    engine.displaySearchMenu();
    return 0;
}