#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct person{
	string name;
	int s1, s2, s3;
	person(){};
	person(string name, int s1, int s2, int s3){
		this->name = name;
		this->s1 = s1;
		this->s2 = s2;
		this->s3 = s3;
	}
	int operator < (person p) const{
		if(s1 == p.s1){
			if(s2 == p.s2){
				if(s3 == p.s3)
					return name< p.name;
				return s3 > p.s3;
			}
			return s2 < p.s2;
		}
		return s1 > p.s1; 
	}
};
vector<person> p;

int main(){
	std::ios::sync_with_stdio(0);
	std:cin.tie(0);
	int n; cin >> n;
	string name;
	int s1, s2, s3;
	for(int i = 0; i < n; i++){
		cin >> name >> s1 >> s2 >> s3;
		p.push_back({name, s1, s2, s3});
	}
	sort(p.begin(), p.end());
	for(int i = 0; i < n; i++)
		cout << p[i].name << "\n";
	return 0;
}