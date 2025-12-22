#include <bits/stdc++.h>
using namespace std;

// int main() {
// 	// your code goes here
// 	long long val = 20151125, idx = 1, multiply = 252533, modulo = 3355439;
// 	long long limit = 5000000;
// 	unordered_map<long long, int> mp;
	
// 	for(int i = 0; i < limit; i++){
// 	    if(mp.find(val) != mp.end()){
// 	       // if(mp[val] == 1) cout << "Found 3 duplicates: " << idx << ": " << val << "\n";
// 	        mp[val]+= 1;
// 	    }
// 	    else{
// 	        mp[val] = 1;
// 	    }
// 	    if(idx == 4940101) cout << idx << " Answer: " << val << "\n"; 
// 	    val = (val * multiply) % modulo;
	    
// 	    idx++;
// 	}
	
// 	return 0;
// }

// Function for Modular Exponentiation: (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        // If exp is odd, multiply base with result
        if (exp % 2 == 1)
            res = (res * base) % mod;
        
        // exp must be even now
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return res;
}

int main() {
    long long start_code = 20151125;
    long long multiplier = 252533;
    long long modulus = 33554393;
    long long iterations = 18361852; // This is (Position - 1)

    // Calculate multiplier^iterations % modulus
    long long combined_multiplier = power(multiplier, iterations, modulus);

    // Multiply by the start code and take modulo one last time
    long long final_code = (start_code * combined_multiplier) % modulus;

    cout << "The code is: " << final_code << endl;

    return 0;
}
