#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// ============================================================================
// 1. LOP TRU TUONG ABSTRACTMEMBER VA CAC LOP CON (STUDENT, FACULTY)
// ============================================================================
class AbstractMember {
protected:
    std::string id;
    std::string name;

public:
    AbstractMember(const std::string& memberId, const std::string& memberName)
        : id(memberId), name(memberName) {}

    virtual ~AbstractMember() {}

    std::string getId() const { return id; }
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    // Phuong thuc ao thuan tuy (Pure virtual functions)
    virtual void displayInfo() const = 0;
    virtual std::string getMemberType() const = 0;
    virtual int getMaxBorrowLimit() const = 0; // Gioi han muon sach
};

// Lop Sinh vien (Duoc muon toi da 3 cuon)
class StudentMember : public AbstractMember {
public:
    StudentMember(const std::string& memberId, const std::string& memberName)
        : AbstractMember(memberId, memberName) {}

    void displayInfo() const override {
        std::cout << "[Sinh Vien] ID: " << std::left << std::setw(8) << id 
                  << " | Ho Ten: " << std::setw(22) << name 
                  << " | Gioi han muon: " << getMaxBorrowLimit() << " cuon" << std::endl;
    }

    std::string getMemberType() const override {
        return "Sinh Vien";
    }

    int getMaxBorrowLimit() const override {
        return 3; // Sinh vien chi duoc muon toi da 3 cuon
    }
};

// Lop Giang vien (Duoc muon toi da 10 cuon)
class FacultyMember : public AbstractMember {
public:
    FacultyMember(const std::string& memberId, const std::string& memberName)
        : AbstractMember(memberId, memberName) {}

    void displayInfo() const override {
        std::cout << "[Giang Vien] ID: " << std::left << std::setw(8) << id 
                  << " | Ho Ten: " << std::setw(22) << name 
                  << " | Gioi han muon: " << getMaxBorrowLimit() << " cuon" << std::endl;
    }

    std::string getMemberType() const override {
        return "Giang Vien";
    }

    int getMaxBorrowLimit() const override {
        return 10; // Giang vien duoc muon toi da 10 cuon
    }
};

// ============================================================================
// 2. MODULE QUAN LY DANH SACH THANH VIEN TRONG RAM (STT 17 - DONG 18)
// ============================================================================
class MemberManager {
private:
    std::vector<AbstractMember*> members; // Luu trư danh sach trong RAM

public:
    MemberManager() {}

    // Destructor: Giai phong toan bo bo nho RAM de tranh ro ri (Memory Leak)
    ~MemberManager() {
        for (AbstractMember* member : members) {
            delete member;
        }
        members.clear();
    }

    // Them thanh vien
    void addMember(AbstractMember* member) {
        if (member == nullptr) return;

        if (findMemberById(member->getId()) != nullptr) {
            std::cout << "[LOI]: Thanh vien voi ID '" << member->getId() << "' da ton tai!" << std::endl;
            delete member; // Giai phong con tro bi trung
            return;
        }

        members.push_back(member);
        std::cout << "=> Da them thanh vien [" << member->getId() << "] thanh cong." << std::endl;
    }

    // Tim kiem thanh vien theo ID
    AbstractMember* findMemberById(const std::string& id) const {
        for (AbstractMember* member : members) {
            if (member->getId() == id) {
                return member;
            }
        }
        return nullptr;
    }

    // Cap nhat / Sua ten thanh vien
    bool updateMember(const std::string& id, const std::string& newName) {
        AbstractMember* member = findMemberById(id);
        if (member != nullptr) {
            member->setName(newName);
            std::cout << "=> Cap nhat ten thanh vien ID [" << id << "] thanh '" << newName << "' thanh cong." << std::endl;
            return true;
        }
        std::cout << "[LOI]: Khong tim thay thanh vien voi ID [" << id << "] de cap nhat." << std::endl;
        return false;
    }

    // Xoa thanh vien
    bool deleteMember(const std::string& id) {
        for (auto it = members.begin(); it != members.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;          // Giai phong bo nho RAM
                members.erase(it);   // Xoa khoi vector
                std::cout << "=> Da xoa thanh vien ID [" << id << "] khoi bo nho RAM." << std::endl;
                return true;
            }
        }
        std::cout << "[LOI]: Khong tim thay thanh vien voi ID [" << id << "] de xoa." << std::endl;
        return false;
    }

    // Hien thi danh sach
    void displayAllMembers() const {
        if (members.empty()) {
            std::cout << "\n[Thong bao]: Danh sach thanh vien trong RAM hien dang rong!" << std::endl;
            return;
        }

        std::cout << "\n================ DANH SACH THANH VIEN (RAM) ================" << std::endl;
        for (const auto& member : members) {
            member->displayInfo();
        }
        std::cout << "============================================================" << std::endl;
    }

    const std::vector<AbstractMember*>& getMembers() const {
        return members;
    }
};

// ============================================================================
// 3. MODULE GIOI HAN MUON SACH (STT 24 - DONG 25 - YEU CAU 2 DE BAI)
// ============================================================================
class BorrowLimitValidator {
public:
    static bool canBorrow(const AbstractMember* member, int currentBorrowedCount) {
        if (member == nullptr) {
            std::cout << "[LOI]: Thong tin thanh vien khong ton tai!" << std::endl;
            return false;
        }

        int maxLimit = member->getMaxBorrowLimit();

        // CHAN neu da muon bang hoac vuot gioi han
        if (currentBorrowedCount >= maxLimit) {
            std::cout << "\n--------------------------------------------------" << std::endl;
            std::cout << "[THONG BAO LOI - VUOT GIOI HAN MUON SACH]" << std::endl;
            std::cout << "  - Thanh vien  : " << member->getName() << " (ID: " << member->getId() << ")" << std::endl;
            std::cout << "  - Loai the    : " << member->getMemberType() << std::endl;
            std::cout << "  - Dang muon   : " << currentBorrowedCount << " / " << maxLimit << " cuon" << std::endl;
            std::cout << "  - PHAN HOI    : [CHAN] " << member->getMemberType() 
                      << " da dat gioi han toi da " << maxLimit << " cuon. Khong the muon them!" << std::endl;
            std::cout << "--------------------------------------------------\n" << std::endl;
            return false;
        }

        std::cout << "=> [HOP LE]: " << member->getMemberType() << " " << member->getName() 
                  << " du dieu kien muon sach (" << currentBorrowedCount << "/" << maxLimit << ")." << std::endl;
        return true;
    }
};

// ============================================================================
// 4. CHUONG TRINH CHINH DEMO TOAN BO CONG VIEC CUA KHANH BAO
// ============================================================================
int main() {
    MemberManager manager;

    std::cout << "==========================================================" << std::endl;
    std::cout << "  CHUONG TRINH QUAN LY THANH VIEN & KIEM TRA GIOI HAN MUON" << std::endl;
    std::cout << "  Nhiem vu: Nguyen Pham Khanh Bao (Dong 18 & Dong 25)" << std::endl;
    std::cout << "==========================================================" << std::endl;

    // --- DEMO CONG VIEC 1: QUAN LY DANH SACH THANH VIEN TRONG RAM ---
    std::cout << "\n>>> 1. KHU VUC DEMO THEM THANH VIEN VAO RAM:" << std::endl;
    manager.addMember(new StudentMember("SV001", "Nguyen Van A"));
    manager.addMember(new StudentMember("SV002", "Tran Thi B"));
    manager.addMember(new FacultyMember("GV001", "PGS.TS Le Van C"));

    manager.displayAllMembers();

    std::cout << "\n>>> 2. KHU VUC DEMO SUA THONG TIN THANH VIEN:" << std::endl;
    manager.updateMember("SV001", "Nguyen Van A (Da cap nhat)");
    manager.displayAllMembers();

    // --- DEMO CONG VIEC 2: KIEM TRA GIOI HAN MUON SACH (YEU CAU 2) ---
    std::cout << "\n>>> 3. KHU VUC DEMO KIEM TRA GIOI HAN MUON SACH (YEU CAU 2):" << std::endl;

    AbstractMember* sv1 = manager.findMemberById("SV001");
    AbstractMember* gv1 = manager.findMemberById("GV001");

    // Thu nghiem truong hop Sinh vien muon 2 cuon (Hop le)
    std::cout << "\n- Kiem tra Sinh vien khi dang muon 2 cuon:" << std::endl;
    BorrowLimitValidator::canBorrow(sv1, 2);

    // Thu nghiem truong hop Sinh vien muon 3 cuon (Da dat toi da 3 -> Chan)
    std::cout << "\n- Kiem tra Sinh vien khi dang muon 3 cuon (Thu muon cuon thu 4):" << std::endl;
    BorrowLimitValidator::canBorrow(sv1, 3);

    // Thu nghiem truong hop Giang vien muon 5 cuon (Hop le vi max = 10)
    std::cout << "\n- Kiem tra Giang vien khi dang muon 5 cuon:" << std::endl;
    BorrowLimitValidator::canBorrow(gv1, 5);

    // Thu nghiem truong hop Giang vien muon 10 cuon (Da dat toi da 10 -> Chan)
    std::cout << "\n- Kiem tra Giang vien khi dang muon 10 cuon (Thu muon cuon thu 11):" << std::endl;
    BorrowLimitValidator::canBorrow(gv1, 10);

    // --- DEMO XOA THANH VIEN ---
    std::cout << "\n>>> 4. KHU VUC DEMO XOA THANH VIEN VAK BO NHO RAM:" << std::endl;
    manager.deleteMember("SV002");
    manager.displayAllMembers();

    std::cout << "=> Chuong trinh ket thuc. Bo nho RAM duoc tu dong giai phong an toan.\n" << std::endl;

    return 0;
}
