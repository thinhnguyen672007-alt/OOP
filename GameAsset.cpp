#include <iostream>
#include <string>
using namespace std;

class GameAsset {
    private:
        string id;
        int sizeMB;

    public:
        void Print() {
            cout<<"Asset ID: "<<id<<endl;
            cout<<"Size:"<<sizeMB<<"MB"<<endl;
        }

        int GetSizeMB() {
            return sizeMB;
        }
        
    GameAsset(string n, int s) : id(n), sizeMB(s) {
        cout<<"Tạo id và size"<<"\n";
    }
};

int main() {
    string id = "tree";
    int sizeMB = 10;
    GameAsset myAsset1(id, sizeMB);
    
    myAsset1.Print();

    GameAsset* myAsset2 = new GameAsset("rock", 20);
    myAsset2->Print();
    delete myAsset2;

    return 0;
}