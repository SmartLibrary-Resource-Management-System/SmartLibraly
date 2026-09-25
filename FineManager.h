#ifndef FINE_MANAGER_H
#define FINE_MANAGER_H

class FineManager {
public:
    static double tinhTienPhat(int soNgayQuaHan, double mucPhatMotNgay = 5000.0) {
        if (soNgayQuaHan <= 0) {
            return 0.0; 
        }
        return soNgayQuaHan * mucPhatMotNgay;
    }
};

#endif
