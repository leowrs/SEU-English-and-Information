#include <iostream>
using namespace std;
class Time 
{
public:
   Time( ); 
    void show_time( ); 
private:
    int hour,minute,sec;
};
void main( )
{
     Time t1;    
     t1.show_time( );                  
}
// /*
Time::Time( ) 
{
    cout << "ÊäÈëÊ±¡¢·Ö¡¢Ãë£º";
      cin>>hour;
      cin>>minute;
      cin>>sec;
}    //*/
void Time::show_time( )
{
    cout<<hour+1<<":" <<minute<<":"<<sec<<endl;
}

