// 先后生成链表算法
#include <iostream>
using namespace std;

typedef int Datatype;  //给int类型重新命名
struct node
{
   Datatype info;
   node *link;
};

node *createdown()
{  
	Datatype data;
	node *head,*tail,*p;                       
	head=new node; //建立链表头结点  
	tail=head;
	cout << "输入数据（以ctrl+z为结束符）：";
	while(cin>>data) //^Z结束输入(ctrl+Z)
	{	   
		p=new node; //每输入一个数申请一个结点
		p->info=data;    //添入数据
		tail->link= p;  //新结点接到链尾 
		tail=p; //尾指针到链尾 
	}
	tail->link=NULL; //链尾空指针
	return head;     //返回头指针
}      



void show(node *head)
// 链表的遍历：从链表的头开始依次对链表中的结点进行处理（输出数值）
{
	node *p =head;
	cout<<"输出链表中的数值（从首结点到尾结点的顺序）"<<endl;
	while(p->link!=NULL)
	{ 
		p=p->link;
		cout<<p->info<<"  "<<endl;
	}

}

void main()
{
	node *head;
	head = createdown();
	show(head);

}




