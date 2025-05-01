#include <iostream>
#include <initializer_list>
#include <cassert>
#include "ADS_set_speziell.h" // Ensure this includes your ADS_set implementation

void test_iterator_modes() {
    // Test cases from the document
    struct TestCase {
        std::initializer_list<int> input;
        std::initializer_list<int> expected_normal;
        std::initializer_list<int> expected_spezial;
    };

    TestCase test_cases_first_last[] = {
        {{}, {}, {}}, // Edge case: empty
        {{1}, {1}, {1}}, // Single element
        {{1, 4}, {1, 4}, {4, 1}}, // Two elements
        {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {2, 1, 3, 4, 5}}, // Test with ascending and descending logic
        {{1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}, {2, 1, 3, 4, 5, 6, 7, 8}} // Larger case
    };

    size_t iters = 0;
    
    for (const auto& test : test_cases_first_last) {
        ADS_set<int> adsSet(test.input);
        
        // Normal mode test
        std::cout << "Testing Normal Mode..." << std::endl;
        auto normal_iter = adsSet.begin();
        std::cout << "Expected: ";
        for (int val : test.expected_normal) {
            std::cout << val << " ";
        }
        std::cout << std::endl << "Actual: ";
        for (; normal_iter != adsSet.end(); ++normal_iter) {
            std::cout << *normal_iter << " ";
        }
        std::cout << std::endl << std::endl;

        // Special mode test
        std::cout << "Testing Special Mode..." << std::endl;
        auto special_iter = adsSet.y();
        std::cout << "Expected: ";
        for (int val : test.expected_spezial) {
            std::cout << val << " ";
        }
        std::cout << std::endl << "Actual: ";
        for (; special_iter != adsSet.end(); ++special_iter) {
            iters++;
            if (iters > 50) exit(1);
            std::cout << *special_iter << " ";
        }
        std::cout << std::endl << std::endl;
        
        // Error handling: Check for iterator validity
        if (adsSet.empty() && (normal_iter != adsSet.end() || special_iter != adsSet.end())) {
            std::cerr << "Error: Iterators returned non-end values for empty set!" << std::endl;
        }
        else if (adsSet.end() != normal_iter || adsSet.end() != special_iter) {
            std::cerr << "Error: Iterators are not the same" << std::endl;
            exit(-1);
        } else {
            std::cout << "Iterators are valid." << std::endl << std::endl;
        }
    }

    // Further error handling scenarios can be added as needed
}

int main() {
    try {
        test_iterator_modes();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception occurred!" << std::endl;
    }

    return 0;
}