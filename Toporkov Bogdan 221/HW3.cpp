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
            u_ptr<T>& operator = (u_ptr<T>a){
                if(!a.ptr) throw 1;
                if(this == &a) return this;
                ptr = a.ptr;
                a.ptr = nullptr;
                return this;
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
