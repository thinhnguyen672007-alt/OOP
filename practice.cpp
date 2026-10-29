#include <iostream> 
#include <string>
using namespace std;

class phuongTien {
    protected :
        string bienSo;
        string hangXe;

    public : 
        phuongTien(string bs, string hx) {
            bienSo = bs;
            hangXe = hx;
        }

        virtual ~phuongTien() {};

        virtual void diChuyen() = 0;

        virtual void hienThi() = 0;
};

class Oto : public phuongTien {
    private :
        int soChoNgoi;

    public :
        Oto(string bs, string hx, int numberChairs) : phuongTien(bs,hx) {
            soChoNgoi = numberChairs;
        }

        void diChuyen() override {
            cout << "Di chuyển với tốc độ tối đa 120km/h" << endl;
        }

        void hienThi() override {
            cout << "Xe sang trọng quý phái" << endl;
        }
};

class xeMay : public phuongTien {
    private :
        int dungTichXiLang;

    public :
        xeMay(string bs, string hx, int dungTich) : phuongTien(bs,hx) {
            dungTichXiLang = dungTich;
        }

        void diChuyen() override {
            cout << "Di chuyển với tốc độ tối đa 80km/h" << endl;
        }

        void hienThi() override {
            cout << "Xe tiện lợi, luồn lách lúc tắc đường" << endl;
        }
};

int main() {
    phuongTien* ds[2];
    ds[0] = new Oto("30-F8", "BMW", 2);
    ds[1] = new xeMay("29-N3", "Honda", 10);

    for(int i = 0; i < 2; i++) {
        ds[i]->diChuyen();
        ds[i]->hienThi();
    }

    for(int i = 0; i < 2; i++) delete ds[i];

    return 0;
}