#include <iostream>
#include <string>
using namespace std;

template <typename T, int size> class Orderedlist
{
	int maxsize;
	int last;
	T slist[size];
	public:
		Orderedlist(){ last=-1; maxsize=size;}
		void InsertSort();
		bool Insert(T & elem,int i);
		void print();
};

class Element
{
	string  key;	// 其他域省略
public:
	bool operator<(Element ele)   {return key<ele.key;}
	void putkey(string k){key=k;}
	void show(){cout<<key<<'\t';}
};


int main()
{
	const int h=10;
	int i;
	
	Orderedlist<Element,100> ordlist;
	string mslist[h]={"cat","book","car","zoo","fish","cab","dog","cap","fox","can"};
	Element n[h];

	for(i=0;i<h;i++)
		n[i].putkey(mslist[i]);
	
	for(i=0;i<h;i++)
		ordlist.Insert(n[i],i);  //建立顺序表
	
	cout<<"未排序表："<<endl;
	ordlist.print();

	cout<<"已排序表："<<endl;
	ordlist.InsertSort();
	ordlist.print();



	return 0;
}



template <typename T,int size>
void Orderedlist<T,size>::InsertSort()
{
	T temp;
	int i,j;
	for(i=1;i<=last;i++)
	{
		temp=slist[i];
		j=i;
		while(j>0 && temp<slist[j-1])
		{
			slist[j]=slist[j-1];
			j--;
		}
		slist[j]=temp;

	}

}



template <typename T,int size>
bool Orderedlist<T,size>::Insert(T & elem, int i)
{
	int j;
	if (i<0||i>last+1||last==maxsize-1) return false;
	else
	{
		last++;
		for (j=last;j>i;j--) slist[j]=slist[j-1];
		slist[i]=elem;
		return true;
	}
}

template <typename T,int size>
 void Orderedlist<T,size>::print()
{
	int i;
	for(i=0;i<=last;i++)
	{
		slist[i].show();
		if(i%5==4) cout<<endl;	
	}
	cout<<endl;
}