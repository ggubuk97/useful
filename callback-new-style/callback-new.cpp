//C++11 style callback

#include <iostream>
#include <functional>
using namespace std;


class A
{
public:

	void registerCallback(std::function<void(void)> f) { cb_ = f; };
	// this is same with above
	//void registerCallback(const std::function<void(void)>& f) { cb_ = f; };
	void print() { cb_(); };

private:
	std::function<void()> cb_;
};


class B
{
public:
	void callee() { std::cout << "I'm B callee" << std::endl; };
	void test() {
		A a;
		// std::bind 를 이용해서 호출하면 callee()가 static function이 아니어도 된다.
		a.registerCallback(std::bind(&B::callee, this));
		a.print();
	};
};


int main()
{
	B b;
	b.test();
}