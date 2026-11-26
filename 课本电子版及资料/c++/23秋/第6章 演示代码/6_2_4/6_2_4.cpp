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
		void BubbleSort();
		bool Insert(T & elem,int i);
		void print();
};

class student
{
	int id;
	string name;
	char sex;
	int age;
	string address;
	float eng,phy,math,electron; // 英语、物理、数学和电子学成绩
public:
	student(){}
	student(int,string,char,int,string,float,float,float,float);
	bool operator < (student ele) {return id<ele.id;}
	void show(){cout<<'\t'<<id<<'\t'<<name<< '\t'<<sex
		<<'\t'<<age<<'\t'<<address<<'\t'<<eng<<'\t'<<phy<<'\t'<<math<<'\t'
	<<electron<<endl; }

};


int main()
{
	const int h=4;
	int i;
	
	Orderedlist<student,100> ordlist;

	student n[h]={
		student(6004327,"张菲",'m',19,"北京路58号",80,89,88,98),
		student(6004121,"光羽",'w',19,"上海路58号",82,92,83,92),
		student(6004118,"刘蓓",'w',18,"南京路58号",84,83,88,90),
		student(6004219,"赵芸",'m',18,"天津路58号",81,86,87,91)
	};

	for(i=0;i<h;i++)
		ordlist.Insert(n[i],i);  //建立顺序表
	
	cout<<"未排序表"<<endl;
	ordlist.print();

	cout<<"已排序表"<<endl;
	ordlist.BubbleSort();
	ordlist.print();


	return 0;
}






student::student(int i,string n,char s,int a,string add,float en,float ph, float ma, float ele)
{
	id = i;
	name = n;
	age = a;
	address = add;
	eng = en;
	phy = ph;
	math = ma;
	electron = en;
}


template <typename T,int size>
void Orderedlist<T,size>::BubbleSort()
{
	bool noswap;
	int i,j;
	T temp;
	for(i=0;i<last;i++)
	{
		noswap=true;
		for(j=last;j>i;j--)
		{
			if(slist[j]<slist[j-1])
			{
				temp=slist[j];
				slist[j]=slist[j-1];
				slist[j-1]=temp;
				noswap=false;
			}
		}
		if(noswap) 
			break;
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