/* 输入一门课程的成绩，输出相应的等级；
分别使用if-else嵌套语句和switch语句来实现。
*/

#include <iostream>
using namespace std;

void main()
{
	double score;

	cout<<"请输入成绩:";
	cin>>score;

	cout<<"1、用if-else嵌套语句进行判断："<<endl;
	if( score>100||score<0)
		cout<<"成绩输入有误"<<endl;
	else if(score>=90)
		cout<<"成绩等级为：Grade A"<<endl;
	else if (score>=80)
		cout<<"成绩等级为：Grade B"<<endl;
	else if (score>=70)
		cout<<"成绩等级为：Grade C"<<endl;
	else if (score>=60)
		cout<<"成绩等级为：Grade D"<<endl;
	else
		cout<<"成绩等级为：Not Passed"<<endl;

	cout<<endl<<"2、用switch语句进行判断："<<endl;
	switch( int(score/10))   // score/10这样可以减少case的个数
	{
	case 10: case 9:cout<<"成绩等级为：Grade A"<<endl;break;
		//注意case 10对应的是100分
	case 8: cout<<"成绩等级为：Grade B"<<endl;break;
	case 7: cout<<"成绩等级为：Grade C"<<endl;break;
	case 6: cout<<"成绩等级为：Grade D"<<endl;break;
    default: cout<<"成绩等级为：Not Passed"<<endl;
	}
// 要注意if-else的配对、数据区间的划分；
// switch语句适合用整型进行常量匹配。
}