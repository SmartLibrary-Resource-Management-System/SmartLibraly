#ifndef BOOK_H
#define BOOK_H

#include "AbstractLibraryResource.h"
#include <iomanip>

/**
 * @brief Lớp đại diện cho Sách vật lý (Physical Book).
 */
class Book : public AbstractLibraryResource {
private:
    std::string isbn;
    int totalCopies;
    int availableCopies;
    std::string shelfLocation;
    int pageCount;

public:
    Book(const std::string& id,
         const std::string& title,
         const std::string& author,
         const std::string& genre,
         const std::string& publisher,
         int publicationYear,
         const std::string& isbn,
         int totalCopies,
         const std::string& shelfLocation,
         int pageCount)
        : AbstractLibraryResource(id, title, author, genre, publisher, publicationYear),
          isbn(isbn), totalCopies(totalCopies), availableCopies(totalCopies),
          shelfLocation(shelfLocation), pageCount(pageCount) {}

    virtual ~Book() override = default;

    // Getters
    std::string getIsbn() const { return isbn; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }
    std::string getShelfLocation() const { return shelfLocation; }
    int getPageCount() const { return pageCount; }

    // Implement pure virtual functions
    std::string getResourceType() const override {
        return "Physical Book";
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
        std::cout << "[BOOK] " << title << " (" << publicationYear << ")" << std::endl;
        std::cout << "  - ID: " << id << std::endl;
        std::cout << "  - Author: " << author << std::endl;
        std::cout << "  - Genre: " << genre << std::endl;
        std::cout << "  - Publisher: " << publisher << std::endl;
        std::cout << "  - ISBN: " << isbn << std::endl;
        std::cout << "  - Shelf Location: " << shelfLocation << std::endl;
        std::cout << "  - Pages: " << pageCount << std::endl;
        std::cout << "  - Availability: " << availableCopies << "/" << totalCopies << " copies" << std::endl;
        std::cout << "========================================" << std::endl;
    }
};

#endif // BOOK_H
