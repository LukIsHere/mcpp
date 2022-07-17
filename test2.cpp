#include <iostream>
#include<thread>

using namespace std;
void Dowork()
{
    cout << "ok" << endl;
}

int main(){
    std::thread thre(Dowork);
    thre.join();
    return  0;
}