#include <mutex>

using namespace std;
class Singleton {
public:
	Singleton& getInstance() {
		static Singleton s;
		return s;
	}
private:
	Singleton() {}	
	~Singleton() {}
	Singleton(const Singleton &singleton) = delete;
	Singleton(const Singleton &&singleton) = delete;
	Singleton &operator=(const Singleton &singleton) = delete;
	Singleton &operator=(const Singleton &&singleton) = delete;
};

class Singleton {
public:
	Singleton* getInstance() {
		if (!_instance) {
			mu.lock();
			if (!_instance) {
				_instance = new Singleton();
			}
			mu.unlock();
		}
		return _instance;
	}	
private:
	Singleton() {}	

	Singleton *_instance;
	mutex mu;
};
