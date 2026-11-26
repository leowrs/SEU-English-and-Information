// 链表查找，按关键字
#include <iostream>
using namespace std;

typedef int Datatype;  //给int类型重新命名
struct node
{
   Datatype info;
   node *link;
};

node *createup(Datatype [], int);
void show(node *head);
node *traversal(node *,Datatype );

void main()
{
	node *head;

	Datatype arr[5] = {1,2,3,4,5};
	head = createup(arr,5); 
	show(head);

	node *p;
	int data;
	cout<<endl<<"请输入需要查询的数：";
	cin>>data;
	p = traversal(head,data);
	cout<<endl<<"查找结果是： ";
	if(p!=NULL)
		cout<<"找到了！" << endl;
	else
		cout<<"没找到！"<<endl;
	cout<<endl;

}


node *traversal(node *head,Datatype data)
{
node *p=head->link;
while(p!=NULL&&p->info!=data) 
	p=p->link;
return p;     //p为NULL则未找到
}
//返回值为指针p，指向链表中找到的结点。

node *createup(Datatype arr[], int size) //向前生成链表
{  
	node *head,*p;                       
	head=new node; //建立链表头结点  
	head->link=NULL;
	int i=0;
	while(i<size) //^Z结束输入(ctrl+Z)
	{	   
		p=new node; //每输入一个数申请一个结点
		p->info=arr[i++];    //添入数据
		p->link= head->link;  //新结点接到表头结点的后面 
		head->link=p; //尾指针到链尾 
	}
	return head;     //返回头指针
}      

void show(node *head)
{
	node *p =head;
	cout<<"输出链表中的数值"<<endl;
	while(p->link!=NULL)
	{ 
		p=p->link;
		cout<<p->info<<"  ";
	}
	cout<<endl;

}