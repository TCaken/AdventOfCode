#include <bits/stdc++.h>
using namespace std;



int main() {
	string source, s, from, to, temp;
	int ans = 0, space1, n, m, start;
	unordered_map<string, int> mp;
	
	getline(cin, source);
	while(getline(cin, s)){
	    space1 = s.find(" ");
	    from = s.substr(0, space1);
	    
	    n = from.size();
	    
	    to = s.substr(space1+4);
	    m = to.size();
	    
	   // cout << from << " -> " << to << "\n";
	   // cout << n << " " << m << "\n";
	    
	    start = 0;
	    while((start = source.find(from, start)) != -1){
	       // cout << "Found " << from << " at pos-" << start << "\n";
	        temp = source;
	        temp.replace(start, n, to);
	       // cout << s << " -> " << temp << "\n";
	        mp[temp] = 1;
	        start++;
	    }
	}
	
	cout << "Final Answer: " << mp.size() << "\n";
	return ans;
}
