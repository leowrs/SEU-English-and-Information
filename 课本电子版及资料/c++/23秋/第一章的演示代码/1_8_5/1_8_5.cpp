#include <iostream>
using namespace std;
int main()
{
	   char city[5];
	   cout<<"Input the city :"<<endl;   
  //    cin.getline(city,5);			  
  cin>>city;   //与cin.getline的重要区别：不检查字符数组的长度（在数组空间不够的情况下程序会出错）
       cout<<"接受的字符串：" <<city<<endl;
	   system("pause");
	   return 0;
// input  :   nanjing
}
