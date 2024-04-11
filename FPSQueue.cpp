
#include<mutex>
#include<condition_variable>
#include<queue>

template<typename T>
class QueueFPS : public std:: queue<T>
{
public:
    QueueFPS(): counter(0) {}
    void push(const T& entry)
    {
        std::lock_guard<std::mutex> lock(mutex);

        std::queue<T>::push(entry);// ??
        counter += 1;
        _cv.notify_one();
        if (counter == 1) {
            // Start counting from a second frame(earmup)
            tm.reset();
            tm.start();
        }
    }

    T get() {
        std::lock_guard<std::mutex> lock(mutex);
        T entry = this->front();
        this->pop();
        return entry;
    }

    	/// <summary>
	/// 等待消息
	/// </summary>
	/// <param name="msg">消息对象</param>
	// void wait(T& msg) {
	// 	std::unique_lock<std::mutex>lck(_mtx);
	// 	while (!_queue.size()) {
    //         _cv.wait(lck);
    //     } 
	// 	msg = _queue.front();
	// 	_queue.pop();
	// }
    // https://blog.csdn.net/mo4776/article/details/119408716


    float getFPS()
    {
        tm.stop();
        double fps = counter / tm.getTimeSec();
        tm.start();
        return static_cast<float>(fps);
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(mutex);
        while (!this->empty()) {
           this->pop();
        }
    }
    
    unsigned int counter;
    
private:
    cv::TickMeter tm;
    std::mutex mutex;
    //条件变量
	std::condition_variable _cv;
};