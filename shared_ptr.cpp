#include <iostream>

class Shared_Ptr{
    class ControlBlock{
    private:
        int count;
    public:
        ControlBlock(){
            count = 1;
        }
        int get_count(){
            return count;
        }
        void increment(){
            ++count;
        }
        int decrement(){
            return --count;
        }
    };
private:

    ControlBlock* counter =  nullptr;
    T* s_ptr = nullptr;

public:
    Shared_Ptr() = default;

    explicit SharedStr(T* obj) {
		counter = new CenterBlock();
		s_ptr = obj;
	}

    Shared_Ptr(const Shared_Ptr& obj){
        this->counter = obj.counter;
        this->counter->increment();
        this->s_ptr = obj.s_ptr;
    }
    Shared_Ptr& operator=(const Shared_Ptr& obj){
        if(this != &obj){
            if(s_ptr != nullptr){
                if(counter->decrement() == 0){
                    delete counter;
					delete s_ptr;
                }
            }
            counter = obj.counter;
            counter->increment();
            s_ptr = obj.s_ptr;
        }
        return *this;
    }
    Shared_Ptr(Shared_Ptr&& obj){
        this->counter = obj.counter;
		this->s_ptr = obj.s_ptr;
		obj.counter = nullptr;
		obj.s_ptr = nullptr;
    }
    Shared_Ptr& operator=(Shared_Ptr&& obj) noexcept{
		if (this != &obj) {
			if (s_ptr != nullptr) {
				if (counter->decrement() == 0) {
					delete counter;
					delete s_ptr;
                }
            }
            counter = obj.counter;
            s_ptr = obj.s_ptr;
            obj.counter = nullptr;
            obj.s_ptr =  nullptr;
        }
        return *this;
    }
    ~Shared_Ptr() {
		if (s_ptr != nullptr && counter->decrement() == 0) {
			delete counter;
			delete s_ptr;
			counter = nullptr;
			s_ptr = nullptr;
		}
	}

    public:
	int use_count() {
		if (counter == nullptr) { return 0; }
		return counter->get_count();
	}
	T* get() {
		return s_ptr;
	}
	T* operator ->() {
		return s_ptr;
	}
	T operator *() {
		return * s_ptr;
	}
    void reset(T* obj = nullptr) {
		if (s_ptr != nullptr && counter->get_count() == 1) {
			delete counter;
			delete s_ptr;
			counter = nullptr;
			s_ptr = nullptr;
		}
		else {
			s_ptr = obj;
			counter = new CenterBlock();
		}
	}

};

