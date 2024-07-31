#include <list>
#include <iostream>
using namespace std;
int main(){
   list<int> l = {1};
   int i = *l.begin();
   l.pop_front(); 
}
