#include <iostream>
#include <string>
using namespace std; 

class Person {
    protected :
        string name;
        int age;

    public : 
        Person(string n, int a) {
            name = n;
            age = a;
        };

        void show() {
            cout << "Họ và tên: " << name <<endl;
            cout << "Tuổi: " << age << endl;
        };
};

class Student : public Person {
    private : 
        int StudentID;

    public: 
        Student(int id, string n, int a) : Person(n,a) {
            StudentID = id;
        };

        void showInfor() {
            cout << "Mã Sinh Viên : " << StudentID << endl;
        }
};

int main() {
    Student s(11257829, "Nguyễn Vũ Đức Thịnh", 19);
    cout << "Một vài thông tin cá nhân:" << endl;
    s.show();
    s.showInfor();
    return 0;
}