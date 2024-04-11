#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <queue>

using namespace std;
class BoundedBlockingQueue {
private:
	int cap;
	mutex mtx;
	condition_variable cv;
	std::deque<int> q;
public:
    BoundedBlockingQueue(int capacity) {
        this->cap = capacity;
    }
    
    void enqueue(int element) {
        std::unique_lock<std::mutex> lock(mtx);
				cv.wait(lock, [this]() {
					return q.size() < cap;
				});
				q.push_front(element);
				lock.unlock();
				cv.notify_one();
    }
    
    int dequeue() {
        std::unique_lock<std::mutex> lock(mtx);
				cv.wait(lock, [this]() {
					return q.size() > 0;
				});
				int res = q.back();
				q.pop_back();
				lock.unlock();
				cv.notify_one();
				return res;
    }
    
    int size() {
        std::lock_guard<std::mutex> lock(mtx);
	//std::unique_lock<std::mutex> lock(mtx);
	int size = q.size();
	//lock.unlock();
	cv.notify_one();
	return size;
    }

};

void producer(BoundedBlockingQueue& queue) {
    for (int i = 0; i < 10; ++i) {
        queue.enqueue(i);
        std::cout << "生产者：已生产元素 " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer(BoundedBlockingQueue& queue) {
    for (int i = 0; i < 10; ++i) {
        int value = queue.dequeue();
        std::cout << "消费者：已消费元素 " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

//////
template <typename T>
class UnboundedBlockingQueue {
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<T> q;

public:
    void enqueue(T v) {
        std::unique_lock<std::mutex> lock(mtx);
        q.push(v);
        lock.unlock();
        cv.notify_all();
    }

    T dequeue() {
        T res = 0;
        std::unique_lock<std::mutex> lock(mtx);
	std::cout << " waiting ..." << endl;
        cv.wait(lock, [this]() { return !q.empty(); });
	std::cout << " wait done." << endl;
	res = q.front();
        q.pop();
        lock.unlock();
        return res;
    }
};

// template <typename T>
void producerU(UnboundedBlockingQueue<int>& queue) {
    for (int i = 0; i < 10; ++i) {
        queue.enqueue(i);
        std::cout << "生产者：已生产元素 " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// template <typename T>
void consumerU(UnboundedBlockingQueue<int>& queue) {
    while (true) {
        int value = queue.dequeue();
        std::cout << "消费者：已消费元素 " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    //BoundedBlockingQueue queue(5); // 创建容量为 5 的有界阻塞队列
    //std::thread producerThread(producer, std::ref(queue)); // 创建生产者线程
    //std::thread consumerThread(consumer, std::ref(queue)); // 创建消费者线程

    UnboundedBlockingQueue<int> queue;
    std::thread producerThread(producerU, std::ref(queue)); // 创建生产者线程
    std::thread consumerThread(consumerU, std::ref(queue)); // 创建消费者线程

    producerThread.join(); // 等待生产者线程结束
    consumerThread.join(); // 等待消费者线程结束

    return 0;
}