#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager() {
    // Khởi tạo danh sách rỗng
}

ResourceManager::~ResourceManager() {
    // Thu hồi toàn bộ bộ nhớ động đã cấp phát cho các đối tượng tài nguyên
    for (AbstractLibraryResource* res : resources) {
        delete res;
    }
    resources.clear();
}

void ResourceManager::addResource(AbstractLibraryResource* resource) {
    if (resource == nullptr) {
        std::cout << "[Lỗi] Không thể thêm con trỏ null vào danh sách!\n";
        return;
    }
    resources.push_back(resource);
    std::cout << "[Thành công] Đã thêm tài nguyên ID: " << resource->getId() << "\n";
}

bool ResourceManager::removeResource(const std::string& id) {
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it; // Giải phóng vùng nhớ heap
            resources.erase(it); // Xóa con trỏ khỏi vector
            std::cout << "[Thành công] Đã xóa tài nguyên ID: " << id << "\n";
            return true;
        }
    }
    std::cout << "[Thất bại] Không tìm thấy tài nguyên với ID: " << id << " để xóa.\n";
    return false;
}

bool ResourceManager::updateResource(const std::string& id, const std::string& newTitle, const std::string& newAuthor) {
    AbstractLibraryResource* res = findResourceById(id);
    if (res != nullptr) {
        res->setTitle(newTitle);
        res->setAuthor(newAuthor);
        std::cout << "[Thành công] Đã cập nhật thông tin tài nguyên ID: " << id << "\n";
        return true;
    }
    std::cout << "[Thất bại] Không tìm thấy tài nguyên với ID: " << id << " để cập nhật.\n";
    return false;
}

AbstractLibraryResource* ResourceManager::findResourceById(const std::string& id) const {
    for (AbstractLibraryResource* res : resources) {
        if (res != nullptr && res->getId() == id) {
            return res;
        }
    }
    return nullptr;
}

void ResourceManager::displayAll() const {
    if (resources.empty()) {
        std::cout << "Danh sách tài nguyên trong RAM hiện đang trống.\n";
        return;
    }
    std::cout << "===== DANH SÁCH TÀI NGUYÊN HIỆN CÓ =====\n";
    for (const auto& res : resources) {
        if (res != nullptr) {
            res->displayInfo();
        }
    }
    std::cout << "========================================\n";
}

const std::vector<AbstractLibraryResource*>& ResourceManager::getResources() const {
    return resources;
}