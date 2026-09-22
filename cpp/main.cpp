#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;

bool ready = false;
int data = 0;

void producer() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        data = 42;
        ready = true;
    } // 先解锁

    cv.notify_one();  // 通知一个等待线程
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [] {
        return ready;
    });

    // 返回时已重新持有锁，且 ready 为 true
    int value = data;
    lock.unlock();

    std::cout << "收到数据：" << value << '\n';
}

int main() {
    std::thread c(consumer);
    std::thread p(producer);

    c.join();
    p.join();
    
}