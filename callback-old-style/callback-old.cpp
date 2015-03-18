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
	void print2() { cb2_(userdata_); };	// callback�� ȣ���� �� ���� ���� pointer�� �ٽ� �Ѱ��ش�.

private:
	functor cb_;
	functor2 cb2_;
	void* userdata_;
};

class B
{
public:
	// C++98
	// callback function�� static���� ����Ǿ�� �Ѵ�.
	static void callee(void) {cout << "callee" << endl;};
	void test(A* a) {
		a->registerCallback(&B::callee);
	};

	// callee�� static func�̶� non-static member�� �������� ���ϴ� ������ �ִ�.
	// �׷��� this pointer�� ���� �����ϴ� ����� ����� �� �ִ�.
	static void callee2(void* userdata) { 
		B* b = (B*)userdata;
		b->member_ = 5;		// now you can access non-static member in static function!!
		cout << "calle2 " << b->member_ << endl;
	};
	void test2(A* a) {
		a->registerCallback2(&B::callee2, this);	// this�� ���� �����Ѵ�.
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