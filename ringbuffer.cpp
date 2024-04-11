
#include <atomic>
#include <array>
#include <thread>

template<typename T, size_t Capacity>
class RingBuffer {
public:
    RingBuffer() : readIndex(0), writeIndex(0) {}

    bool isEmpty() const {
        return readIndex.load() == writeIndex.load();
    }

    bool isFull() const {
        return (writeIndex.load() + 1) % Capacity == readIndex.load();
    }

    void enqueue(const T& data) {
        while (isFull()) {
            // 缓冲区已满，等待
        }
        buffer[writeIndex.load()] = data;
        writeIndex = (writeIndex.load() + 1) % Capacity;
    }

    T dequeue() {
        while (isEmpty()) {
            // 缓冲区已空，等待
        }
        T data = buffer[readIndex.load()];
        readIndex = (readIndex.load() + 1) % Capacity;
        return data;
    }

private:
    std::array<T, Capacity> buffer;
    std::atomic<size_t> readIndex;
    std::atomic<size_t> writeIndex;
};

// 使用示例
RingBuffer<int, 5> buffer;

void producer() {
    for (int i = 0; i < 10; ++i) {
        buffer.enqueue(i);
    }
}

void consumer() {
    for (int i = 0; i < 10; ++i) {
        int data = buffer.dequeue();
        // 处理数据
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);
    producerThread.join();
    consumerThread.join();
    return 0;
}