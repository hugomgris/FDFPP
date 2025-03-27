#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main(int argc, char* argv[]) {
    // Check if correct number of arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    // Input and output file names from command line arguments
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    // Open input file
    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cerr << "Error: Could not open input file " << inputFileName << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cerr << "Error: Could not open output file " << outputFileName << std::endl;
        return 1;
    }

    // Regex pattern to match 0xNNNNNN hex values
    std::regex hexPattern("0x[0-9A-Fa-f]{6}");
    
    // Regex pattern to match all commas
    std::regex commaPattern(",");

    // String to store each line
    std::string line;

    // Process each line of the input file
    while (std::getline(inputFile, line)) {
        // Remove all hex values from the line
        std::string processedLine = std::regex_replace(line, hexPattern, "");

        // Remove all commas
        processedLine = std::regex_replace(processedLine, commaPattern, "");

        // Remove multiple consecutive spaces that might be left after removal
        std::regex spacePattern("\\s+");
        processedLine = std::regex_replace(processedLine, spacePattern, " ");

        // Trim leading and trailing spaces
        processedLine.erase(0, processedLine.find_first_not_of(" "));
        processedLine.erase(processedLine.find_last_not_of(" ") + 1);

        // Write processed line to output file if not empty
        if (!processedLine.empty()) {
            outputFile << processedLine << std::endl;
        }
    }

    // Close files
    inputFile.close();
    outputFile.close();

    std::cout << "Hex values and commas removed. Output written to " << outputFileName << std::endl;

    return 0;
}