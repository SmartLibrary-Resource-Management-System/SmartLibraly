#pragma once
#include <filesystem>
#include <string>

#include "models/Library.h"


class LibraryFileRepository {
public:
    explicit LibraryFileRepository(std::filesystem::path dataDirectory) : dir_(std::move(dataDirectory)) {}

    void save(const Library& library) const;
    void load(Library& library) const;  // throws PersistenceException
    bool hasData() const;
    const std::filesystem::path& directory() const { return dir_; }
    static const char* const* fileNames();  // NULL-terminated list

private:
    std::filesystem::path dir_;
};
