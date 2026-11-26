//包含两个对象成员
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

class studentRoom
{
private:
	long number;
public:
	studentRoom(long num=0)
	{	
		number = num; 
		cout<<"赋给学生的宿舍号："<<number<<endl;
	}
	~studentRoom()
	{
		cout<<"删除宿舍号："<<number<<endl;
	}
};


class student   //包含两个对象成员：studentID,studentRoom
{
private:
    studentID id;    //此处成员对象的定义顺序决定了成员对象的构造函数的调用顺序
	studentRoom Roomnum;
	char name[20];
public:
 student(const char sname[]="no name",long sid=0,long snum=0):Roomnum(snum), id(sid)
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
   student ss("朱明",8002132,12);
}