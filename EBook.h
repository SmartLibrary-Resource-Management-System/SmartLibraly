#ifndef EBOOK_H
#define EBOOK_H

#include "AbstractLibraryResource.h"

/**
 * @brief Lớp đại diện cho Sách điện tử (E-Book).
 */
class EBook : public AbstractLibraryResource {
private:
    std::string isbn;
    std::string fileFormat;      // e.g., PDF, EPUB
    double fileSizeMB;           // e.g., 15.5 MB
    std::string downloadUrl;     // Đường dẫn tải hoặc đọc online
    int activeBorrows;           // Số người đang đọc đồng thời
    int maxConcurrentLicenses;   // Giới hạn lượt mượn đồng thời (0 nếu không giới hạn)

public:
    EBook(const std::string& id,
          const std::string& title,
          const std::string& author,
          const std::string& genre,
          const std::string& publisher,
          int publicationYear,
          const std::string& isbn,
          const std::string& fileFormat,
          double fileSizeMB,
          const std::string& downloadUrl,
          int maxConcurrentLicenses = 0)
        : AbstractLibraryResource(id, title, author, genre, publisher, publicationYear),
          isbn(isbn), fileFormat(fileFormat), fileSizeMB(fileSizeMB),
          downloadUrl(downloadUrl), activeBorrows(0),
          maxConcurrentLicenses(maxConcurrentLicenses) {}

    virtual ~EBook() override = default;

    // Getters
    std::string getIsbn() const { return isbn; }
    std::string getFileFormat() const { return fileFormat; }
    double getFileSizeMB() const { return fileSizeMB; }
    std::string getDownloadUrl() const { return downloadUrl; }
    int getActiveBorrows() const { return activeBorrows; }
    int getMaxConcurrentLicenses() const { return maxConcurrentLicenses; }

    // Implement pure virtual functions
    std::string getResourceType() const override {
        return "E-Book";
    }

    bool isAvailable() const override {
        if (maxConcurrentLicenses <= 0) return true; // Không giới hạn bản quyền số
        return activeBorrows < maxConcurrentLicenses;
    }

    bool borrowItem() override {
        if (isAvailable()) {
            activeBorrows++;
            return true;
        }
        return false;
    }

    void returnItem() override {
        if (activeBorrows > 0) {
            activeBorrows--;
        }
    }

    void displayDetails() const override {
        std::cout << "========================================" << std::endl;
        std::cout << "[E-BOOK] " << title << " (" << publicationYear << ")" << std::endl;
        std::cout << "  - ID: " << id << std::endl;
        std::cout << "  - Author: " << author << std::endl;
        std::cout << "  - Genre: " << genre << std::endl;
        std::cout << "  - Format: " << fileFormat << " (" << fileSizeMB << " MB)" << std::endl;
        std::cout << "  - ISBN: " << isbn << std::endl;
        std::cout << "  - Download Link: " << downloadUrl << std::endl;
        if (maxConcurrentLicenses > 0) {
            std::cout << "  - Active Reads: " << activeBorrows << "/" << maxConcurrentLicenses << std::endl;
        } else {
            std::cout << "  - License: Unlimited concurrent access" << std::endl;
        }
        std::cout << "========================================" << std::endl;
    }
};

#endif // EBOOK_H
