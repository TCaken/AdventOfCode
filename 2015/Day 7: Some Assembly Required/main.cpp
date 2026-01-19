#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cctype>
#include <algorithm>
#include <cstdint>

using namespace std;

// Stores the raw instructions: key = wire (e.g., "d"), value = rule (e.g., "x AND y")
map<string, string> circuit;

// Stores calculated results to avoid re-work (Memoization)
map<string, uint16_t> memo;

// Helper: Check if a string is a pure number
bool is_number(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

// Recursive function to solve for a specific wire
uint16_t evaluate(string wire) {
    // 1. BASE CASE: If it's just a number (e.g., "123"), return it.
    if (is_number(wire)) return (uint16_t)stoi(wire);

    // 2. CACHE CHECK: If we already solved this wire, return the saved answer.
    if (memo.count(wire)) return memo[wire];

    // 3. PARSE & RECURSE: Get the rule and evaluate dependencies
    string rule = circuit[wire];
    stringstream ss(rule);
    string part1, op, part2;
    vector<string> tokens;
    string temp;
    
    // Split rule into tokens
    while(ss >> temp) tokens.push_back(temp);

    uint16_t result = 0;

    if (tokens.size() == 1) {
        // Form: "123 -> x" or "y -> x" (Assignment)
        result = evaluate(tokens[0]);
    } 
    else if (tokens.size() == 2) {
        // Form: "NOT y -> x"
        // Note: The '~' operator in C++ promotes to int, so we trust uint16_t cast to truncate it
        result = ~evaluate(tokens[1]);
    } 
    else if (tokens.size() == 3) {
        // Form: "x AND y -> z", "x LSHIFT 2 -> z", etc.
        string lhs_str = tokens[0];
        string oper = tokens[1];
        string rhs_str = tokens[2];

        // Recurse for operands
        uint16_t lhs = evaluate(lhs_str);
        uint16_t rhs = evaluate(rhs_str);

        if (oper == "AND") result = lhs & rhs;
        else if (oper == "OR") result = lhs | rhs;
        else if (oper == "LSHIFT") result = lhs << rhs;
        else if (oper == "RSHIFT") result = lhs >> rhs;
    }

    // 4. SAVE RESULT: Store in cache before returning
    memo[wire] = result;
    return result;
}

int main() {
    // --- INPUT PARSING ---
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        
        // Parse "OPERATIONS -> WIRE"
        size_t arrow_pos = line.find(" -> ");
        string expression = line.substr(0, arrow_pos);
        string target_wire = line.substr(arrow_pos + 4);
        
        circuit[target_wire] = expression;
    }

    // --- SOLVE PART 1 ---
    // The puzzle usually asks for the signal on wire "a"
    if (circuit.count("a")) {
        uint16_t result_a = evaluate("a");
        cout << "Signal on wire 'a': " << result_a << endl;

        // --- SOLVE PART 2 (Standard AoC Variation) ---
        // Part 2 usually asks: Take the signal from 'a', override wire 'b' with it, 
        // reset the circuit, and find 'a' again.
        
        cout << "--- Part 2 Check ---" << endl;
        // 1. Reset the cache (wires have new values now)
        memo.clear();
        
        // 2. Override wire 'b' with the signal we just found
        circuit["b"] = to_string(result_a);
        
        // 3. Solve for 'a' again
        uint16_t result_b = evaluate("a");
        cout << "New signal on wire 'a' (after overriding 'b'): " << result_b << endl;
    } else {
        // Debugging for the example case provided in the prompt
        cout << "Signal on d: " << evaluate("d") << endl;
        cout << "Signal on e: " << evaluate("e") << endl;
        cout << "Signal on f: " << evaluate("f") << endl;
        cout << "Signal on g: " << evaluate("g") << endl;
        cout << "Signal on h: " << evaluate("h") << endl;
        cout << "Signal on i: " << evaluate("i") << endl;
    }

    return 0;
}