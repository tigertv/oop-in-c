#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyClass MyClass;

MyClass* new_MyClass();
void MyClass_setI(MyClass* this, int i);
int MyClass_getI(MyClass* this);

struct MyClass {
	int i;
	void (* const setI)(MyClass *this, int i);
	int (* const getI)(MyClass *this);
} MyClass_def = {1, MyClass_setI, MyClass_getI};

MyClass* new_MyClass() {
	MyClass *o = malloc(sizeof(MyClass));
	memcpy(o, &MyClass_def, sizeof MyClass_def);
	return o;
}

void MyClass_setI(MyClass* this, int i) {
	this->i = i;
}

int MyClass_getI(MyClass* this) {
	return this->i;
}

int main() {
	MyClass a = MyClass_def;
	printf("a.getI() = %d\n", a.getI(&a));
	a.setI(&a, 777);
	printf("a.getI() = %d\n", a.getI(&a));

	MyClass *b = new_MyClass();
	printf("b->getI() = %d\n", b->getI(b));
	b->setI(b, 12345);
	printf("b->getI() = %d\n", b->getI(b));
	
	return 0;
}
