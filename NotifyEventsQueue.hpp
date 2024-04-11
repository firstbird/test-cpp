
#include <mutex>

class NotifyEventsQueue {
public:
	static NotifyEventsQueue& getInstance() {
		static NotifyEventsQueue instance;
		return instance;
	}

	bool handleMsg(std::string notifyType);
	void clear();

private:
	NotifyEventsQueue() {}
	~NotifyEventsQueue() {}

	NotifyEventsQueue(const NotifyEventsQueue&) = delete;
	NotifyEventsQueue &operator=(const NotifyEventsQueue &) = delete;

	std::mutex mMutex;
};