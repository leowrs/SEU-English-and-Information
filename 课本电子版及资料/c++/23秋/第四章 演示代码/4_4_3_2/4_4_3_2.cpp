//在student构造函数头部的冒号表示要对对象成员的构造函数进行调用。
//但在构造函数的声明中，冒号及冒号以后部分必须略去。

#include <iostream>
using namespace std;

class studentID
{
private:
	long value;
public:
   studentID(long id=0)
   {
	value=id;
	cout<<"赋给学生的学号："<<value<<endl;
    }
   ~studentID()
   {
	cout<<"删除学号："<<value<<endl;
    } 
};

class student
{
private:
    studentID id;  
	char name[20];
public:
    student (const char [], long);
// 在构造函数的声明中，冒号及冒号以后部分必须略去！！！
     ~student();
 };

student::student(const char sname[]="no name",long sid=0):id(sid)
// 在构造函数的定义中，注意冒号及冒号以后部分
    {
 	 strcpy_s(name,sname);
	 cout<<"学生名："<<name<<endl;
     } 


int main()
{
   student ss("朱明",8002132);
   return 0;
}



student:: ~student()
     {	cout<<"删除学生名："<<name<<endl;  }