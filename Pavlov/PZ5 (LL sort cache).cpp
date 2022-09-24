#include <iostream>
#include <string>
using namespace std;


template <class Type>
struct LinkedList{

    LinkedList(): size(0), head(nullptr), tail(nullptr), instance(0){ }
    int get_inst(){return instance++;}
    size_t get_size(){return size;}
    void print_all(){
        cout << "ALL elements: ";
        Node<Type> * boof = head;
        while(boof != nullptr){
            cout<<boof->name << ": " << boof->data << "->cache: "<<boof->cache<<"; ";
            boof  = boof->next;
        }
        //cout<<boof->name << ": " << boof->data << "; "<<endl;
        cout<<endl;
    }
    void revers_print(){
        cout <<"Reverce print"<<endl;
        cout << "ALL elements: ";
        Node<Type> * boof = tail;
        while(boof->prev != nullptr){
            cout<<boof->name << ": " << boof->data << "; ";
            boof  = boof->prev;
        }
        cout<<boof->name << ": " << boof->data << "; "<<endl;
    }

    ~LinkedList(){
        Node<Type> * boof = tail->prev;
        while(boof){
            delete tail;
            tail = boof;
            boof = boof->prev;
        }
    }
    void pop_front(){
        if(head == nullptr) return;
        if(size == 1)
            tail = nullptr;
        Node<Type> * boof = head->next;
        delete head;
        head = boof;
        head->prev = nullptr;
        --size;
    }
    void clear(){
        Node<Type> * boof = tail->prev;
        while(boof){
            delete tail;
            tail = boof;
            boof = boof->prev;
        }
    }
    void removeAt(size_t index){
        if((index >= 0) && (index < size )) {
            if (index == 0) {
                this->pop_front();

            } else if(index == size - 1)
                this->pop_back();
            else {

                if(index < (size - index)){
                    Node <Type> *boof = head;
                    for (size_t i = 0; i < index - 1; ++i) {
                        boof = boof->next;
                    }
                    Node <Type> *boof2 = boof->next->next;
                    delete boof->next;
                    boof->next = boof2;
                    boof2->prev = boof;
                }
                else{
                    Node <Type> *boof = tail;
                    for (size_t i = 0; i < size - index -1; ++i) {
                        boof = boof->prev;
                    }
                    Node <Type> *boof2 = boof->prev->prev;
                    delete boof->prev;
                    boof->prev = boof2;
                    boof2->next = boof;
                }
                /////////////
                --size;
            }

        }
        else{
            cout << "wrong index"<<endl;
        }
    }
    void pop_back(){
        if(head == nullptr) return;
        if(size == 1)
            pop_front();
        Node<Type> * boof = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete boof;
        size--;
    }

    void push_back(Type data, string name_ = "default"){
        if(name_ == "default")
            name_+= to_string(get_inst());
        if(head == nullptr){
            head = new Node<Type>(data, name_);
            tail = head;
        }
        else{
            tail->next = new Node<Type>;
            tail->next->prev = tail;
            tail = tail->next;
            tail->data = data;
            tail->name = name_;
        }
        ++size;
    }
    void push_front(Type data, string name_ = "default"){
        /*Node<Type> * boof = new Node<Type>;
        boof->data = data;
        boof->next = head;
        head = boof;
        ++size;
        */
        if(name_ == "default")
            name_+= to_string(get_inst());
        head = new Node<Type>(data, head, nullptr, name_);
        if(size == 1)
            tail = head->next;
        if(size == 0)
            tail = head;
        if(head->next != nullptr) {
            head->next->prev = head;
        }
        ++size;
    }
    void insert(Type val, size_t index, string name_ = "default"){
        if(name_ == "default")
            name_+= to_string(get_inst());
        if((index >= 0) && (index <= size )) {
            if (index == 0) {
                this->push_front(val, name_);

            } else if(index == size)
                this->push_back(val, name_);
            else {

                if(index < (size - index)){
                    Node <Type> *boof = head;
                    for (size_t i = 0; i < index - 1; ++i) {
                        boof = boof->next;
                    }
                    Node <Type> *boof2 = new Node<Type>;
                    boof2->data = val;
                    boof2->name = name_;
                    boof2->next = boof->next;
                    boof2->prev = boof;
                    boof->next->prev = boof2;
                    boof->next = boof2;
                }
                else{
                    Node <Type> *boof = tail;
                    for (size_t i = 0; i < size - index -1; ++i) {
                        boof = boof->prev;
                    }
                    Node<Type> * boof2 = new Node<Type>;
                    boof2->prev = boof->prev;
                    boof->prev->next = boof2;
                    boof->prev = boof2;
                    boof2->data = val;
                    boof2->name = name_;
                    boof2->next = boof;
                }
                /////////////
                ++size;
            }

        }
        else{
            cout << "wrong index"<<endl;
        }
    }

    Type& operator[](const size_t index){
        if(index >= 0 && index < size) {
            Node <Type> *boof;
            if (index < (size - index)) {
                boof = head;
                for (size_t i = 0; i < index; ++i) {
                    boof = boof->next;
                }
            } else {
                boof = tail;
                for (size_t i = 0; i < size - index - 1 ; ++i) {
                    boof = boof->prev;
                }
            }
            return boof->data;
        }
        cout << "wrong index"<<endl;
    }
    /*Type& operator[](const int index){
        size_t counter = 0;
        Node<Type> * boof = head;
        while(boof != 0){
            if(counter == index){
                return boof->data;
            }
            boof = boof->next;
            ++counter;
        }
    }*/
    //block three
    //void swap(Node <Type> * a, Node<Type> * b ){} мне лень переносить объявление нода, так что эта функ будет в прайвате
    void test2(){swap(head->next ,head->next->next->next );} // для тестов swap

    Type * search_by_name(string name_){ // skel
        Node<Type> * boof = head;
        while(boof != nullptr){
            if(boof->name == name_){
                break;
            }
            boof = boof->next;
        }
        if(!boof)
            return nullptr;
        boof->cache += 1;
        // сортировка
        Node<Type> * boof2 = boof;
        while(boof2->prev != nullptr && boof2->prev->cache < boof->cache){
            boof2 = boof2->prev;
        }
        swap(boof, boof2);

    }
private:
    template <class T>
    struct Node{
        Node(T data = T(), Node *pNext = nullptr, Node *pPrev = nullptr,string name = "", int cache_ = 0)
            : data(data), next(pNext), prev(pPrev),name(name), cache(cache_){}
        Node(T data, string name):data(data), next(nullptr), prev(nullptr),name(name), cache(0){}
        Node * next;
        Node * prev;
        T data;
        string name;
        int cache;
    };
    Node<Type> * tail;
    Node<Type> * head;
    int instance;
    size_t  size;
    //block 3
    // swap has done
    void swap(Node <Type> * a, Node<Type> * b ){
        if(a == b || a == nullptr || b == nullptr) return;
        //cout <<"a-p: " << a->prev << "; a:" << a << "; a-n"<< a->next <<endl;
        //cout <<"b-p: " << b->prev << "; b:" << b << "; b-n"<< b->next <<endl;
        //neighbors elements - OK - MB_Ok
        if(a->next == b){
            if(a->prev != nullptr){
                b->prev = a->prev;
                a->prev->next = b;
            }
            else{
                b->prev = nullptr;
                head = b;
            }
            if(b->next != nullptr){
                a->next = b->next;
                b->next->prev = a;
            }
            else{
                a->next = nullptr;
                tail = b;
            }
            b->next = a;
            a->prev = b;
            return;

        }
        else if(b->next == a){
            swap(b,a);
            return;
        }
        //not nei:
        // HEAD-Tail - OK - OK
        if(a->prev == nullptr && b->next == nullptr) { //head-tail setuation
            b->next = a->next;
            a->next = nullptr;

            b->next->prev = b;
            b->prev->next = a;

            a->prev = b->prev;
            b->prev = nullptr;

            head = b;
            tail = a;
            return;
        }
        else if(b->prev == nullptr && a->next == nullptr){ // tail - head setuation
            swap(b, a);
            return;
        }
        //Tail - X - OK - OK
        if(a->prev != nullptr && b->next == nullptr){
            b->next = a->next;
            a->next = b->prev; //tmp boof

            b->next->prev = b;
            b->prev = a->prev;
            a->prev = a->next; // boof
            b->prev->next = b;
            a->prev->next = a;
            a->next = nullptr;
            tail = a;
            return;
        }
        else if(b->prev != nullptr && a->next == nullptr){
            swap(b, a);
            return;
        }
        //Head - X - OK - OK
        if(a->prev == nullptr && b->next != nullptr){
            a->prev = b->prev;
            a->prev->next = a;
            b->prev = a->next; // место буфера

            a->next = b->next;
            b->next = b->prev;
            b->next->prev = b;
            a->next->prev = a;
            b->prev = nullptr;
            head = b;
            return;
        }
        else if(b->prev == nullptr && a->next != nullptr){
            swap(b, a);
            return;
        }
        //X - X - OK
        //if() ифа не будет - тк вариантов больше не осталось(скорее всего)
        // обмен значений с предыдущими элиментами
        Node<Type> * boof = a->prev;
        a->prev->next = b;
        b->prev->next = a;
        boof = a->prev;  //////////////// ткуда boof
        a->prev = b->prev;
        b->prev = boof;
        //обмен со след элл
        a->next->prev = b;
        b->next->prev = a;
        boof = a->next;
        a->next = b->next;
        b->next = boof;



    }

};

int main() {
    LinkedList<int> a;
    cout << "t0\n";
    a.push_front(11, "1st");
    a.push_back(12, "2nd");
    a.push_back(13, "3rd");
    a.push_back(14, "4th");
    a.push_back(15,"5th");
    a.print_all();
    //a.revers_print();
    a.search_by_name("2nd");
    a.search_by_name("3rd");
    a.search_by_name("4th");
    a.print_all();
    a.search_by_name("2nd");
    a.search_by_name("3rd");
    a.print_all();
    a.search_by_name("2nd");


    a.print_all();
    a.revers_print();

}
