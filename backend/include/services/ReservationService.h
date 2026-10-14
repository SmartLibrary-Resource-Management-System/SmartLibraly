#pragma once
#include <string>
#include <vector>

#include "models/Library.h"

class ReservationService {
public:
    explicit ReservationService(Library& library) : library_(library) {}

    Reservation reserve(int memberId, int resourceId, const std::string& date = "");
    Reservation cancel(int reservationId);
    void complete(int reservationId);

    std::vector<Reservation> fulfillQueue(int resourceId);

    std::vector<Reservation> getQueue(int resourceId) const;
    std::vector<Reservation> getAll() const;
    std::vector<Reservation> getForMember(int memberId) const;
    const Reservation* findReady(int memberId, int resourceId) const;
    int readyCount(int resourceId) const;
    int waitingCount() const;
    int effectiveAvailableCopies(const LibraryResource& resource) const;
    bool hasOpenReservation(int memberId, int resourceId) const;

private:
    Library& library_;
};
