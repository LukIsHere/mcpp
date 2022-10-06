#include <iostream>
#include <cmath>
using namespace std;

void add(int& t){
    t++;
}
int main() {
    int i = 0;
    add(i);
    std::cout << i << std::endl;
}