// 【例4.6】含有成员对象的类的构造函数（完整版）
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
    student (const char sname[]="no name", long sid=0):id(sid)
    {
 	 strcpy_s(name,sname);
	 cout<<"学生名："<<name<<endl;
     } 
      ~student()
     {	
		  cout<<"删除学生名："<<name<<endl; 
	  }
 };

void main()
{
   student ss("朱明",8002132);
}