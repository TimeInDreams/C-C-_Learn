#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <set>
using namespace std;
int main()
{
    string name;
    int i = 0;
    //����map,<key_value,value>
    map<int , string> m;
    for ( i = 0; i < 5; i++ ){
        cin >> name;
        //����pair
        m.insert(make_pair(i,name));
    }
    //Ѱ��ֵ
    map<int ,string>::iterator ite;
    ite = m.find(3);
    if ( ite == m.end() ) cout << "not found\n";
    else cout << ite->second << endl;
    //ɾ��ֵ
    m.erase(3);


    set<int> s;
    for ( i = 0; i < 5; i++ ){
        s.insert(i);
    }
    auto ite = s.find(3);
    if ( ite == s.end() ) cout << "not found\n";
    else cout << "found\n";
    s.erase(3);
    return 0;
}
