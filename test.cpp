#include <iostream>
#include <fstream>
#include <map>
using namespace std;
map<string, string> symbolTable;
void loadfile()
{
    string line;
    ifstream file("test.txt");
    while (getline(file, line))
    {
        symbolTable.insert(pair<string, string>(to_string(rand()), line));
    }
    file.close();
}
void savefile()
{
    ofstream test("test.txt");
    test << "hej" << endl;
    test.close();
}
int main()
{
    srand(time(0));
    loadfile();
    symbolTable.insert(pair<string, string>("hi", "hello"));
    map<string, string>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); it++)
    {
        cout << it->first // string (klucz)
             << ':'
             << it->second // string wartość
             << endl;
    }
}