#include <iostream> 
using namespace std; 
int main()
{
     int age1=18,age2=20,*p_age;
     p_age=&age1;    //情况1，见图
     cout<<"age of wang ping is"<<*p_age<<endl;
     p_age=&age2;    //情况2 
     cout<<"age of zhang ling is" <<*p_age<<endl;
     return 0;
}
