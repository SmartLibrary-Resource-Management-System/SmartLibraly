#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "AbstractLibraryResource.h"
#include "Book.h"
#include "EBook.h"
#include "Journal.h"
#include "AbstractMember.h"

class FileManager {
public:
    
    static bool saveResources(const std::vector<AbstractLibraryResource*>& resources, const std::string& filename);
    static bool loadResources(std::vector<AbstractLibraryResource*>& resources, const std::string& filename);

    static bool saveMembers(const std::vector<AbstractMember*>& members, const std::string& filename);
    static bool loadMembers(std::vector<AbstractMember*>& members, const std::string& filename);
    static bool exportInventoryReport(const std::vector<AbstractLibraryResource*>& resources, 
                                  const std::vector<AbstractMember*>& members, 
                                  const std::string& filename = "inventory_report.txt");
};

#endif 