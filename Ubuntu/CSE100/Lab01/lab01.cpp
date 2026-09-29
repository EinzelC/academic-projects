#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Insertion sort function
void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " inputfile [outputfile]\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    std::vector<int> numbers;
    int num;
    while (infile >> num) {
        numbers.push_back(num);
    }
    infile.close();

    insertionSort(numbers);

    if (argc >= 3) {
        std::ofstream outfile(argv[2]);
        if (!outfile) {
            std::cerr << "Error opening output file.\n";
            return 1;
        }
        for (int n : numbers) {
            outfile << n << "\n";
        }
        outfile.close();
    } else {
        for (int n : numbers) {
            std::cout << n << "\n";
        }
    }

    return 0;
}