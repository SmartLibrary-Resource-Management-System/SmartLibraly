#pragma once
#include <string>

class FinePolicy {
public:
    virtual ~FinePolicy() = default;
    virtual double calculateFine(int overdueDays) const = 0;
    virtual std::string describe() const = 0;
};

class StudentFinePolicy : public FinePolicy {
public:
    static constexpr double RATE_FACTOR = 1.0;
    explicit StudentFinePolicy(double resourceRatePerDay);
    double calculateFine(int overdueDays) const override;
    std::string describe() const override;

private:
    double ratePerDay_;
};

class FacultyFinePolicy : public FinePolicy {
public:
    static constexpr double RATE_FACTOR = 0.5;
    static constexpr int GRACE_DAYS = 3;
    explicit FacultyFinePolicy(double resourceRatePerDay);
    double calculateFine(int overdueDays) const override;
    std::string describe() const override;

private:
    double ratePerDay_;
};
