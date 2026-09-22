#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <vector>
#include <string>
#include "AbstractLibraryResource.h"

class ResourceManager {
private:
    // Mảng động quản lý con trỏ tài nguyên đa hình trong RAM
    std::vector<AbstractLibraryResource*> resources;

public:
    ResourceManager();
    ~ResourceManager();

    // Thêm một tài nguyên mới vào danh sách
    void addResource(AbstractLibraryResource* resource);

    // Xóa tài nguyên theo mã ID, giải phóng vùng nhớ tương ứng
    bool removeResource(const std::string& id);

    // Cập nhật thông tin tiêu đề và tác giả theo ID
    bool updateResource(const std::string& id, const std::string& newTitle, const std::string& newAuthor);

    // Tìm kiếm con trỏ tài nguyên theo ID (hỗ trợ kiểm tra/cập nhật sâu)
    AbstractLibraryResource* findResourceById(const std::string& id) const;

    // Hiển thị toàn bộ danh sách tài nguyên hiện có trong RAM
    void displayAll() const;

    // Lấy tham chiếu đến vector tài nguyên để các module khác (Search Engine, Loan Workflow) sử dụng
    const std::vector<AbstractLibraryResource*>& getResources() const;
};

#endif // RESOURCE_MANAGER_H