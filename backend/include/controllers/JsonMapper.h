#pragma once
#include "models/Library.h"
#include "services/LibraryApp.h"
#include "utils/Json.h"

class JsonMapper {
public:
    explicit JsonMapper(LibraryApp& app) : app_(app) {}

    Json resource(const LibraryResource& resource) const;
    Json member(const Member& member) const;
    Json loan(const Loan& loan) const;
    Json reservation(const Reservation& reservation) const;
    Json queueOf(int resourceId) const;         
    Json reservationQueues() const;             
    Json stats(const InventoryStats& stats) const;
    Json loanList(const std::vector<Loan>& loans, size_t limit = 0) const;  

private:
    LibraryApp& app_;
};
