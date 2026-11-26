// Original Author: GitHub @leowrs (https://github.com/leowrs)

template <typename T, int size>class seqlist
{
    T slist[size];   //存放顺序表的数组
    int Maxsize;   //最大可容纳项数 
    int last;    //已存表项的最后位置
public:
    seqlist() { last = -1; Maxsize = size; }    //初始化为空表
    int Length() const { return last + 1; } //计算表长度
    int Find(T& x)const;        // 寻找x在表中位置（下标）
    bool IsIn(T& x);          //判断x是否在表中
    bool Insert(T& x, int i);         //x插入到列表中第i个位置处（下标）
    bool Remove(T& x);            //删除x
    int Next(T& x);                      //寻找x的后继位置
    int Prior(T& x);                     //寻找x的前驱位置
    bool IsEmpty() { return last == -1; }                    //判断表是否空
    bool IsFull() { return last == Maxsize - 1; }          //判断表是否满
    T Get(int i) { return i<0 || i>last ? NULL : slist[i]; } //取第i个元素之值
    T& operator[](int i);   //重载下标运算符[]
    seqlist operator+=(seqlist);
    void show();
};


template <typename T, int size>
int seqlist<T, size>::Find(T& x) const
{
    int i = 0;
    while (i <= last && slist[i] != x) i++;  //顺序查找是否有x 
    if (i > last) return -1; //未找到，返回-1
    else return i; //找到，返回下标
}

template <typename T, int size>
bool seqlist<T, size>::Insert(T& x, int i)
{
    int j;
    if (i<0 || i>last + 1 || last == Maxsize - 1)
        return false;
    //插入位置不合理，不能插入（稳健性）
    else
    {
        last++;
        for (j = last; j > i; j--) slist[j] = slist[j - 1];
        //从表最后位置向前依次后移，空出指定位置来
        slist[i] = x;
        return true;
    }
}

template <typename T, int size>
T& seqlist<T, size>::operator[](int i)
{
    if (i > last + 1 || i < 0 || i >= Maxsize)
    {
        cout << "下标出界！" << endl;
        exit(1);
    }
    if (i > last) last++; //下标运算符[]，只能增加表的元素，不能减少
    return slist[i];
}

template <typename T, int size>
bool seqlist<T, size>::IsIn(T& x)
{
    int i = 0;
    bool found = 0;
    while (i <= last && !found) //换了一种方法来查找
        if (slist[i] != x) i++;
        else found = 1; //找到
    return found;
}

template <typename T, int size>
bool seqlist<T, size>::Remove(T& x)
{
    int i = Find(x), j; //先去找x在哪个位置
    if (i >= 0)
    {
        last--;
        for (j = i; j <= last; j++)
            slist[j] = slist[j + 1];
        //依次前移，保证表连续
        return true;
    }
    return false; //表中不存在x
}

template <typename T, int size>
int seqlist<T, size>::Next(T& x)
{
    int i = Find(x);
    if (i >= 0 && i < last) return i + 1; //x后继位置
    else return -1; //x不在表中，或在表末尾
}
template <typename T, int size>
int seqlist<T, size>::Prior(T& x)
{
    int i = Find(x);
    if (i > 0 && i <= last)  return i - 1; //x前驱的位置
    else return -1;
}

#pragma once
