
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <class T> 
void printVector(char *s,const vector<T> &v)
{
	cout<<s<<" = (";
	if(v.size() == 0) {
		cout<<")";
		return; 
	}
	vector<T>::const_iterator i=v.begin();
	for(;i<v.begin()+v.size()-1;i++)
		cout<<*i<<' ';
	cout<<*i<<")\n";
}

bool f1(int n)
{
	return n <4;
}

void main()
{
	int a[] ={1,2,3,4,5};
	vector<int> v1; 
	printVector("v1",v1);
	for (int j=1; j<=5;j++)
		v1.push_back(j);
	
	
	vector<int> v2(3,7);
	vector<int>:: iterator i1=v1.begin()+1;
	vector<int>   v3(i1,i1+2);
	vector<int> v4(v1); // v4=1 2 3 4 5 
	vector<int> v5(5); // v5= 0 0 0 0 0
	v5[1]=v5.at(3)=9; 
	//v5= 0 
	printVector("v3",v3);
	v3.reserve(6);
	printVector("v3",v3);
	v4.resize(7);
	printVector("v4",v4);
	v4.resize(3);
	v4.clear();
	
	sort(v5.begin(), v5.end());
	printVector("v5",v5);














