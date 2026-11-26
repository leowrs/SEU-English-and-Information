// 【例7.5_h】单链表类模板
/*定义结点类模板*/
template<typename T>class List; //提前引用声明
template<typename T>class Node
{
    T info;                                     //数据域
    Node<T> *link; //指针域,<>中是参数名表,类模板实例化为类
public:
    Node();   //生成头结点的构造函数
    Node(const T & data); //生成一般结点的构造函数
    void InsertAfter(Node<T> * p); //在当前结点后插入      
    Node<T>* RemoveAfter();  //删除当前结点的后继结点
    friend class List<T>;  //以List为友元类    
};

template <typename T> Node<T>::Node(){link=NULL;}

template <typename T> Node<T>::Node(const T & data)
{
	info=data;
	link=NULL;
}


template <typename T>void  Node<T>::InsertAfter(Node <T> *p)
{
	p->link=link;
	link=p;
}


template <typename T>Node<T>*  Node<T>::RemoveAfter()
{
	Node<T> *temp=link;
	if(link==NULL) 
		temp = NULL;
	else 
		link=temp->link;
	return temp;
}


//////////////////////////////////////////////////
/*定义链表类 */
template<typename T>class List
{
    Node<T> *head,*tail; //链表头指针和尾指针
public:
    List();  //构造函数，生成头结点(空链表)
    ~List(); //析构函数
    void MakeEmpty(); //清空链表，只余表头结点
    Node<T>* Find(T data); //搜索结点，返回地址
    int Length();    //计算单链表长度
    void PrintList();   //打印链表的数据域
    void InsertFront(Node<T>* p);  //可用来向前生成链表
    void InsertRear(Node<T>* p);   //可用来向后生成链表 
    void InsertOrder(Node<T> *p);  //按升序生成链表
    Node<T>*CreatNode(T data);   //创建结点(孤立结点)
    Node<T>*DeleteNode(Node<T>* p); //删除指定结点
}; 

template <typename T>List<T>::List()
{
	head=tail=new Node<T>();
}

template <typename T>List<T>::~List()
{
	MakeEmpty();
	delete head;
}

template <typename T>void List<T>::MakeEmpty()
{
	Node<T>* temp;
	while(head->link!=NULL)
	{
		temp=head->link;
		head->link=temp->link;
		delete temp;
	}
}

template <typename T> Node<T>* List<T>::Find(T data)
{
	Node<T>* temp=head->link;
	while(temp!=NULL && temp->info!=data)
		temp=temp->link;
	return temp;
}


template <typename T>int List<T>::Length()
{
	Node<T>* temp=head->link;
	int count=0;
	while(temp!=NULL)
	{
		temp=temp->link;
		count++;
	}
	return count;
}


template <typename T>void List<T>::PrintList()
{
	Node<T>* temp=head->link;
	while(temp!=NULL)
	{
		cout<<temp->info<<"  ";
		temp=temp->link;
	}
	cout<<endl;
}



template <typename T>void List<T>::InsertFront(Node<T>*p) //链头插入
{
	p->link=head->link;
	head->link=p;
	if(tail==head) tail=p;
}



template <typename T>void List<T>::InsertRear(Node<T>* p)  // 链尾插入
{
	p->link = tail->link;
	tail->link = p;
	tail = p;
}



template <typename T>void List<T>::InsertOrder(Node<T>* p)  // 升序插入
{
	Node<T>* temp=head->link, *tempQ=head;
	while(temp!=NULL)
	{
		if(p->info < temp->info) break;
		tempQ=temp;
		temp=temp->link;
	}
	tempQ->InsertAfter(p);
	if(tail == tempQ)
		tail=tempQ->link;
}



template <typename T> Node<T>* List<T>::CreatNode(T data)  // 创建一个结点
{
	Node<T>* temp = new Node<T>(data);
	return temp;
}


template <typename T> Node<T>* List<T>::DeleteNode(Node<T>* p)
{
	Node<T>* temp=head;
	while(temp->link!=NULL && temp->link!=p)
		temp=temp->link;
	
	if(temp->link == tail)
		tail = temp;
	return temp->RemoveAfter();

}