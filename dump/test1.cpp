#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<unistd.h>
#include <list>

using namespace std;

void display(list<int> &l){
	list<int>::iterator i;
	for(i = l.begin(); i != l.end();i++){
		cout << *i << " ";
	}
}
void delete_elem(list<int> &l, int to_delete){
	list<int>::iterator i;
	for(i = l.begin(); i!=l.end();i++){
		if(*i == to_delete){
			i = l.erase(i);
			i--;
	}
	}
}
void insert_bef(list<int> &l, int insert_before, int val){
list<int>::iterator i;
	for(i = l.begin(); i != l.end(); i++){
		if(*i == insert_before){
			l.insert(i, val);
		}
	}
}
void insert_aft(list<int> &l, int insert_after, int val){
list<int>::iterator i;
	for(i = l.begin(); i != l.end(); i++){
		if(*i == insert_after){
			i++;
			l.insert(i, val);
			
		}
	}
}
void find_and_replace(list<int> &l, int old, int newv){
	list<int>::iterator i;
	for(i = l.begin(); i != l.end(); i++){
		if(*i == old){
			l.insert(i, newv);
			i = l.erase(i);
			
		}
	}
}
int main(){

//	cout << t << " " << t1;
	list<int> l{1,2,4,4,5,6,8};
	int del = 4;
	int ins = 5;
	delete_elem(l, del);
	insert_bef(l, ins, 999);
	insert_aft(l , ins, 997);
	find_and_replace(l, 1, 8743);
	display(l);
	
	
	
	//insert before
		
}


