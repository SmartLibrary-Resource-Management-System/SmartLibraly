#ifndef ABSTRACT_MEMBER_H
#define ABSTRACT_MEMBER_H

#include <string>

enum class Role {
    LIBRARIAN,
    MEMBER
};
class AbstractMember {
protected:
    std::string memberId;
    std::string fullName;
    std::string email;
    std::string phoneNumber;
    int borrowedBooksCount;

public:
    AbstractMember(std::string id, std::string name, std::string mail, std::string phone)
        : memberId(id), fullName(name), email(mail), phoneNumber(phone), borrowedBooksCount(0) {}

    virtual ~AbstractMember() = default;

    virtual double calculateFine(int overdueDays) const = 0;
    virtual int getMaxLoanLimit() const = 0;
    virtual Role getRole() const = 0;

    std::string getMemberId() const { return memberId; }
    std::string getFullName() const { return fullName; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phoneNumber; }
    int getBorrowedBooksCount() const { return borrowedBooksCount; }

    void incrementBorrowedCount() { borrowedBooksCount++; }
    void decrementBorrowedCount() { if (borrowedBooksCount > 0) borrowedBooksCount--; }
};

class StudentMember : public AbstractMember {
private:
    std::string studentId;
    std::string major;
    int academicYear;

public:
    StudentMember(std::string id, std::string name, std::string mail, std::string phone, 
                  std::string sId, std::string m, int year)
        : AbstractMember(id, name, mail, phone), studentId(sId), major(m), academicYear(year) {}

    double calculateFine(int overdueDays) const override {
        return overdueDays > 0 ? overdueDays * 5000.0 : 0.0; 
    }

    int getMaxLoanLimit() const override {
        return 3;
    }

    Role getRole() const override {
        return Role::MEMBER;
    }
};

class FacultyMember : public AbstractMember {
private:
    std::string employeeId;
    std::string department;
    std::string academicTitle;

public:
    FacultyMember(std::string id, std::string name, std::string mail, std::string phone, 
                  std::string eId, std::string dept, std::string title)
        : AbstractMember(id, name, mail, phone), employeeId(eId), department(dept), academicTitle(title) {}
    
    virtual ~FacultyMember() override = default;

    double calculateFine(int overdueDays) const override {
        return 0.0; 
    }

    int getMaxLoanLimit() const override {
        return 5;
    }

    Role getRole() const override {
        return Role::MEMBER;
    }
};

#endif
