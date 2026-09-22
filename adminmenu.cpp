#include <iostream>
#include <string>
#include <limits>
#include "ResourceManager.h"
#include "Book.h"
#include "EBook.h"
#include "Journal.h"

using namespace std;

// Hàm tiện ích hỗ trợ đọc chuỗi có dấu cách an toàn
string inputLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

// Xử lý menu Thêm tài nguyên (Book / EBook / Journal)
void handleAddResource(ResourceManager& manager) {
    cout << "\n--- CHỌN LOẠI TÀI NGUYÊN CẦN THÊM ---\n";
    cout << "1. Sách in (Physical Book)\n";
    cout << "2. Sách điện tử (E-Book)\n";
    cout << "3. Tạp chí khoa học (Academic Journal)\n";
    cout << "Lựa chọn của bạn: ";
    
    int type;
    if (!(cin >> type)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[Lỗi] Lựa chọn không hợp lệ!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm

    if (type < 1 || type > 3) {
        cout << "[Lỗi] Loại tài nguyên không tồn tại!\n";
        return;
    }

    string id = inputLine("Nhập mã tài nguyên (ID): ");
    
    // Kiểm tra xem ID đã tồn tại trong vector chưa
    if (manager.findById(id) != nullptr) {
        cout << "[Lỗi] Mã ID '" << id << "' đã tồn tại trong hệ thống!\n";
        return;
    }

    string title = inputLine("Nhập tên tài nguyên: ");
    string author = inputLine("Nhập tên tác giả: ");

    if (type == 1) {
        int pages;
        cout << "Nhập số trang: ";
        cin >> pages;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string isbn = inputLine("Nhập mã ISBN: ");

        manager.add(new Book(id, title, author, pages, isbn));
    } 
    else if (type == 2) {
        double fileSize;
        cout << "Nhập dung lượng file (MB): ";
        cin >> fileSize;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string format = inputLine("Nhập định dạng file (PDF, EPUB, MOBI,...): ");

        manager.add(new EBook(id, title, author, fileSize, format));
    } 
    else if (type == 3) {
        int issueNum, year;
        cout << "Nhập số phát hành (Issue #): ";
        cin >> issueNum;
        cout << "Nhập năm xuất bản: ";
        cin >> year;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        manager.add(new Journal(id, title, author, issueNum, year));
    }
}

// Xử lý Xóa tài nguyên theo ID
void handleRemoveResource(ResourceManager& manager) {
    cout << "\n--- XÓA TÀI NGUYÊN KHỎI KHO ---\n";
    string id = inputLine("Nhập ID tài nguyên cần xóa: ");
    manager.remove(id);
}

// Giao diện Menu Admin Quản lý kho sách
void runAdminInventoryMenu(ResourceManager& manager) {
    int choice = 0;
    while (true) {
        cout << "\n=========================================\n";
        cout << "       MENU ADMIN: QUẢN LÝ KHO SÁCH      \n";
        cout << "=========================================\n";
        cout << "1. Thêm tài nguyên mới (Book/EBook/Journal)\n";
        cout << "2. Xóa tài nguyên theo ID\n";
        cout << "3. Cập nhật thông tin tài nguyên\n";
        cout << "4. Hiển thị danh sách tài nguyên trong RAM\n";
        cout << "0. Quay lại / Thoát\n";
        cout << "-----------------------------------------\n";
        cout << "Vui lòng chọn chức năng (0-4): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[Lỗi] Vui lòng nhập số hợp lệ!\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleAddResource(manager);
                break;
            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                handleRemoveResource(manager);
                break;
            case 3: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string id = inputLine("Nhập ID cần sửa: ");
                string newTitle = inputLine("Nhập tiêu đề mới: ");
                string newAuthor = inputLine("Nhập tác giả mới: ");
                manager.update(id, newTitle, newAuthor);
                break;
            }
            case 4:
                manager.displayAll();
                break;
            case 0:
                cout << "Đã thoát Menu Quản lý kho.\n";
                return;
            default:
                cout << "[Lỗi] Lựa chọn không hợp lệ, vui lòng chọn lại!\n";
                break;
        }
    }
}

// Hàm main dùng để test chạy trực tiếp module này
int main() {
    ResourceManager manager;
    
    // Thêm sẵn 1 vài phần tử mẫu để kiểm tra dữ liệu trong RAM
    manager.add(new Book("B01", "Lap trinh huong doi tuong", "Nguyen Van A", 350, "978-604-01"));
    manager.add(new EBook("EB01", "Clean Code", "Robert C. Martin", 15.5, "PDF"));
    manager.add(new Journal("J01", "IEEE Software Trends", "IEEE", 12, 2024));

    // Khởi chạy Menu Admin
    runAdminInventoryMenu(manager);

    return 0;
}
