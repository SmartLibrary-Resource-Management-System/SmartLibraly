#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>


bool FileManager::saveResources(const std::vector<AbstractLibraryResource*>& resources, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[Error] Không thể mở file: " << filename << std::endl;
        return false;
    }

    for (const auto* res : resources) {
        if (!res) continue;

        std::string type = res->getResourceType();

        if (type == "Physical Book") {
            const Book* b = dynamic_cast<const Book*>(res);
            if (b) {
                file << "BOOK|" << b->getResourceId() << "|" << b->getTitle() << "|"
                     << b->getAuthor() << "|" << b->getCategory() << "|" << b->getPublisher() << "|"
                     << b->getPublishYear() << "|" << b->getIsbn() << "|" << b->getTotalCopies() << "|"
                     << b->getShelfLocation() << "|" << b->getPageCount() << "\n";
            }
        } 
        else if (type == "E-Book") {
            const EBook* eb = dynamic_cast<const EBook*>(res);
            if (eb) {
                file << "EBOOK|" << eb->getResourceId() << "|" << eb->getTitle() << "|"
                     << eb->getAuthor() << "|" << eb->getCategory() << "|" << eb->getPublisher() << "|"
                     << eb->getPublishYear() << "|" << eb->getIsbn() << "|" << eb->getFileFormat() << "|"
                     << eb->getFileSizeMB() << "|" << eb->getDownloadUrl() << "|" << eb->getMaxConcurrentLicenses() << "\n";
            }
        } 
        else if (type == "Academic Journal") {
            const Journal* j = dynamic_cast<const Journal*>(res);
            if (j) {
                file << "JOURNAL|" << j->getResourceId() << "|" << j->getTitle() << "|"
                     << j->getAuthor() << "|" << j->getCategory() << "|" << j->getPublisher() << "|"
                     << j->getPublishYear() << "|" << j->getIssn() << "|" << j->getVolume() << "|"
                     << j->getIssueNumber() << "|" << j->getDoi() << "|" << j->getImpactFactor() << "|"
                     << j->getAvailableCopies() << "\n";
            }
        }
    }

    file.close();
    std::cout << "[Success] Đã lưu danh sách tài nguyên vào " << filename << std::endl;
    return true;
}

bool FileManager::loadResources(std::vector<AbstractLibraryResource*>& resources, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "[Info] Chưa có file dữ liệu " << filename << ". Tạo danh sách mới." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string type;
        std::getline(ss, type, '|');

        if (type == "BOOK") {
            std::string id, title, author, genre, publisher, yearStr, isbn, totalCopiesStr, shelf, pageStr;
            std::getline(ss, id, '|');
            std::getline(ss, title, '|');
            std::getline(ss, author, '|');
            std::getline(ss, genre, '|');
            std::getline(ss, publisher, '|');
            std::getline(ss, yearStr, '|');
            std::getline(ss, isbn, '|');
            std::getline(ss, totalCopiesStr, '|');
            std::getline(ss, shelf, '|');
            std::getline(ss, pageStr, '|');

            Book* b = new Book(id, title, author, genre, publisher, std::stoi(yearStr),
                               isbn, std::stoi(totalCopiesStr), shelf, std::stoi(pageStr));
            resources.push_back(b);
        }
        else if (type == "EBOOK") {
            std::string id, title, author, genre, publisher, yearStr, isbn, format, sizeStr, url, licensesStr;
            std::getline(ss, id, '|');
            std::getline(ss, title, '|');
            std::getline(ss, author, '|');
            std::getline(ss, genre, '|');
            std::getline(ss, publisher, '|');
            std::getline(ss, yearStr, '|');
            std::getline(ss, isbn, '|');
            std::getline(ss, format, '|');
            std::getline(ss, sizeStr, '|');
            std::getline(ss, url, '|');
            std::getline(ss, licensesStr, '|');

            EBook* eb = new EBook(id, title, author, genre, publisher, std::stoi(yearStr),
                                  isbn, format, std::stod(sizeStr), url, std::stoi(licensesStr));
            resources.push_back(eb);
        }
        else if (type == "JOURNAL") {
            std::string id, title, author, genre, publisher, yearStr, issn, volStr, issueStr, doi, impactStr, copiesStr;
            std::getline(ss, id, '|');
            std::getline(ss, title, '|');
            std::getline(ss, author, '|');
            std::getline(ss, genre, '|');
            std::getline(ss, publisher, '|');
            std::getline(ss, yearStr, '|');
            std::getline(ss, issn, '|');
            std::getline(ss, volStr, '|');
            std::getline(ss, issueStr, '|');
            std::getline(ss, doi, '|');
            std::getline(ss, impactStr, '|');
            std::getline(ss, copiesStr, '|');

            Journal* j = new Journal(id, title, author, genre, publisher, std::stoi(yearStr),
                                     issn, std::stoi(volStr), std::stoi(issueStr), doi,
                                     std::stod(impactStr), std::stoi(copiesStr));
            resources.push_back(j);
        }
    }

    file.close();
    std::cout << "[Success] Nạp tài nguyên từ " << filename << " thành công." << std::endl;
    return true;
}

bool FileManager::saveMembers(const std::vector<AbstractMember*>& members, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[Error] Không thể mở file: " << filename << std::endl;
        return false;
    }

    for (const auto* m : members) {
        if (!m) continue;
        const StudentMember* sm = dynamic_cast<const StudentMember*>(m);
        if (sm) {
            file << "STUDENT|" << sm->getMemberId() << "|" << sm->getFullName() << "|"
                 << sm->getEmail() << "|" << sm->getPhoneNumber() << "\n";
        }

        const FacultyMember* fm = dynamic_cast<const FacultyMember*>(m);
        if (fm) {
            file << "FACULTY|" << fm->getMemberId() << "|" << fm->getFullName() << "|"
                 << fm->getEmail() << "|" << fm->getPhoneNumber() << "\n";
        }
    }

    file.close();
    std::cout << "[Success] Đã lưu danh sách thành viên vào " << filename << std::endl;
    return true;
}

bool FileManager::loadMembers(std::vector<AbstractMember*>& members, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "[Info] Chưa có file dữ liệu " << filename << ". Tạo danh sách mới." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string type;
        std::getline(ss, type, '|');

        if (type == "STUDENT") {
            std::string id, name, email, phone;
            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, email, '|');
            std::getline(ss, phone, '|');

            StudentMember* sm = new StudentMember(id, name, email, phone, id, "General", 1);
            members.push_back(sm);
        }
        else if (type == "FACULTY") {
            std::string id, name, email, phone;
            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, email, '|');
            std::getline(ss, phone, '|');

            FacultyMember* fm = new FacultyMember(id, name, email, phone, id, "Faculty", "Lecturer");
            members.push_back(fm);
        }
    }

    file.close();
    std::cout << "[Success] Nạp thành viên từ " << filename << " thành công." << std::endl;
    return true;
}