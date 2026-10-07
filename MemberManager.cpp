#include "MemberManager.h"

MemberManager::MemberManager() {}

// Destructor: Tu dong giai phong toan bo con tro trong vector khi huy doi tuong
MemberManager::~MemberManager() {
    for (AbstractMember* member : members) {
        delete member; // Giai phong bo nho RAM
    }
    members.clear();
}

// 1. HAM THEM THANH VIEN
void MemberManager::addMember(AbstractMember* member) {
    if (member == nullptr) return;

    // Kiem tra trung ID
    if (findMemberById(member->getId()) != nullptr) {
        std::cout << "Loi: Thanh vien voi ID '" << member->getId() << "' da ton tai!" << std::endl;
        delete member; // Giai phong con tro vua tao neu bi trung de tranh memory leak
        return;
    }

    members.push_back(member);
    std::cout << "Da them thanh vien [" << member->getId() << "] thanh cong." << std::endl;
}

// 2. HAM TIM KIEM THANH VIEN THEO ID
AbstractMember* MemberManager::findMemberById(const std::string& id) const {
    for (AbstractMember* member : members) {
        if (member->getId() == id) {
            return member;
        }
    }
    return nullptr;
}

// 3. HAM SUA THONG TIN THANH VIEN (Cap nhat ten)
bool MemberManager::updateMember(const std::string& id, const std::string& newName) {
    AbstractMember* member = findMemberById(id);
    if (member != nullptr) {
        member->setName(newName);
        std::cout << "Cap nhat thong tin thanh vien ID [" << id << "] thanh cong." << std::endl;
        return true;
    }
    std::cout << "Khong tim thay thanh vien voi ID [" << id << "] de cap nhat." << std::endl;
    return false;
}

// 4. HAM XOA THANH VIEN
bool MemberManager::deleteMember(const std::string& id) {
    for (auto it = members.begin(); it != members.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;          // Giai phong vung nho RAM cua doi tuong
            members.erase(it);   // Xoa con tro khoi vector
            std::cout << "Da xoa thanh vien ID [" << id << "] thanh cong." << std::endl;
            return true;
        }
    }
    std::cout << "Khong tim thay thanh vien voi ID [" << id << "] de xoa." << std::endl;
    return false;
}

// 5. HAM HIEN THI DANH SACH THANH VIEN
void MemberManager::displayAllMembers() const {
    if (members.empty()) {
        std::cout << "Danh sach thanh vien trong RAM hien dang rong." << std::endl;
        return;
    }

    std::cout << "\n=== DANH SACH THANH VIEN (RAM) ===" << std::endl;
    for (const auto& member : members) {
        member->displayInfo();
    }
    std::cout << "===================================\n" << std::endl;
}

const std::vector<AbstractMember*>& MemberManager::getMembers() const {
    return members;
}
