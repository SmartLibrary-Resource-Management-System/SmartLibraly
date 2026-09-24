#include <iostream>
#include <limits>

void moduleAddResource() {
    std::cout << "\n[Chuc nang] Them tai nguyen moi...\n";
}

void moduleBorrowResource() {
    std::cout << "\n[Chuc nang] Xu ly muon tai nguyen...\n";
}

void moduleReturnResource() {
    std::cout << "\n[Chuc nang] Xu ly tra tai nguyen...\n";
}

void moduleSearchResource() {
    std::cout << "\n[Chuc nang] Tim kiem tai nguyen (Title, Author, ISBN, Genre)...\n";
}

void moduleCalculateFine() {
    std::cout << "\n[Chuc nang] Tinh tien phat qua han...\n";
}

void moduleDataExport() {
    std::cout << "\n[Chuc nang] Luu/Xuat bao cao du lieu...\n";
}

void displayMenu() {
    std::cout << "\n=============================================\n";
    std::cout << "    SMART LIBRARY & RESOURCE MANAGEMENT\n";
    std::cout << "=============================================\n";
    std::cout << "1. Them tai nguyen moi\n";
    std::cout << "2. Muon tai nguyen\n";
    std::cout << "3. Tra tai nguyen\n";
    std::cout << "4. Tim kiem tai nguyen\n";
    std::cout << "5. Tinh tien phat\n";
    std::cout << "6. Luu/Xuat du lieu\n";
    std::cout << "0. Thoat chuong trinh\n";
    std::cout << "=============================================\n";
    std::cout << "Nhap lua chon cua ban (0-6): ";
}

int main() {
    int choice = -1;
    bool running = true;

    while (running) {
        displayMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[Loi] Lua chon khong hop le. Vui long nhap so!\n";
            continue;
        }

        switch (choice) {
            case 1:
                moduleAddResource();
                break;
            case 2:
                moduleBorrowResource();
                break;
            case 3:
                moduleReturnResource();
                break;
            case 4:
                moduleSearchResource();
                break;
            case 5:
                moduleCalculateFine();
                break;
            case 6:
                moduleDataExport();
                break;
            case 0:
                std::cout << "\nDang thoat he thong. Tam biet!\n";
                running = false;
                break;
            default:
                std::cout << "\n[Loi] Tieu muc khong ton tai. Vui long chon tu 0 den 6!\n";
                break;
        }
    }

    return 0;
}