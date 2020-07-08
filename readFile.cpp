#include <fstream>
#include <iostream>
using namespace std;


int main() 
{
    char data[4096];
    // 以读模式打开文件
    ifstream infile; 
    // infile.open("126_20200628_152703.data"); 
    infile.open("a.txt"); 
    infile.read(data, 4096);

    cout << data << endl;

    // 关闭打开的文件
    infile.close();
    return 0;
}



