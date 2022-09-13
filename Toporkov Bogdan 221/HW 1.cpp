#include <iostream>
#include <exception>
using namespace std;
struct String{
    String(const char * c){
        for(size = 0; c[size] != '\0'; ++size){}
        head = new char[++size];
        for(int i = 0 ; i < size + 1; i++){
            head[i] = c[i];
        }
    }
    String(): size(0), head(nullptr){}
    ~String(){
        delete[] head;
        head = nullptr;
        size = 0;
    }
    String(String & s){
        size = s.get_size();
        head = new char[size];
        for(int i = 0; i < size + 1; i++ ){
            head[i] = s[i];
        }
    }
    char & operator[](int i){
        if(i < 0 || i > size) {
            throw exception();
        }
        return head[i];
    }
    char operator[](int i) const{
        if(i < 0 || i > size) {
            throw exception();
        }
        return head[i];
    }
    void show() const{
        for (int i = 0; i < size; i++)
            cout << head[i]<<" ";
        cout << endl;
    }
    int get_size() const{ return size;}
    protected:
        char * head;
        int size;
};
int main() {
    String s1;
    String s2("123456");
    s2.show();
    s2[2] = '9';
    s2.show();
    s1.show();
    String s3(s2);
    s3.show();

}
