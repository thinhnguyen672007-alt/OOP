#include <iostream>
#include <string>
using namespace std;

class Order {
    protected:
        string OrderID;
        string CustomerName;
        double costPerOrder;

    public:
        static double totalCost;
        static int numOrder;
        Order() {
            OrderID = "";
            CustomerName = "";
            costPerOrder = 0;
            numOrder++;
        }

        Order(string o, string name, double cost = 0) {
            OrderID = o;
            CustomerName = name;
            costPerOrder = cost;
            totalCost += cost;
            numOrder++;
        }

        virtual ~Order() {}

        virtual void get() {
            cout << "Nhập ID của đơn hàng: ";
            cin >> OrderID;
            cout << "Nhập tên khách hàng của đơn hàng: ";
            cin.ignore();
            getline(cin, CustomerName);
        }

        virtual void display() {
            cout << "ID của đơn hàng là : " <<OrderID << endl;
            cout << "Tên của khách hàng là : " << CustomerName << endl;
            cout << "Chi phí đơn hàng: " << costPerOrder << endl;
        }

        double getCostPerOrder() const { return costPerOrder; }
        string getOrderID() const { return OrderID; }
        string getCustomerName() const { return CustomerName; }

        // Question 3: 
        bool operator<(const Order& other) const {
            if(this->costPerOrder < other.costPerOrder) {
                return true;
            } else {
                return false;
            }
        }

        
        static double getAvrCost() {
            if (numOrder == 0) {
                return 0.0;
            }
            return totalCost / numOrder;
        }
};


double Order::totalCost = 0.0;
int Order::numOrder = 0;

// Question 4
class domesticOrder : public Order {
    protected:
        double productValue;
        double shippingFee;

    public:
        domesticOrder() : Order() {
            productValue = 0;
            shippingFee = 0;
        }

        domesticOrder(double pV, double sP, string o, string name) : Order(o, name) {
            productValue = pV;
            shippingFee = sP;
            costPerOrder = productValue + shippingFee;
            totalCost += costPerOrder; 
        }

        ~domesticOrder() {}

        void get() override {
            Order::get();
            cout << "Nhập giá trị sản phẩm: ";
            cin >> productValue;
            cout << "Nhập phí vận chuyển: ";
            cin >> shippingFee;
            costPerOrder = productValue + shippingFee;
            totalCost += costPerOrder;
        }

        void display() override {
            Order::display();
            cout << "Giá trị sản phẩm: " << productValue << endl;
            cout << "Phí vận chuyển: " << shippingFee << endl;
        }
};

class internationalOrder : public Order {
    protected:
        double productValue;
        float tax;
        double internationalShippingFee;

    public:
        internationalOrder() : Order() {
            productValue = 0;
            tax = 0;
            internationalShippingFee = 0;
        }

        internationalOrder(double p, float t, double fee, string o, string name) : Order(o, name) {
            productValue = p;
            tax = t;
            internationalShippingFee = fee;
            costPerOrder = productValue + tax + internationalShippingFee;
            totalCost += costPerOrder;
        }

        ~internationalOrder() {}

        void get() override {
            Order::get();
            cout << "Nhập giá trị sản phẩm: ";
            cin >> productValue;
            cout << "Nhập thuế: ";
            cin >> tax;
            cout << "Nhập phí vận chuyển quốc tế: ";
            cin >> internationalShippingFee;
            costPerOrder = productValue + tax + internationalShippingFee;
            totalCost += costPerOrder;
        }

        void display() override {
            Order::display();
            cout << "Giá trị sản phẩm: " << productValue << endl;
            cout << "Thuế: " << tax << endl;
            cout << "Phí vận chuyển quốc tế: " << internationalShippingFee << endl;
        }
};

int main() {
    int n;
    cout << "Nhập số lượng đơn hàng: ";
    cin >> n;


    Order** orders = new Order*[n];

    for (int i = 0; i < n; i++) {
        int type;
        cout << "\n--- Đơn hàng thứ " << i + 1 << " ---" << endl;
        cout << "Chọn loại đơn hàng (1: Nội địa, 2: Quốc tế): ";
        cin >> type;

        if (type == 1) {
            orders[i] = new domesticOrder();
        } else {
            orders[i] = new internationalOrder();
        }
        orders[i]->get();
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (*orders[j] < *orders[j + 1]) {
                Order* temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }

    cout << "\nNo    OrderID     Customer Name    Cost\n";
    for (int i = 0; i < n; i++) {
        cout << (i + 1) << "\t"
             << orders[i]->getOrderID() << "\t\t"
             << orders[i]->getCustomerName() << "\t\t"
             << orders[i]->getCostPerOrder() << endl;
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; i++) {
        delete orders[i];
    }
    delete[] orders;

    return 0;
}
