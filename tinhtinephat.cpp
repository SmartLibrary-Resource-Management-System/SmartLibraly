#include <iostream>
#include <string>

using namespace std;

class AbstractMember {
protected:
    string memberID;
    string fullName;
public:
    AbstractMember(string id, string name) : memberID(id), fullName(name) {}
    virtual ~AbstractMember() {}

    virtual double PolymorphiccalculateFine(int overdueDays) const = 0;
};

class StudentMember : public AbstractMember {
public:
    StudentMember(string id, string name) : AbstractMember(id, name) {}

    double PolymorphiccalculateFine(int overdueDays) const override {
        if (overdueDays <= 0) return 0.0;
        const double FINE_PER_DAY = 10000.0; // 10k/ngày
        return overdueDays * FINE_PER_DAY;
    }
};

class FacultyMember : public AbstractMember {
public:
    FacultyMember(string id, string name) : AbstractMember(id, name) {}

    double PolymorphiccalculateFine(int overdueDays) const override {
        if (overdueDays <= 0) return 0.0;
        const double FINE_PER_DAY = 5000.0; // 5k/ngày
        return overdueDays * FINE_PER_DAY;
    }
};