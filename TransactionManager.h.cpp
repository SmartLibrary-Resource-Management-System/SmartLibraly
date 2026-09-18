#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

// Include các file header do thành viên khác trong nhóm phụ trách
#include "AbstractLibraryResource.h"
#include "AbstractMember.h"
#include "FineManager.h"
#include "ReservationQueue.h"


struct LoanTransaction {
    std::string transactionId;
    std::string memberId;
    std::string resourceId;
    std::chrono::system_clock::time_point borrowDate;
    std::chrono::system_clock::time_point dueDate;
    std::chrono::system_clock::time_point returnDate;
    bool isReturned;
    double fineAmount;

    LoanTransaction(std::string transId, std::string mId, std::string rId, int loanDays)
        : transactionId(transId), memberId(mId), resourceId(rId), isReturned(false), fineAmount(0.0) {
        borrowDate = std::chrono::system_clock::now();
        dueDate = borrowDate + std::chrono::hours(24 * loanDays);
    }
};


class TransactionManager {
private:
    std::vector<LoanTransaction> transactions;
    int transactionCounter;

public:
    TransactionManager() : transactionCounter(1) {}

    
    bool borrowResource(AbstractMember* member, AbstractLibraryResource* resource, ReservationQueue& reservationQueue) {
        if (!member || !resource) {
            std::cout << "[Lỗi Giao Dịch] Thông tin Thành viên hoặc Tài nguyên không hợp lệ.\n";
            return false;
        }

        if (member->getBorrowedBooksCount() >= member->getMaxLoanLimit()) {
            std::cout << "[Mượn Thất Bại] Thành viên " << member->getFullName() 
                      << " đã đạt giới hạn mượn tối đa (" << member->getMaxLoanLimit() << " tài nguyên).\n";
            return false;
        }

        if (!resource->isAvailable()) {
            std::cout << "[Mượn Thất Bại] Tài nguyên \"" << resource->getTitle() 
                      << "\" hiện đã hết bản khả dụng.\n";
            std::cout << "--> Tự động thêm thành viên " << member->getMemberId() << " vào Hàng đợi đặt trước (Reservation Queue)...\n";
            reservationQueue.themVaoHangDoi(member->getMemberId());
            return false;
        }

        if (resource->borrowItem()) {
            member->incrementBorrowedCount();

            int loanDays = (member->getRole() == Role::MEMBER) ? 14 : 30;
            std::string transId = "TXN" + std::to_string(transactionCounter++);

            LoanTransaction newTxn(transId, member->getMemberId(), resource->getId(), loanDays);
            transactions.push_back(newTxn);

            std::cout << "==================================================\n";
            std::cout << "[GIAO DỊCH MƯỢN THÀNH CÔNG] Mã GD: " << transId << "\n";
            std::cout << " - Thành viên: " << member->getFullName() << " (ID: " << member->getMemberId() << ")\n";
            std::cout << " - Tài nguyên: " << resource->getTitle() << " (ID: " << resource->getId() << ")\n";
            std::cout << " - Số lượng đã mượn: " << member->getBorrowedBooksCount() << "/" << member->getMaxLoanLimit() << "\n";
            std::cout << "==================================================\n";
            return true;
        }

        return false;
    }

   
    bool returnResource(AbstractMember* member, AbstractLibraryResource* resource, int overdueDays, ReservationQueue& reservationQueue) {
        if (!member || !resource) {
            std::cout << "[Lỗi Giao Dịch] Thông tin không hợp lệ.\n";
            return false;
        }

        LoanTransaction* activeTxn = nullptr;
        for (auto& txn : transactions) {
            if (txn.memberId == member->getMemberId() && txn.resourceId == resource->getId() && !txn.isReturned) {
                activeTxn = &txn;
                break;
            }
        }

        if (!activeTxn) {
            std::cout << "[Lỗi Trả Sách] Không tìm thấy lịch sử mượn tài nguyên này của thành viên " << member->getFullName() << ".\n";
            return false;
        }

        resource->returnItem();
        member->decrementBorrowedCount();
        activeTxn->isReturned = true;
        activeTxn->returnDate = std::chrono::system_clock::now();

        double fine = 0.0;
        if (overdueDays > 0) {
            fine = member->calculateFine(overdueDays);
            activeTxn->fineAmount = fine;
        }

        std::cout << "==================================================\n";
        std::cout << "[TRẢ SÁCH THÀNH CÔNG] Mã GD: " << activeTxn->transactionId << "\n";
        std::cout << " - Thành viên: " << member->getFullName() << "\n";
        std::cout << " - Tài nguyên: " << resource->getTitle() << "\n";
        if (fine > 0) {
            std::cout << " - PẠT TRỄ HẠN: Trễ " << overdueDays << " ngày. Tiền phạt: " << fine << " VNĐ.\n";
        } else {
            std::cout << " - Tình trạng: Trả đúng hạn.\n";
        }
        std::cout << "==================================================\n";

        if (!reservationQueue.kiemTraTrong()) {
            std::string nextMemberId = reservationQueue.layNguoiTiepTheo();
            std::cout << "--> Thông báo: Tài nguyên vừa trả đã được chuyển quyền ưu tiên cho thành viên trong hàng đợi (ID: " 
                      << nextMemberId << ").\n";
        }

        return true;
    }

    
    void displayAllTransactions() const {
        std::cout << "\n==================================================\n";
        std::cout << "        LỊCH SỬ GIAO DỊCH MƯỢN / TRẢ SÁCH         \n";
        std::cout << "==================================================\n";
        if (transactions.empty()) {
            std::cout << "Chưa có giao dịch nào được ghi nhận.\n";
            return;
        }
        for (const auto& txn : transactions) {
            std::cout << "Mã GD: " << txn.transactionId 
                      << " | Member ID: " << txn.memberId 
                      << " | Resource ID: " << txn.resourceId 
                      << " | Trạng thái: " << (txn.isReturned ? "Đã trả" : "Đang mượn") 
                      << " | Tiền phạt: " << txn.fineAmount << " VNĐ\n";
        }
        std::cout << "--------------------------------------------------\n";
    }
};

#endif // TRANSACTION_MANAGER_H