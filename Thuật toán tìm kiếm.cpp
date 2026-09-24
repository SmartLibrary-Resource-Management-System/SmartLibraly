#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct LibraryResource {
    std::string title;
    std::string author;
    std::string isbn;
    std::string genre;
};

struct GenrePredicate {
    std::string targetGenre;
    GenrePredicate(std::string g) : targetGenre(g) {}
    bool operator()(const LibraryResource& res) const {
        return res.genre == targetGenre;
    }
};

int main() {
    std::vector<LibraryResource> resources = {
        {"C++ Primer", "Stanley B. Lippman", "978-0321714114", "Education"},
        {"The Hobbit", "J.R.R. Tolkien", "978-0547928227", "Fantasy"},
        {"Clean Code", "Robert C. Martin", "978-0132350884", "Technology"}
    };

    std::string searchTitle = "The Hobbit";
    auto itTitle = std::find_if(resources.begin(), resources.end(), 
        [&searchTitle](const LibraryResource& res) {
            return res.title == searchTitle;
        });

    std::string searchAuthor = "Robert C. Martin";
    auto itAuthor = std::find_if(resources.begin(), resources.end(), 
        [&searchAuthor](const LibraryResource& res) {
            return res.author == searchAuthor;
        });

    std::string searchISBN = "978-0321714114";
    auto itISBN = std::find_if(resources.begin(), resources.end(), 
        [&searchISBN](const LibraryResource& res) {
            return res.isbn == searchISBN;
        });

    auto itGenre = std::find_if(resources.begin(), resources.end(), GenrePredicate("Fantasy"));

    return 0;
}