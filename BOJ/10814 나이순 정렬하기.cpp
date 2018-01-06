#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct person{
	int age, ind;
	string name;
	person(){};
	person(int age, int ind, string name){
		this->age = age;
		this->ind = ind;
		this->name = name;
	}
	bool operator < (person p) const{
		if(age == p.age) return ind < p.ind;
		return age < p.age;
	}
};

map<int, int> dup;
vector<person> p;
int main(){
	std::ios::sync_with_stdio(0);
	std:cin.tie(0);
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		int age; string name;
		cin >> age >> name;
		p.push_back({age, dup[age]++, name});
	}
	sort(p.begin(), p.end());
	for(int i = 0; i < p.size(); i++)
		cout << p[i].age << " " << p[i].name << "\n";
	return 0;
}