#include <iostream>

int findOccurrences(const char* str1, const char* str2, const char** firstOccurrence) {
    // Initialize the count of occurrences
    int occurrences = 0;

    // Iterate through the first string
    while (*str1) {
        const char* p1 = str1;
        const char* p2 = str2;

        // Check if the current position in the first string matches the second string
        while (*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }

        // If the second string is fully matched, update the count and set the first occurrence pointer
        if (!(*p2)) {
            occurrences++;
            if (occurrences == 1 && firstOccurrence) {
                *firstOccurrence = str1;
            }
        }

        // Move to the next character in the first string
        str1++;
    }

    // If no occurrences were found, set the first occurrence pointer to nullptr
    if (occurrences == 0 && firstOccurrence) {
        *firstOccurrence = nullptr;
    }

    return occurrences;
}

int main() {
    const char* str1 = "hellohellohello";
    const char* str2 = "lo";

    const char* firstOccurrence = nullptr;
    int occurrences = findOccurrences(str1, str2, &firstOccurrence);

    if (occurrences > 0) {
        std::cout << "Occurrences: " << occurrences << std::endl;
        std::cout << "First occurrence at index: " << (firstOccurrence - str1) << std::endl;
    } else {
        std::cout << "No occurrences found." << std::endl;
    }

    return 0;
}

