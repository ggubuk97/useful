#include <iostream>
using namespace std;

// define void pointer as a handle
typedef void *PVOID;
typedef PVOID HANDLE;

typedef void *HANDLE;
typedef void* handle;
//typedef (void*) handle2;	// compile error


class MyComponent
{
public:
	void print(void) { cout << "MyComponent" << endl; };
};


HANDLE createComponent()
{
	MyComponent* comp = new MyComponent();
	return (HANDLE)comp;
}

void printComponent(HANDLE h)
{
	MyComponent* handle = (MyComponent*)h;
	handle->print();
}


int main(int argc, char* argv[])
{
	HANDLE h = createComponent();
	printComponent(h);

	return 0;
}
