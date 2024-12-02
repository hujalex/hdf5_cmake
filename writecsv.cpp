#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem> // For file existence check (C++17)

using namespace std;

int main() {
    const string filename = "data.csv";

    // Check if the file exists
    bool file_exists = std::filesystem::exists(filename);

    // Open the CSV file in append mode if it exists, or create a new one otherwise
    std::ofstream file(filename, std::ios::app);

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }

    // Write the header only if the file is new
    if (!file_exists) {
        for (int i = 0; i < 10; ++i) {
            file << "header" << ",";
        }
        file << "\n";
    }

    // Define some data
    std::vector<float> v(100, 3.1415926f);

    // Write data to the CSV file
    for (size_t i = 0; i < v.size(); ++i) {
        file << v[i] << ",";
    }
    file << "\n";

    // Close the file
    file.close();

    std::cout << "Data written to CSV file successfully." << std::endl;

    return 0;
}
