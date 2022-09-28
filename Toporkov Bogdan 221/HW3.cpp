#include <iostream>
using namespace std;
template <class T>
struct u_ptr{
    explicit u_ptr(T& a): ptr(new T){
        *ptr = a;
    }
    ~u_ptr(){
        if(!ptr) return;
        delete ptr;
        ptr = nullptr;
    }
    u_ptr<T>& operator = (u_ptr<T> & a){
        if(!a.ptr) throw 1;
        if(this == &a) return *this;
        delete ptr;
        ptr = a.ptr;
        a.ptr = nullptr;
        return *this;
    }
    T & operator * (){
        if(!ptr) throw 1;
        return *ptr;
    }
    T & operator -> (){
        if(!ptr) throw 1;
        return *ptr;
    }
    T get_val(){
        if(!ptr) throw 1;
        return *ptr;
    }
private:
    T * ptr;
    u_ptr(u_ptr<T>&){}

};


int main() {
    int b = 10, c = 5;
    u_ptr<int> a(b);
    u_ptr<int> a1(c);
    cout << a.operator*() << endl;
    cout << a1.operator*()<<endl;
    a = a1;
    cout << a.operator*() << endl;

}
