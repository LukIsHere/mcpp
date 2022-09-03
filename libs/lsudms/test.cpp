#include <iostream>
#include "lsudms.hpp"

using namespace std;

int main(){
    ums::connect();
    
    while (true)
    {

        //
        ums::db dbb("test","test.txt");
        //

        string in;
        cin >> in;
        ums::cmd cmd = ums::cmd(in);
        string first =cmd.get(0);
        if(first=="test"){
            cout << ums::list("hi,hello").include("hi") << endl;
            ums::user u = ums::user("{\"haj\":\"hi\"}");
            cout << "export {\"haj\":\"hi\"} : " << u.getS();
            if(u.getS()=="{\"haj\":\"hi\"}") cout << " [ok]" << endl;
            else cout << " [error]" << endl;
            cout << "{\"haj\":\"hi\"} : get haj -> " << u.gets("haj");
            if(u.gets("haj")=="hi") cout << " [ok]" << endl;
            else cout << "[error]" << endl;
            ums::user u2 = ums::user("{\"haj\":\"hi,hello,how\"}");
            cout << "{\"haj\":\"hi,hello,how\"} : include(hello) -> ";
            if(u2.Linclude("haj","hello")) cout << "true [ok]" <<endl;
            else cout << "false [error]" << endl;
            cout << "{\"haj\":\"hi,hello,how\"} : include(howw) -> ";
            if(!u2.Linclude("haj","howw")) cout << "false [ok]" <<endl;
            else cout << "true [error]" << endl;
            ums::user u3 = ums::user("{\"haj\":\"hi\"}");
            cout << "{\"haj\":\"hi\"} : getI(haj) -> ";
            if(u3.geti("haj")==-1)cout << -1 << " [ok]"<<endl;
            else cout << u3.geti("haj") << " [error]" << endl;
            ums::user u4 = ums::user("{\"haj\":\"43\"}");
            cout << "{\"haj\":\"43\"} : getI(haj) -> ";
            if(u4.geti("haj")==43)cout << 43 << " [ok]"<< endl;
            else cout << u4.geti("haj") << " [error]" << endl;
        }
        if(first=="sort"){
            ums::top top = ums::top(ums::score(0,""));
            top.addS(ums::score(100,"hik"));
            top.addS(ums::score(130,"fik"));
            top.addS(ums::score(140,"hif"));
            cout << top.out() << endl;
        }
        if(first=="mkdb"){
            dbb.addU(103,ums::user("{\"haj\":\"hi\"}"));
            dbb.addU(100,ums::user("{\"haj\":\"hell\"}"));
            dbb.save();
        }
        if(first=="rddb"){
            dbb.load();
        }
        if(first=="logdb"){
            dbb.log();
        }
    }
    
}