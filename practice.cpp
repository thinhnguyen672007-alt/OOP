#include <iostream> 
#include <string>
using namespace std;

class transport {
    protected :
        int lisencePlate;
        string autoMaker;
        int yearProduction;

    public :
        transport(int l, string a, int y) {
            lisencePlate = l;
            autoMaker = a;
            yearProduction = y;
            if(y > 2026) {
                cout <<" Bạn đi trước tương lai à!"<<endl;
            } else if (y < 2000) {
                cout <<"Xe đã quá cũ! Cần đổi ngay!"<<endl;
            }
        }

        virtual ~transport() {};

        virtual void speed() {
            cout <<"Các phương tiện có vận tốc trung bình là 50km/h"<<endl;
        }

        virtual void refuel() {
            cout <<"Cần nạp nhiên liệu"<<endl;
        }
};

class carElectric : public transport {
    public :
        carElectric(int l, string a, int y) : transport(l, a, y) {}

        void speed() override {
            cout <<"Vận tốc của ô tô có thể lên tới 100km/h" << endl;
        }

        void refuel() override {
            cout <<"Xe cần nạp điện để tiếp tục đi" << endl;
        }

};

class motorbike : public transport {
    public :
        motorbike(int l, string a, int y) : transport(l, a, y) {}

        void speed() override {
            cout <<"Vận tốc của xe máy có thể lên tới 70km/h" << endl;
        }

        void refuel() override {
            cout <<"Xe cần đổ xăng để tiếp tục đi" << endl;
        }
};

class truck : public transport {
    public :
        truck(int l, string a, int y) : transport(l, a, y) {}

        void speed() override {
            cout <<"Vận tốc của xe tải có thể lên tới 120km/h" << endl;
        }

        void refuel() override {
            cout <<"Xe cần đổ xăng để tiếp tục đi" << endl;
        }
};

int main() {
    transport* t[3];
    t[0] = new carElectric( 123, "Vin", 2023);
    t[1] = new motorbike( 278, "Honda", 1999);
    t[2] = new truck( 183, "Suzuki", 2027);

    for (int i = 0; i< 3; i++) {
        t[i]->speed();
        t[i]->refuel();
    }

    for (int i = 0; i<3; i++){
        delete t[i];
    }
    return 0;

}
