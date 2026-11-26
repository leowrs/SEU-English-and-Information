// 向前生成链表算法
#include <iostream>
using namespace std;

typedef int Datatype;  //给int类型重新命名
struct node
{
   Datatype info;
   node *link;
};

node *createup()
{  
	Datatype data;
	node *head,*p;                       
	head=new node; //建立链表头结点  
	head->link=NULL;
	cout<<"向前生成链表算法。"<<endl;
	cout<<"请输入数据，以^Z结束输入"<<endl;
	while(cin>>data) //^Z结束输入(ctrl+Z)
	{	   
		p=new node; //每输入一个数申请一个结点
		p->info=data;    //添入数据
		p->link= head->link;  //新结点接到链尾 
		head->link=p; //尾指针到链尾 
	}
	return head;     //返回头指针
}      

void show(node *head)
// 链表的遍历：从链表的头开始依次对链表中的结点进行处理（输出数值）
{
	node *p =head;
	cout<<"输出链表中的数值(输出顺序：从头部到尾部)"<<endl;
	while(p->link!=NULL)
	{ 
		p=p->link;
		cout << p->info << "   ";
	}
	cout<<  endl;
}

void main()
{
	node *head;
	head = createup();
	show(head);

}



