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
		void SelectSort();
		bool Insert(T & elem,int i);
		void print();
};

class Num
{
	int id;
public:
	Num(){}
	Num(int i){id=i;}
	bool operator < (Num ele) {return id<ele.id; }
	void show(){cout<<id<<"   ";}
};


int main()
{
	const int h=8;
	int i;

	Orderedlist<Num,100> ordlist;
	Num slist[h]={Num(49),Num(38),Num(65),Num(97),Num(76),Num(13),Num(27),Num(49)};

	for(i=0;i<h;i++)
	ordlist.Insert(slist[i],i);

	cout<<"Î´ÅÅÐò±í£º"<<endl;
	ordlist.print();

	cout<<"ÒÑÅÅÐò±í£º"<<endl;
	ordlist.SelectSort();
	ordlist.print();

	return 0;
}

template <typename T,int size>
void Orderedlist<T,size>::SelectSort()
{
	T temp;
	int i,j,k;

	
	for(i=0;i<last;i++)
	{
		k=i;
		temp=slist[i];
		for(j=i;j<=last;j++)
			if(slist[j]<temp)
			{
				k=j;
				temp=slist[j];
			}

		if(k!=i)
		{
			temp=slist[i];
			slist[i]=slist[k];
			slist[k]=temp;
		}
			

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
		//if(i%5==4) cout<<endl;	
	}
	cout<<endl;
}













