#ifndef MEMBER_MANAGER_H
#define MEMBER_MANAGER_H

#include <vector>
#include <string>
#include <iostream>

// ==========================================
// Basic Abstract Member Class & Derived Classes
// ==========================================
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

    virtual void displayInfo() const = 0;
    virtual std::string getMemberType() const = 0;
};

// Student Member Class
class StudentMember : public AbstractMember {
public:
    StudentMember(const std::string& memberId, const std::string& memberName)
        : AbstractMember(memberId, memberName) {}

    void displayInfo() const override {
        std::cout << "[Sinh Vien] ID: " << id << " | Ho Ten: " << name << std::endl;
    }

    std::string getMemberType() const override {
        return "Student";
    }
};

// Faculty Member Class
class FacultyMember : public AbstractMember {
public:
    FacultyMember(const std::string& memberId, const std::string& memberName)
        : AbstractMember(memberId, memberName) {}

    void displayInfo() const override {
        std::cout << "[Giang Vien] ID: " << id << " | Ho Ten: " << name << std::endl;
    }

    std::string getMemberType() const override {
        return "Faculty";
    }
};

// ==========================================
// Member Manager Class Header
// ==========================================
class MemberManager {
private:
    // Vector truong quan ly cac con tro AbstractMember trong bộ nhớ RAM
    std::vector<AbstractMember*> members;

public:
    MemberManager();
    ~MemberManager(); // Destructor de giai phong bo nho (tranh memory leak)

    // Cac ham quan ly chinh
    void addMember(AbstractMember* member);
    bool updateMember(const std::string& id, const std::string& newName);
    bool deleteMember(const std::string& id);
    AbstractMember* findMemberById(const std::string& id) const;
    void displayAllMembers() const;

    // Getter danh sach vector
    const std::vector<AbstractMember*>& getMembers() const;
};

#endif // MEMBER_MANAGER_H
