#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, ans1, ans2, end = 1000000, sum;
	string s;
	vector<int> v(1000000, 0);
	
	getline(cin , s);
	n = stoi(s);
	
	// Part 1
	for(int i = 0; i < end; i++){
	    sum = 0;
	    for(int j = 1; j <= sqrt(i); j++){
	        if(i % j == 0){
	            sum += 10*j;
	            if(j != i/j) sum += 10*(i/j);
	        }
	    }
	    
	    if(sum >= n){
	        cout << i << " " << sum << "\n";
	        ans1 = i;
	        break;
	    }
	    
	   // cout << i << " " << sum << "\n";
	}
	
	//Part 2
	for(int i = 0; i < end; i++){
	    for(int j = 1; j <= 50; j++){
	        if(i*j < 1000000){
	            v[i*j] += 11*i;
	        }
	    }
	    if(v[i] > n){
	        cout << i << " " << v[i] << "\n";
	        ans2 = i;
	        break;
	    }
	}
	
	cout << "Part 1: " << ans1 << "\n";
	cout << "Part 2: " << ans2 << "\n";
	
	return 0;
}
