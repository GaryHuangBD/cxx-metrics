//
// Created by garyhuang on 18-2-2.
//

#include<iostream>
using namespace std;
int main()
{
    int b = 10;
    int &a(b);
    int *aa = &b;
    cout << b<<endl;
}