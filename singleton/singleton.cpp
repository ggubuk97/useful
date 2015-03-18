#include <iostream>
#include <mutex>

using namespace std;

class Singleton
{
public:
	static Singleton& GetInstance();

private:
	Singleton() {};
	~Singleton() {};


// C++03
//	Singleton(const Singleton&);
//	const Singleton& operator= (const Singleton&);

// C++11
	Singleton(const Singleton&) = delete;
	const Singleton& operator= (const Singleton&) = delete;

public:
	void print() { cout << "this : " << this << endl; }
};




//////////////////////////////////////////////////////////////////////
//	Implementation
//////////////////////////////////////////////////////////////////////

// Most simple way
/*
Singleton& Singleton::GetInstance()
{
	static Singleton instance;
	return instance;
}
*/

// Common way
Singleton& Singleton::GetInstance()
{
	static Singleton* instance = nullptr;
	if (!instance) {
		instance = new Singleton();
	}
	return *instance;
}



int main()
{
	Singleton& s = Singleton::GetInstance();
	s.print();
}



/////////////////////////////////////
//	Thread-safe problem.
/////////////////////////////////////

// solution 1 - use simple lock
// 항상 lock을 사용하기 때문에 client가 자주 GetInstance()를 호출할 경우 비용이 많이 드는 문제가 있다.
/*
Singleton& Singleton::GetInstance()
{
	std::mutex singleton_mutex;
	std::lock_guard<std::mutex> lock(singleton_mutex);

	static Singleton instance;
	return instance;
}
*/

// solution 2 - DCLP(Double Check Locking Pattern)
// 1번에서 문제가 된 mutex 비용의 문제가 없어졌다. 하지만 system에 따라 multi-thread 환경에서 문제가 되는 경우가 간혹 있다.
/*
Singleton& Singleton::GetInstance()
{
	static Singleton* instance = nullptr;
	if (!instance) {
		std::mutex singleton_mutex;
		std::lock_guard<std::mutex> lock(singleton_mutex);

		if (!instance) {
			instance = new Singleton();
		}
	}

	return *instance;
}
*/

// singleton은 호출되는 시점에 instance가 생성되는 lazy instantiation이다.
// lazy instantiation 모델 대신 main()이 호출되기 전이나 mutex lock으로 구현된 API 초기화 시점을 이용하는 방법이 있다.

// solution 3 - static initialization before main function call
/*
static Singleton& foo = Singleton::GetInstance();
int main()
{

}
*/

// solution 4 - explict API initialization
/*
void APIInitialize()
{
	std::mutex singleton_mutex;
	std::lock_guard<std::mutex> lock(singleton_mutex);

	Singleton::GetInstance();
}
*/

