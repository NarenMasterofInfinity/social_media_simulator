#include <time.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
  time_t rem = time(NULL);
  sleep(2);
  int t =  108971619;
  if(t > 60 && t < 3600){
    cout << t/60 << "minutes ago";
  }
  else if (t > 60 && t < 86400){
    cout << t/3600 << "hours ago";
  }
  else if(t > 60){
    cout << t/86400 << "days ago";
  }
  else{
    cout << t << "seconds ago";
  }
}