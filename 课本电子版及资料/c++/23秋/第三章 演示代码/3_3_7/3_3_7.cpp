#include<iostream>
using namespace std;
int t=10;	// 全局变量
void fun()
{
	cout<<"t="<<t<<endl;
	int t=5;	// 局部变量
	cout<<"t="<<t<<endl;
	cout << "t=" << ::t << endl;

}
int main()
{
	fun();
    return 0;
}
