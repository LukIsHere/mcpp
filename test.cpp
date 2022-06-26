#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout << "hej" << endl;
    ofstream test("hello.txt");
    test << "text 1" << endl
         << "text 2";
    test.close();
    string tt;
    ifstream test2("hello.txt");
    while (getline(test2, tt))
    {
        cout << tt << endl;
    }
}