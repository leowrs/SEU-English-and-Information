#include <iostream.h>
#include <string.h>

void main()
{

	char s1[20];
	char s2[]="1234567890";
	char s3[20]="abcd";
  
 	 strcpy(s1,s3);     // 对未赋值的字符串s1
	 strcpy(s2,s3);   // 对已赋值的字符串s2
 	cout<<s1<<endl;
 	cout<<s2<<endl;
 
}
 