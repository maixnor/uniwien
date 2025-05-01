#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    // Open input file
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    
    // Read number of values
    int n;
    infile >> n;
    
    // Read the n integers
    std::vector<int> numbers;
    int num;
    for (int i = 0; i < n; i++) {
        infile >> num;
        numbers.push_back(num);
    }
    infile.close();
    
    // Count frequency of each number
    std::map<int, int> frequency;
    for (int number : numbers) {
        frequency[number]++;
    }
    
    // Create a vector of pairs (number, frequency)
    std::vector<std::pair<int, int>> freq_pairs;
    for (const auto& pair : frequency) {
        freq_pairs.push_back(pair);
    }
    
    // Sort by frequency (descending) and then by value (ascending)
    std::sort(freq_pairs.begin(), freq_pairs.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second; // Descending by frequency
            }
            return a.first < b.first; // Ascending by value when frequencies are equal
        });
    
    // Write to output file
    std::ofstream outfile("output.txt");
    if (!outfile) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }
    
    for (size_t i = 0; i < freq_pairs.size(); i++) {
        for (int j = 0; j < freq_pairs[i].second; j++) {
            outfile << freq_pairs[i].first;
            if (i < freq_pairs.size() - 1 || j < freq_pairs[i].second - 1) {
                outfile << " ";
            }
        }
    }
    
    outfile.close();
    return 0;
}