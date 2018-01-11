#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <vector>

int count=0;
std::mutex mtx;
std::mutex mtx_count;
int data_pass,data_rec;


class Threadtask{
private:
    int _i=0;
    int _num_thread;
    bool _passing_exc=false;
    bool _rec_exc=false;
    
public:
    Threadtask();
    void passing();
    void receiving();
    void passing_message(int x);
    void receiving_message(int x);
    
};

void Threadtask::passing_message(int x){
    data_pass=x;
    //std::cout<<"passing value  "<<x<<std::endl;
}

void Threadtask::receiving_message(int x){
    data_rec=x;
    //std::cout<<"receiving value"<<x<<std::endl;
}
void Threadtask::passing(){
    while(1){
        if(!_passing_exc){
            mtx.lock();
            this->passing_message(count);
            mtx.unlock();
            _passing_exc=true;
            //usleep(1000000);
        }
        if(_passing_exc&&_rec_exc)
            {
                _passing_exc=false;
                _rec_exc=false;
            }
    }
}

void Threadtask::receiving(){
    while(1){
        if(!_rec_exc){
            mtx.lock();
            this->receiving_message(count);
            mtx.unlock();
            _rec_exc=true;
            //usleep(1000);
        }

    }

}

Threadtask::Threadtask(){
    }


int main(){
    Threadtask obj1;
    std::vector<std::thread> threads;
    threads.push_back(std::thread(&Threadtask::passing,&obj1));
    threads.push_back(std::thread(&Threadtask::receiving,&obj1));
    while(1){
        mtx.lock();
        count=rand() %100 +1;
        std::cout<<"passing :"<<data_pass<<"receive :"<<data_rec<<std::endl;
        mtx.unlock();
        usleep(1000000);
        
    }
    for(auto& thread : threads){
        thread.join();
    return 0;
}
}
