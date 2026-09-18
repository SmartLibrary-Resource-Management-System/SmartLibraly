#ifndef ABSTRACT_LIBRARY_RESOURCE_H
#define ABSTRACT_LIBRARY_RESOURCE_H

#include <string>
#include <queue>
class AbstractLibraryResource {
protected:
    std::string resourceId;
    std::string title;
    std::string author;
    std::string category;
    std::string publisher;
    int publishYear;
    std::string resourceType;
    std::queue<std::string> reservationQueue; 

public:
    AbstractLibraryResource(std::string id, std::string t, std::string a, 
                            std::string cat, std::string pub, int pYear, std::string rType)
        : resourceId(id), title(t), author(a), category(cat), 
          publisher(pub), publishYear(pYear), resourceType(rType) {}

    virtual ~AbstractLibraryResource() = default;

    virtual void registerReservation(const std::string& memberId) {
        reservationQueue.push(memberId);
    }

    virtual std::string popReservation() {
        if (reservationQueue.empty()) return "";
        std::string nextMember = reservationQueue.front();
        reservationQueue.pop();
        return nextMember;
    }


    std::string getResourceId() const { return resourceId; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getCategory() const { return category; }
    std::string getPublisher() const { return publisher; }
    int getPublishYear() const { return publishYear; }
    std::string getResourceType() const { return resourceType; }
    

    size_t getReservationCount() const { return reservationQueue.size(); }

    virtual void displayDetails() const = 0; 
};

#endif
