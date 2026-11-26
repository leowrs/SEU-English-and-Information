// 【例7.3】演示自由存储区对象分配和释放
#include <iostream>
#include <string>
using namespace std;

class CGoods
{
     string Name; 
	 int  Amount;
     float Price;  
	 float Total_value;
public:
     CGoods() {cout<<"调用默认构造函数"<<endl;}
     CGoods(string name,int amount ,float price)
     {
	 cout<<"调用三参数构造函数"<<endl;
	 Name=name;  
	 Amount=amount;
	 Price=price;  
	 Total_value=price*amount;	
      }
     ~CGoods(){ cout<<"调用析构函数"<<endl;}
	 void show(){cout<<"hello"<<endl;}
};

int main()
{
  int n;
  CGoods *pc,*pc1,*pc2;
  pc=new CGoods("夏利2000",10,118000);   //调用三参数构造函数 
  pc1=new CGoods();               //调用默认构造函数,也可写成不带括号，即，pc1=new CGoods; 
  cout<<"     输入商品类数组元素数: ";
  cin>>n;
  pc2=new CGoods[n];  //动态建立数组，不能初始化，调用n次默认构造函数  
 
    delete pc;   //调用析构函数1次
     delete pc1;  //调用析构函数1次
 // delete pc,pc1;  //delete只有释放一个指针所指向的空间
  delete  [] pc2; //调用析构函数3次   ， A行
  return 0;
}
// 如果把A行改为： delete   pc2;  看看程序运行的结果

