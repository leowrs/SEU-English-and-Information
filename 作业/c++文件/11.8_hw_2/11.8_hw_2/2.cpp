// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
#include<iomanip>
using namespace std;
 int judge(int m);
 void main()
 {
	 cout<<"4~50之间的偶数可以表示为两个素数之和"<<endl;
	 int a=0,i;
	 for(i=4;i<=50;i+=2)
	 {
		 int n,m;
		 for(n=2;n<=50;n++)
		{	 if(judge(n))
			 {
				 for(m=n;m<=50;m++)
				 {
					 if(judge(m))
					 {
						 if(i==n+m)
							 {
								 cout<<setw(2)<<i<<"="<<setw(2)<<n<<"+"<<setw(2)<<m<<'\t';
								 a++;
								 if(a%5==0)
								 cout<<endl;
								 
								 break;
						     }
					 }
				 }
		     }
		 }
	 }
	 cout << endl;
	 system("pause");
 }
 int judge(int m)
 {
	 int n=1,i;
	 for(i=2;i<m;i++)
	 {
		 if(m%i==0) 
		 {
			 n=0;
			 break;
		 }
		 else n=1;
	 }
	 return n;
 }