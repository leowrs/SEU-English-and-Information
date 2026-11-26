#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	int prime[21]={0};
	char str[50];
	ifstream ifile; //定义输入文件
	ifile.open("myfile.txt"); //作为输入文件打开
	ifile.getline(str,50); //标题从文件读入到str
	cout<<str<<'\n';
	for(int i=0;i<21;i++)
	{
		ifile>>prime[i];  // 逐个读取素数存入prime
		cout<<prime[i]<<'\t';
		if((i+1)%5==0)
			cout<<endl;
	}	
	ifile.close();
	cout<<endl;
	return 0;








}