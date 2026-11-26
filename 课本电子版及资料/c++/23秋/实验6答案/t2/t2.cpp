#include <iostream>
using namespace std;

void main()
{
	int digit[8];
	int subscript,i,num,num_reverse,num_origin;
	subscript = 0 ;//数组下标初始值为0

	cout<<"请输入一个不超过7位的正整数：";
	cin>>num;
//使用课本第48页的例2.15，来提取每个位上的数字
	num_origin = num;  //保留num的值
	do
	{
		digit[subscript] = num%10;
		num = num/10;
		subscript++;
	}while(num>0);   //提取num中每一位，并存到数组digit中

	num_reverse = 0;
	for(i=0; i< subscript; i++)
		num_reverse = num_reverse*10 + digit[i];
//	cout<<"反向后的整数是："<<num_reverse<<endl;
///*
	if(num_origin == num_reverse)   //回文数的判断
		cout<<num_origin<<"是回文数！"<<endl;
	else
		cout<<num_origin<<"不是回文数！"<<endl;
 //*/

/* 关于回文数的第二种判断方法，该方法可以用于判断任意的字符串是否是回文

	bool Is_palindrome = 1;
	for(i=0; i < subscript/2 ; i++)
		if( digit[i] != digit[subscript-1-i])
		{
			Is_palindrome = 0;
			break;
		}

	if (Is_palindrome == 1)
		cout<<num_origin<<"是回文数！"<<endl;
	else
		cout<<num_origin<<"不是回文数！"<<endl;

*/

}

