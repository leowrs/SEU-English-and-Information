#include <fstream>
using namespace std;

int main()
{
	int prime[]={101,103,107,109,113,127,131,
		137,139,149,151,157,163,167,173,179,181,191,193,197,199};


	ofstream ofile; //定义输出文件
//	ofile.open("C:\\dd\\myfile.txt"); //作为输出文件打开
 	ofile.open("myfile.txt"); //作为输出文件打开
	ofile<< " 100~200间的素数"<<endl; //标题写入文件
	for(int i=0;i<sizeof(prime)/sizeof(prime[0]);i++)
	{
		ofile<<prime[i]<<'\t';  //将素数逐个写入文件
		if((i+1)%10==0) ofile<<'\n';  //每10个换行
	}
    ofile.close () ;	
	return 0;
}