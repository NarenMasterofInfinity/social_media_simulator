#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

int main(){
    string s = "nrengt";
    vector<string> v {"do","re","mi","sa"};
    string s1 =v.at(2);
    cout << v.erase(v.begin(),v.end()-1)[0] <<endl;
    list<int> l{1,2,34,5,1,1};
    l.unique();
    v.insert(v.begin(),"Dfaf");
    for(auto i : l){
        cout << i << " ";
    }
    
}