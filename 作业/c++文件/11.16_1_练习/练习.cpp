// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include <iostream>
using namespace std;
void StringProcess(char str[], char processed_str[])
{
    int j = 0;
    /*本函数用于预处理字符串，删除空格、'\t'并将字母全部调整为大写*/
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\t' || str[i] == ' ')
            continue;
        else
        {
            processed_str[j] = str[i];
            if (processed_str[j] >= 'a' && processed_str[j] <= 'z')
                processed_str[j] -= ('a' - 'A');
            j++;
        }
    }
}
bool isPalin(char processed_str[])
{
    int tail = 0;
    while (processed_str[tail] != '\0')
        tail++;
    int i = 0;
    while (true)
    {
        if (processed_str[i] != processed_str[tail - i - 1])
            return false;
        if (tail - i - 1 <= i)
            return true;
        i++;
    }
}
int main()
{
    char str[256] = { '\0' };
    char processed_str[256] = { '\0' };
    cout << "Input a string:" << endl;
    cin.getline(str, 255);
    cout << "Initial String is:" << endl;
    cout << str << endl;
    StringProcess(str, processed_str);
    cout << "Processed String is:" << endl;
    cout << processed_str << endl;
    if (isPalin(processed_str))
        cout << "This string is a palindrome!" << endl;
    else
        cout << "This string is not a palindrome!" << endl;
    return 0;
}
