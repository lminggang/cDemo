#include <iostream>
using namespace std;

std::string get_ip(std::string ip_last)
{   
    std::string ip_top = "192.168.1.";
    return ip_top + ip_last;
}

int main()
{
    std::string ip_last;
    cout << "请输入IP后缀: ";
    cin >> ip_last;

    std::string ip = get_ip(ip_last);
    cout << ip << endl;

    return 0;
}



