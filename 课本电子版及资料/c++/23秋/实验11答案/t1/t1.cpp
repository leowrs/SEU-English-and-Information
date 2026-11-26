#include <iostream>
using namespace std;
#include "seqlist.h"
          
template <typename T, int size>
seqlist<T, size>   seqlist<T, size>::operator+=(seqlist seq)
{
    int i, j;
    for (i = 0; i < seq.Length() ; i++)  //  或者 i<seq.last+1
    {
        if (!IsIn(seq[i]))
        {
            j = 0;
            while (slist[j] < seq[i] && j < Length())  //必须要加 j<Length()
                j++;
            Insert(seq[i], j);
        }
    }
    return *this;
}

template <typename T, int size>
void  seqlist<T, size>::show()
{
    for (int i = 0; i < Length(); i++)
        cout << Get(i) << "  ";
    cout << endl;
}

void main()
{
    int i, a[5] = { 2,3,4,6,7 };//注意这些数据是已排序的，升序
    int b[5] = { 3,2,7,1,5}; //注意这些数据是无序的
	seqlist <int,100> seqlist1,seqlist2; //顺序表对象seqlisti的元素为整型

    for (i = 0; i < 5; i++)
    {
        seqlist1.Insert(a[i], i);
        seqlist2[i] = b[i];
    }
	
    cout << "seqlist1中的数据为：";
    seqlist1.show();
    cout << "seqlist2中的数据为：";
    seqlist2.show();

	seqlist1 += seqlist2;  //seqlist1中的数据是已排序的，升序

    cout << endl<<"运行+=后，seqlist1中的数据为：";
    seqlist1.show();
 

}


