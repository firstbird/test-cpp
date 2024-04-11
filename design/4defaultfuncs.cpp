
#include <memory>
class MyBuffer {
public:
    // 构造函数，创建一个指定大小的缓冲区
    explicit MyBuffer(size_t size) : size_(size), data_(new char[size]) {}

    // 拷贝构造函数，执行深拷贝
    MyBuffer(const MyBuffer& other) : size_(other.size_), data_(new char[size_]) {
        std::memcpy(data_, other.data_, size_);
    }

    // 移动构造函数，转移资源所有权
    MyBuffer(MyBuffer&& other) noexcept : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    // 拷贝赋值函数，执行深拷贝
    MyBuffer& operator=(const MyBuffer& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = new char[size_];
            std::memcpy(data_, other.data_, size_);
        }
        return *this;
    }

    // 移动赋值函数，转移资源所有权
    MyBuffer& operator=(MyBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    // 析构函数，释放内存
    ~MyBuffer() {
        delete[] data_;
    }

private:
    size_t size_;
    char* data_;
};
