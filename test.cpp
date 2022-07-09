#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout << "hej" << endl;
    ofstream test("hellop.txt");
    test << "text 1" << endl
         << "text 2";
    test.close();
    string tt;
    ifstream test2("hellop.txt");
    while (getline(test2, tt))
    {
        cout << tt << endl;
    }
    int a = 10;
    int *b = &a;
    cout << a << endl;
    *b = 12;
    cout << a << endl;
    cout << b << endl;
}