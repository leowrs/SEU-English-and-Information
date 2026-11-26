#include <iostream>
using namespace std;
#include "Ex7_5.h"   // <Ex7_5>不会搜索当前文件夹，"Ex7_5.h"会搜索当前文件夹
const int h=4;
void main()
{
	Node<int>* P1;
	List<int> list1,list2;
	int a[h],i,j;

	cout<<"1、请输入"<<h<<"个整数"<<endl;
	for(i=0;i<h;i++)
		cin>>a[i];
	
	for(i=0;i<h;i++)
	{
		P1=list1.CreatNode(a[i]);
		list1.InsertFront(P1);
		P1=list2.CreatNode(a[i]);
		list2.InsertRear(P1);
	}

	cout<<endl<<"2、输出list1的数据（向前生成）：";
	list1.PrintList();
	cout<<"list1的长度："<<list1.Length()<<endl;
	
	cout<<"输出list2的数据（向后生成）：";
	list2.PrintList();

	cout<<endl<<"3、请输入一个要求删除的整数：";
	cin>>j;
	P1 = list1.Find(j);

	if(P1!=NULL)
	{
		P1=list1.DeleteNode(P1);
		delete P1;
		cout<<"输出list1的数据：";
		list1.PrintList();
		cout<<"list1的长度："<<list1.Length()<<endl;
	}
	else cout<<"未找到！"<<endl;

	list1.MakeEmpty();  //清空list1
    cout<<endl<<"4、清空 list1后，再重新插入之前输入的数据"<<endl;

	for(i=0;i<h;i++)
	{
		P1=list1.CreatNode(a[i]);
		list1.InsertOrder(P1);
	}
	cout<<"按照升序插入后，list1的数据：";
	list1.PrintList();

	cout<<endl;
}