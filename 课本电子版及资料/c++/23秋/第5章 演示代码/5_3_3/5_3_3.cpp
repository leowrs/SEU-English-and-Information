#include <iostream>
using namespace std;

void main()
{
	int a=3;
 	int *p=&a;   //此处 *为说明符

	cout<<"a的地址："<<&a<<"\t a的值"<<a<<endl;
	cout<<"p的地址："<<&p<<"\t p的值"<<p
		<<"\t 访问p所指向的内存数据 *p="<<*p<<endl;

   /*  注意1： 指针所指向的数据类型与赋值对象的数据类型必须相同
	double num=3;
	p = &num;  //错误：数据类型不匹配

	//*/

  //*  注意2：在使用指针进行间接访问前，需要对指针进行赋值
 	int *s;  // 出错：编译时不提示error，但运行时出错
// 	int *s=&a;   //正确
	cout<<"s的值："<<s<<endl;
	*s=a;   // s没有进行赋值，以s的值作为存储地址，可能是不合法的，会超越界限。
		//*/
 // 为了防止使用到没有初始化的指针，在VC++中，
//程序会对未初始化的指针给个固定值，在Release模式下是出0x004080d0，
	//而在Debug模式下是0xcccccccc。

}

//0xcccccccc : Used by Microsoft's C++ debugging runtime library
//to mark uninitialised stack memory