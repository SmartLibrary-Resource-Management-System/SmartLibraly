#pragma once
#include <optional>
#include <string>
#include <vector>

#include "models/Library.h"
#include "services/ReservationService.h"

struct SearchCriteria {
    std::string query;   
    std::string title, author, isbn, genre, type;
    std::optional<bool> availableOnly;  
    bool hasTextCriteria() const;
};


class SearchService {
public:
    SearchService(const Library& library, const ReservationService& reservations)
        : library_(library), reservations_(reservations) {}

    using Results = std::vector<const LibraryResource*>;
    Results searchByTitle(const std::string& query) const;
    Results searchByAuthor(const std::string& query) const;
    Results searchByISBN(const std::string& query) const;  
    Results searchByGenre(const std::string& query) const;
    Results searchAll(const std::string& query) const;
    const LibraryResource* findByExactIdentifier(const std::string& identifier) const;  

    Results search(const SearchCriteria& criteria) const;  
    Results filter(const SearchCriteria& criteria) const;  

private:
    Results allResources() const;
    const Library& library_;
    const ReservationService& reservations_;
};
