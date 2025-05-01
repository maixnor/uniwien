#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

int main() {
    // Open input files
    std::ifstream fileA("A.txt");
    std::ifstream fileB("B.txt");
    std::ofstream output("output.txt");

    if (!fileA.is_open() || !fileB.is_open() || !output.is_open()) {
        std::cerr << "Error opening files" << std::endl;
        return 1;
    }

    // Read the values from A.txt
    int nA;
    fileA >> nA;
    std::vector<int> valuesA(nA);
    for (int i = 0; i < nA; i++) {
        fileA >> valuesA[i];
    }

    // Read the values from B.txt
    int nB;
    fileB >> nB;
    std::vector<int> valuesB(nB);
    for (int i = 0; i < nB; i++) {
        fileB >> valuesB[i];
    }

    // Map to store the first occurrence position of each value in B
    std::map<int, int> positionMap;
    
    // Set to keep track of which values are in B
    std::set<int> valuesInB;
    
    // Fill the position map and set
    for (int i = 0; i < nB; i++) {
        if (positionMap.find(valuesB[i]) == positionMap.end()) {
            positionMap[valuesB[i]] = i;
        }
        valuesInB.insert(valuesB[i]);
    }

    // Separate values from A into those that are in B and those that aren't
    std::vector<std::pair<int, int>> inB; // pairs of (value, position in B)
    std::vector<int> notInB;

    for (int val : valuesA) {
        if (valuesInB.find(val) != valuesInB.end()) {
            inB.push_back({val, positionMap[val]});
        } else {
            notInB.push_back(val);
        }
    }

    // Sort the values that are in B by their position in B
    std::sort(inB.begin(), inB.end(), 
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });
    
    // Sort the values that are not in B by their value
    std::sort(notInB.begin(), notInB.end());

    // Write to output file
    bool first = true;
    
    // First write values that are in B
    for (const auto& pair : inB) {
        if (!first) output << " ";
        output << pair.first;
        first = false;
    }
    
    // Then write values that are not in B
    for (int val : notInB) {
        if (!first) output << " ";
        output << val;
        first = false;
    }

    // Close files
    fileA.close();
    fileB.close();
    output.close();

    return 0;
}