//【例7.4】定义复制构造函数 和复制赋值操作符实现深复制。 
#include <iostream>
using namespace std;

/*学生类定义：*/
class student
{
     char *pName; 
public:
     student(); //默认构造函数
     student(const char *pname); //带参数构造函数
     student(student &s); //复制构造函数
     ~student(); //析构函数
     student & operator=(student &s); 
}; //复制赋值操作符




/*主函数：*/
int main(void)
{
	student s1("范英明"),s2("沈俊"),s3;
	student s4=s1;
	s3=s2;
	return 0;
}





/*默认构造函数：*/
student :: student()
{
     cout<<"Constructor    ";
     pName=NULL;
     cout<<"默认"<<endl;
}
/*带参数构造函数：*/
student::student(const char *pname)
{
  cout<<"Constructor    ";
  if(pName=new char[strlen(pname)+1])    
       strcpy_s(pName, strlen(pname) + 1,pname);
  cout<<pName<<endl;
}
/*复制构造函数：*/
student::student(student &s)
{
    cout<<"Copy Constructor    ";
    if(s.pName)
    {
       if(pName=new char[strlen(s.pName)+1])
                strcpy_s(pName, strlen(s.pName) + 1,s.pName);
    }
    else  pName=NULL;
    cout<<pName<<endl;
}
/*析构函数：*/
student :: ~student()
{
    cout<<"Destructor    " ; 
    if(pName)   /*请修改一下p227页程序内容*/
    {
	 cout<<pName<<endl;    
        delete[] pName;
     }
} //释放字符串
/*复制赋值操作符：*/
student & student::operator=(student &s)
{
    cout<<"Copy Assign operator    ";
    //如原来已分配，应先撤销，再重分配
    if(pName) delete[ ] pName; 
    if(s.pName)
    {
       if(pName=new char[strlen(s.pName)+1])   
             strcpy_s(pName, strlen(s.pName) + 1,s.pName);
    }
    else pName=NULL;
    cout<<pName<<endl;
    return *this;
}
