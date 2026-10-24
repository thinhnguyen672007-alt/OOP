#include <iostream>
#include <vector> 
using namespace std;

struct Point {
    float x;
    float y;
};

int main() {
    // Ôn tập struct
    Point p1;
    p1.x = 3.0f;
    p1.y=4.0f;
    Point* ptr = &p1;
    cout<<"Giá trị x là: " << (*ptr).x << endl;
    cout<<"Giá trị y là: " << ptr->y << endl;
    
    // ôn tập mảng tĩnh và mảng động 
    int arr[5] = {0};
    int value = 0;
    for(int i = 0; i< 5; i++) {
        arr[i] = value+=1;
        cout<<arr[i]<<endl;
    }

    cout<<"Các giá trị của mảng động"<<endl;
    int* p = (int*)malloc(5 * sizeof(int));
    int value2 = 0;
    for(int i = 0; i<5; i++) {
        p[i] = value2+=1;
        cout<<p[i]<<endl;
    }

    free(p);

    // Ôn tập vector

    cout<<"Các giá trị khi dùng vecctor"<<endl;
    vector<int> v(5);
    int n = v.size();
    for(int i = 0; i< n; i++) {
        v[i] = i+1;
        cout<<v[i]<<" ";
    }

    cout<<n;
    return 0;
}