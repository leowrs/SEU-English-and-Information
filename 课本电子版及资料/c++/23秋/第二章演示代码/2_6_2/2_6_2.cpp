#include <iostream>
using namespace std;


void main(){

	int number, answer, cube;

	cin>>number;   // 输入要求立方根的整数
	if (number>=0)  
	{
		answer=0;

		do 
	   {
 	        cube=answer * answer * answer;
 	        if (cube == number)  {  cout<<"整数立方根是：" << answer << endl; break; }
 	        else  answer++;
		}while (cube<number);
 
 	    if (cube>number)  
			cout <<"无整数立方根"<<endl; 

	}
	else
		cout<<"输入错误—负值数据"<<endl;





}



 
     