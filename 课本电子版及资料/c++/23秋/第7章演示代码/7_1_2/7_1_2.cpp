//【例7.11】动态数组的建立与撤销

#include<iostream>
//#include<cstring>// 说明：包含了C++标准库中的字符串处理函数
//#include <string>
using namespace std;

void main()
{
	int n;
	char *pc;
	cout<<"请输入动态数组的元素个数：";
	cin>>n; //在运行时确定，可输入25 （因为下方有12个文字）
	pc=new char[n];
	strcpy_s(pc,25,"自由存储区内存的动态分配");  //第二个参数25必须写，
	//设第二个参数为x，则x的范围为： strlen("自由存储区内存的动态分配")+1  <= x <= n,   (n是pc所指向的动态内存的大小）
	cout<<endl<<pc<<endl;
	delete [] pc;

 /* 释放完空间后，再使用pc会输出乱值
 	cout<<pc<<endl;
	// */
	//说明1：释放pc所指向的n个字符的内存空间
	//就是告诉系统pc所指的内存空间可以分配给别的申请者
	
	// 说明2：不是删除指针pc本身，指针pc还是存在的，
	// 但此时pc没有指向一个合法的地址了。
	//为了避免出错，一般是将 pc = NULL;
}
