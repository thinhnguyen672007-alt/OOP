#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
    private : 
        string name;
        int id;

    public :
        Student(string name, int id) {
            this->name = name;
            this->id = id;
        }

        string getName(){
            return this->name;
        }

        int getID() {
            return this->id;
        }

};

int main() {
    Student* s1= new Student("Thịnh", 11257829);
    cout<<"Tên học sinh lầ:" << s1->getName() << endl;
    cout<<"ID học sinh là:" << s1->getID() << endl;
    delete s1;
    return 0;
}