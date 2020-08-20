#include <string>
using namespace std;
/////////////////////////////////////////// class diagram ///////////////////////////////////////////
/*
@startuml
skinparam classAttributeIconSize 0
class Animal
{
-	name:string
#	id: int
+	setName(string name):void
+	{abstract} move(): void
+	{static}  count(): int
}
@enduml
*/

class Animal
{
private:
	string name;
protected:
	int id;
public:
	void setName(string name) {}
	void virtual move() {}
	static int count() {}
};

/////////////////////////////////////////// Composition ///////////////////////////////////////////
class Point
{
};

class Circle
{
private:
	Point center;
};


class Heart
{
};

class Person
{
private:
	Heart heart;
};


int main() 
{
	
}