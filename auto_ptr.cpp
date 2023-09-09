#include <iostream>

template <typename T>
class AutoPtr(){

private:
    T* ptr;

public:

    explicit AutoPtr(T* p = nullptr):ptr(p){}

    ~AutoPtr() {
        delete ptr;
    }

    AutoPtr(const AutoPtr& other) = delete;

    AutoPtr& operator=(const AutoPtr& obj){
        if(this != &obj){
            delete ptr;
            ptr = obj.ptr;
            obj.ptr = nullptr;
        }
        return this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const{
        return ptr;
    }

    T* release() {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* p = nullptr) {
        if (p != ptr) {
            delete ptr;
            ptr = p;
        }
    }
};
