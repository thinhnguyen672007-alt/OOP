#include <iostream>
#include <string>
using namespace std;

class payment {
    protected : 
        double amount; 
    
    public :
        payment(double a) {
            amount = a;
        }

        virtual ~payment() {};

        virtual void pay() {
            cout << "Đang thanh toán với số tiền: " << amount << "VND"<< endl;
        }
};

class cashPayment : public payment {
    public :
        cashPayment(double a) : payment(a) {}
        
        void pay() override {
            cout << "Thanh toán tiền mặt: " << amount << "VND" << endl;
        }
};

class momoPayment : public payment {
    public :
        momoPayment(double a) : payment(a) {}

        void pay() override {
            cout << "Thanh toán tiền Momo: " << amount << "VND" << endl;
        }
};

class cardPayment : public payment {
    private :
        string cardNumber;

    public :
        cardPayment(double a, string cardNum) : payment(a) {
            cardNumber = cardNum;
        };

        void pay() override {
            cout << "Thanh toán bằng thẻ với số thẻ : " << cardNumber <<", với số tiền :" << amount << "VND" << endl;
        }
};

int main() {
    payment* p[3];
    p[0] = new cashPayment(50000);
    p[1] = new momoPayment(100000);
    p[2] = new cardPayment(200000, "thinh12345");

    for(int i = 0; i<3; i++) {
        p[i]->pay();
    }

    for(int i = 0; i < 3; i++) {
        delete p[i];
    }

    return 0;
}