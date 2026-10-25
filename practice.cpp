#include <iostream>
using namespace std;

class FloatBuffer {
    private :
        float* data;
        int size;
    
    public : 
        FloatBuffer(int n ){
            size = n ;
            data = new float[n];
            for(int i = 0; i< n; i++ ) {
                data[i] = 0.0f;
            }
        };

        ~FloatBuffer() {
            delete[] data;
            cout<<"Giải phóng bộ nhớ kích thước" << size <<endl;
        };

        void set(int i, float v) {
            if( i >= 0 && i < size ) {
                data[i] = v;
            } else {
                cout << "Index vượt ra size" << endl;
            }
        };

        float get(int i) const {
            if (i >= 0 && i < size) {
                return data[i];
            } else {
                cout << "vượt ra size rồi" << endl;
                return 0.0f;
            }
        };
};

int main() {
    FloatBuffer* buf = new FloatBuffer(8);
    buf->set(1, 3.9f);
    cout << "Gia tri tai vi tri 1: " << buf->get(1) << endl;
    delete buf;
    return 0;
}