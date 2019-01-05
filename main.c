#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////

typedef struct MyChildClass MyChildClass;

MyChildClass* new_MyChildClass();
void MyChildClass_setI(MyChildClass* this, int i);
int MyChildClass_getI(MyChildClass* this);
void MyChildClass_setM(MyChildClass* this, int m);
int MyChildClass_getM(MyChildClass* this);

struct MyChildClass {
	MyClass parent;
	int m;
	void (* const setI)(MyChildClass *this, int i);
	int (* const getI)(MyChildClass *this);
	void (* const setM)(MyChildClass *this, int m);
	int (* const getM)(MyChildClass *this);
} MyChildClass_def = { {1, MyClass_setI, MyClass_getI}, 2, MyChildClass_setI, MyChildClass_getI, MyChildClass_setM, MyChildClass_getM};

MyChildClass* new_MyChildClass() {
	MyChildClass *o = malloc(sizeof(MyChildClass));
	memcpy(o, &MyChildClass_def, sizeof MyChildClass_def);
	return o;
}

void MyChildClass_setM(MyChildClass* this, int m) {
	this->m = m;
}

int MyChildClass_getM(MyChildClass* this) {
	return this->m;
}

void MyChildClass_setI(MyChildClass* this, int i) {
	this->parent.i = i;
}

int MyChildClass_getI(MyChildClass* this) {
	return this->parent.i;
}

/////////////////////////////////////////////////////

int main() {
	MyClass a = MyClass_def;
	printf("a.getI() = %d\n", a.getI(&a));
	a.setI(&a, 776);
	printf("a.setI(776)\n");
	printf("a.getI() = %d\n", a.getI(&a));

	MyClass *b = new_MyClass();
	printf("b->getI() = %d\n", b->getI(b));
	b->setI(b, 12345);
	printf("b->setI(12345)\n");
	printf("b->getI() = %d\n", b->getI(b));
	printf("\n");
	
	MyChildClass *c = new_MyChildClass();
	c->setI(c, 345);
	printf("c->setI(345)\n");
	printf("c->getI() = %d\n", c->getI(c));
	printf("c->getM() = %d\n", c->getM(c));

	MyChildClass *d = new_MyChildClass();
	printf("d->getI() = %d\n", d->getI(d));
	printf("d->getM() = %d\n", d->getM(d));
	d->setM(d, 5555);
	printf("d->setM(5555)\n");
	printf("d->getM() = %d\n", d->getM(d));
	printf("\n");

	MyChildClass e = MyChildClass_def;
	printf("e.getM() = %d\n", e.getM(&e));
	e.setM(&e, 98);
	printf("e.setM(98)\n");
	printf("e.getM() = %d\n", e.getM(&e));
	printf("e.getI() = %d\n", e.getI(&e));
	e.setI(&e, 99);
	printf("e.setI(99)\n");
	printf("e.getI() = %d\n", e.getI(&e));

	MyChildClass f = MyChildClass_def;
	printf("f.getI() = %d\n", f.getI(&f));
	printf("f.getM() = %d\n", f.getM(&f));

	return 0;
}
