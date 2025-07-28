#include<bits/stdc++.h>
#include "json.hpp" 

using json = json;
using namespace std;


long long convertBaseToDecimal(const string& value, int base) {
    long long result = 0;
    for (char digit : value) {
        int digitValue = isdigit(digit) ? digit - '0' : tolower(digit) - 'a' + 10;
        result = result * base + digitValue;
    }
    return result;
}


long long lagrangeInterpolation(const vector<pair<int, long long>>& points, int xTarget, long long primeMod) {
    long long result = 0;
    for (int i = 0; i < points.size(); i++) {
        long long term = points[i].second;
        for (int j = 0; j < points.size(); j++) {
            if (i != j) {
                long long numerator = (xTarget - points[j].first + primeMod) % primeMod;
                long long denominator = (points[i].first - points[j].first + primeMod) % primeMod;

               
                long long inv = 1;
                long long exponent = primeMod - 2;
                long long base = denominator;
                while (exponent) {
                    if (exponent % 2)
                        inv = (inv * base) % primeMod;
                    base = (base * base) % primeMod;
                    exponent /= 2;
                }
                term = (term * numerator % primeMod) * inv % primeMod;
            }
        }
        result = (result + term) % primeMod;
    }
    return result;
}

int main() {
    ifstream inputFile("input.json");
    if (!inputFile) {
        cerr << "Error: input.json not found" << endl;
        return 1;
    }

    json inputData;
    inputFile >> inputData;

    int totalShares = inputData["keys"]["n"];
    int threshold = inputData["keys"]["k"];

   
    long long primeMod = 1000000007;
    vector<pair<int, long long>> shares;

    for (int i = 1; i <= totalShares; i++) {
        string baseStr = inputData[to_string(i)]["base"];
        string valueStr = inputData[to_string(i)]["value"];

        int base = stoi(baseStr);
        long long decimalValue = convertBaseToDecimal(valueStr, base);

        shares.push_back({i, decimalValue});
    }

    
    vector<pair<int, long long>> usedShares(shares.begin(), shares.begin() + threshold);
    long long secret = lagrangeInterpolation(usedShares, 0, primeMod);

    cout << "Reconstructed Secret: " << secret << endl;

    return 0;
}
