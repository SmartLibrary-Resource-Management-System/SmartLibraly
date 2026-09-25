#ifndef RESERVATION_QUEUE_H
#define RESERVATION_QUEUE_H

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class ReservationQueue {
private:
    queue<string> danhSachCho;

public:
    void themVaoHangDoi(string maThanhVien) {
        danhSachCho.push(maThanhVien);
        cout << "Da dua thanh vien " << maThanhVien << " vao hang doi cho sach." << endl;
    }

    string layNguoiTiepTheo() {
        if (!danhSachCho.empty()) {
            string nguoiDung = danhSachCho.front();
            danhSachCho.pop();
            return nguoiDung;
        }
        return "";
    }

    bool kiemTraTrong() {
        return danhSachCho.empty();
    }
};

#endif