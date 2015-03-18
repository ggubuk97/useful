/// C++98 style callback

#include <iostream>
using namespace std;

// define function pointer
typedef void(*functor)(void);
typedef void(*functor2)(void*);


class A
{
public:
	void registerCallback(functor callback) {
		cb_ = callback;
	};
	void print() { cb_(); };


	void registerCallback2(functor2 callback2, void* userdata) {
		cb2_ = callback2;
		userdata_ = userdata;
	};
	void print2() { cb2_(userdata_); };	// callback을 호출할 때 전달 받은 pointer를 다시 넘겨준다.

private:
	functor cb_;
	functor2 cb2_;
	void* userdata_;
};

class B
{
public:
	// C++98
	// callback function은 static으로 선언되어야 한다.
	static void callee(void) {cout << "callee" << endl;};
	void test(A* a) {
		a->registerCallback(&B::callee);
	};

	// callee는 static func이라서 non-static member에 접근하지 못하는 단점이 있다.
	// 그래서 this pointer를 같이 전달하는 방법을 사용할 수 있다.
	static void callee2(void* userdata) { 
		B* b = (B*)userdata;
		b->member_ = 5;		// now you can access non-static member in static function!!
		cout << "calle2 " << b->member_ << endl;
	};
	void test2(A* a) {
		a->registerCallback2(&B::callee2, this);	// this를 같이 전달한다.
	};
private:
	int member_;
};

int main()
{
	A* a = new A();
	B b;
	b.test(a);
	a->print();

	b.test2(a);
	a->print2();

	return 0;
}