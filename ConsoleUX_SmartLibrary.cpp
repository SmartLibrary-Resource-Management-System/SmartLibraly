#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>

// ============================================================================
// HỆ THỐNG HOÀN THIỆN UX CONSOLE (STT 31 - DÒNG 32) - NGUYỄN PHẠM KHÁNH BẢO
// Giải quyết các vấn đề:
// 1. Chữ bị dính vào nhau -> Thêm căn lề (iomanip), khoảng trống và định dạng bảng.
// 2. Menu không thoát ra được trang trước -> Xây dựng điều hướng luồng menu chuẩn (Back/Exit).
// 3. Lỗi nhập liệu trôi lệnh -> Xử lý cin.ignore() và xóa bộ nhớ đệm (buffer).
// 4. Màn hình rác -> Hàm xóa màn hình (clearScreen) và tạm dừng xem kết quả (pauseScreen).
// ============================================================================

// --- 1. CAC HAM TIEN ICH GIAO DIEN (UX UTILS) ---
class ConsoleUX {
public:
    // Xóa màn hình Console (Hỗ trợ cả Windows và Linux/Mac)
    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    // Tạm dừng màn hình để người dùng đọc thông tin trước khi quay lại
    static void pauseScreen() {
        std::cout << "\n[Bam Enter de tiep tuc...]";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }

    // In tiêu đề trang đẹp mắt, căn giữa, tránh dính chữ
    static void printHeader(const std::string& title) {
        clearScreen();
        std::cout << "==========================================================" << std::endl;
        std::cout << "   " << title << std::endl;
        std::cout << "==========================================================" << std::endl;
    }

    // In dòng phân cách phân đoạn
    static void printDivider() {
        std::cout << "----------------------------------------------------------" << std::endl;
    }

    // In thông báo lỗi rõ ràng
    static void printError(const std::string& message) {
        std::cout << "\n[LOI HIEN THI]: " << message << std::endl;
    }

    // In thông báo thành công
    static void printSuccess(const std::string& message) {
        std::cout << "\n[THANH CONG]: " << message << std::endl;
    }
};

// --- 2. MO PHONG DU LIEU THANH VIEN & SACH (Dung de test UX) ---
struct Member {
    std::string id;
    std::string name;
    std::string type;
    int borrowedCount;
};

// --- 3. MO PHONG CAC CHUC NANG THEO MENU DUOC CHUAN HOA UX ---
class SmartLibraryApp {
private:
    std::vector<Member> members;

public:
    SmartLibraryApp() {
        // Dữ liệu mẫu ban đầu
        members.push_back({"SV001", "Nguyen Van A", "Sinh Vien", 2});
        members.push_back({"GV001", "PGS.TS Le Van C", "Giang Vien", 5});
    }

    // HIỂN THỊ BẢNG DANH SÁCH - Fix lỗi dính chữ bằng std::setw
    void displayMemberList() {
        ConsoleUX::printHeader("DANH SACH THANH VIEN THU VIEN");

        if (members.empty()) {
            std::cout << "\n  (Danh sach dang rong!)" << std::endl;
        } else {
            // In Tiêu đề cột chuẩn hóa độ rộng
            std::cout << std::left 
                      << std::setw(10) << "STT/ID" 
                      << std::setw(25) << "Ho va Ten" 
                      << std::setw(15) << "Chuc Vu" 
                      << std::setw(12) << "Da Muon" << std::endl;
            ConsoleUX::printDivider();

            // In dữ liệu căn lề ngay ngắn
            for (const auto& m : members) {
                std::cout << std::left 
                          << std::setw(10) << m.id 
                          << std::setw(25) << m.name 
                          << std::setw(15) << m.type 
                          << std::setw(12) << (std::to_string(m.borrowedCount) + " cuon") << std::endl;
            }
            ConsoleUX::printDivider();
        }
        ConsoleUX::pauseScreen();
    }

    // THÊM THÀNH VIÊN - Xử lý nhập liệu chuẩn tránh trôi dòng
    void addMemberUI() {
        ConsoleUX::printHeader("THEM THANH VIEN MOI");

        std::string id, name;
        int typeChoice;

        std::cout << "Nhap ID thanh vien (vd: SV003): ";
        std::cin >> id;

        std::cout << "Nhap Ho va Ten: ";
        std::cin.ignore(10000, '\n'); // Xóa bộ nhớ đệm
        std::getline(std::cin, name);

        std::cout << "Chon Loai the (1. Sinh Vien | 2. Giang Vien): ";
        while (!(std::cin >> typeChoice) || (typeChoice != 1 && typeChoice != 2)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            ConsoleUX::printError("Lua chon khong hop le! Vui long nhap 1 hoac 2: ");
        }

        std::string typeStr = (typeChoice == 1) ? "Sinh Vien" : "Giang Vien";
        members.push_back({id, name, typeStr, 0});

        ConsoleUX::printSuccess("Da them thanh vien [" + name + "] vao he thong!");
        ConsoleUX::pauseScreen();
    }

    // SUB-MENU QUẢN LÝ THÀNH VIÊN - Cho phép QUAY LẠI TRANG TRƯỚC
    void memberManagementSubMenu() {
        int choice = -1;
        while (choice != 0) { // 0 = Quay lại trang trước
            ConsoleUX::printHeader("SUB-MENU: QUAN LY THANH VIEN");
            std::cout << "  1. Xem danh sach thanh vien" << std::endl;
            std::cout << "  2. Them thanh vien moi" << std::endl;
            std::cout << "  0. <-- QUAY LAI MENU CHINH" << std::endl;
            ConsoleUX::printDivider();
            std::cout << "Nhap lua chon cua ban [0-2]: ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                ConsoleUX::printError("Nhap sai dinh dang! Vui long nhap so.");
                ConsoleUX::pauseScreen();
                continue;
            }

            switch (choice) {
                case 1:
                    displayMemberList();
                    break;
                case 2:
                    addMemberUI();
                    break;
                case 0:
                    // Thoát khỏi vòng lặp sub-menu -> Tự động quay lại Menu chính
                    std::cout << "\n[Dang quay lai Menu chinh...]" << std::endl;
                    break;
                default:
                    ConsoleUX::printError("Lựa chon khong co trong danh sach!");
                    ConsoleUX::pauseScreen();
                    break;
            }
        }
    }

    // MAIN MENU HE THONG
    void run() {
        int mainChoice = -1;
        while (mainChoice != 0) {
            ConsoleUX::printHeader("HE THONG QUAN LY THU VIEN THONG MINH");
            std::cout << "  1. Quan ly Thanh vien (Sub-Menu)" << std::endl;
            std::cout << "  2. Rà soat Giao dien & Kiem tra Console (Demo UX)" << std::endl;
            std::cout << "  0. THOAT CHUONG TRINH" << std::endl;
            ConsoleUX::printDivider();
            std::cout << "Nhap lua chon [0-2]: ";

            if (!(std::cin >> mainChoice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                ConsoleUX::printError("Nhap sai! Vui long nhap phim so.");
                ConsoleUX::pauseScreen();
                continue;
            }

            switch (mainChoice) {
                case 1:
                    memberManagementSubMenu(); // Chuyển sang Sub-menu (có thể quay lại)
                    break;
                case 2:
                    ConsoleUX::printHeader("DEMO RA SOAT UX CONSOLE");
                    std::cout << "- Cac loi da duoc khac phuc:" << std::endl;
                    std::cout << "  [x] In chu khong con bi dinh vao nhau nhờ std::setw." << std::endl;
                    std::cout << "  [x] Menu đã co muc '0. QUAY LAI' de tro ve trang truoc." << std::endl;
                    std::cout << "  [x] Xoa man hinh va tam dung sau moi thao tac." << std::endl;
                    ConsoleUX::pauseScreen();
                    break;
                case 0:
                    ConsoleUX::printHeader("QUAY LAI / THOAT");
                    std::cout << "\nCam on ban da su dung phan mem! Tam biet.\n" << std::endl;
                    break;
                default:
                    ConsoleUX::printError("Lua chon khong hop le!");
                    ConsoleUX::pauseScreen();
                    break;
            }
        }
    }
};

// --- 4. HAM MAIN CHAY CHUONG TRINH ---
int main() {
    SmartLibraryApp app;
    app.run();
    return 0;
}
