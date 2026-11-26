#include <iostream> 
using namespace std;
void transpose(int x[][3],int y[][2]);  //函数声明
// 形参数组中的第一维（高维）可以不写
//但是第二维（低维）一定要写
void  main( ) 
{
       int a[2][3]={{1,2,3},{4,5,6}};
       int b[3][2];
       transpose(a,b);
	   cout<<endl<<endl;
 }

void transpose(int x[][3], int y[][2])
{
	int i,j;
	cout<<"原矩阵a为"<<endl;  
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			cout<<x[i][j]<<"\t";
            y[j][i] = x[i][j];   //对每个元素进行转置变换；  
		}
		cout<<endl;
	}	
     cout<<endl<<"转置后的矩阵b为"<<endl;
     for(i=0;i<3;i++)
     {
		for(j=0;j<2;j++)
		{
			cout<<y[i][j]<<"\t";
		}
		cout<<endl;
      }
}
