#ifndef JOURNAL_H
#define JOURNAL_H

#include "AbstractLibraryResource.h"

/**
 * @brief Lớp đại diện cho Tạp chí khoa học (Academic Journal).
 */
class Journal : public AbstractLibraryResource {
private:
    std::string issn;
    int volume;
    int issueNumber;
    std::string doi;
    double impactFactor;
    int availableCopies;
    int totalCopies;

public:
    Journal(const std::string& id,
            const std::string& title,
            const std::string& author,
            const std::string& genre,
            const std::string& publisher,
            int publicationYear,
            const std::string& issn,
            int volume,
            int issueNumber,
            const std::string& doi,
            double impactFactor = 0.0,
            int totalCopies = 1)
        : AbstractLibraryResource(id, title, author, genre, publisher, publicationYear),
          issn(issn), volume(volume), issueNumber(issueNumber),
          doi(doi), impactFactor(impactFactor),
          totalCopies(totalCopies), availableCopies(totalCopies) {}

    virtual ~Journal() override = default;

    // Getters
    std::string getIssn() const { return issn; }
    int getVolume() const { return volume; }
    int getIssueNumber() const { return issueNumber; }
    std::string getDoi() const { return doi; }
    double getImpactFactor() const { return impactFactor; }
    int getAvailableCopies() const { return availableCopies; }

    // Implement pure virtual functions
    std::string getResourceType() const override {
        return "Academic Journal";
    }

    bool isAvailable() const override {
        return availableCopies > 0;
    }

    bool borrowItem() override {
        if (availableCopies > 0) {
            availableCopies--;
            return true;
        }
        return false;
    }

    void returnItem() override {
        if (availableCopies < totalCopies) {
            availableCopies++;
        }
    }

    void displayDetails() const override {
        std::cout << "========================================" << std::endl;
        std::cout << "[JOURNAL] " << title << " (" << publicationYear << ")" << std::endl;
        std::cout << "  - ID: " << id << std::endl;
        std::cout << "  - Editor/Author: " << author << std::endl;
        std::cout << "  - ISSN: " << issn << " | Vol: " << volume << ", Issue: " << issueNumber << std::endl;
        std::cout << "  - DOI: " << doi << std::endl;
        std::cout << "  - Impact Factor: " << impactFactor << std::endl;
        std::cout << "  - Availability: " << availableCopies << "/" << totalCopies << " copies" << std::endl;
        std::cout << "========================================" << std::endl;
    }
};

#endif // JOURNAL_H
