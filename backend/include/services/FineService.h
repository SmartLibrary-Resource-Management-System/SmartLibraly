#pragma once
#include <string>

#include "models/LibraryResource.h"
#include "models/Member.h"

class FineService {
public:
    double calculateFine(const Member& member, const LibraryResource& resource, int overdueDays) const;
    std::string describePolicy(const Member& member, const LibraryResource& resource) const;
};
