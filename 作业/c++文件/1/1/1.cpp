// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<iostream>
#include<iomanip>
using namespace std;
int main(){
	int a,n;
	for(a=1,n=0;a<=2000;a++){
		if(a%3==2&&a%5==3&&a%7==2){
			n++;
			cout<<setw(8)<<a;
		if(n%5==0)
			cout<<endl;}}
	system("pause");
		return 0;
}