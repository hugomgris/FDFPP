#/**
# * @file MapBuilder.cpp
# * @brief Implements the MapBuilder class for constructing map data from files or strings.
# *
# * The MapBuilder class loads map data from a file or string, parses dictionary files for character maps,
# * and provides methods for building, printing, and validating map input. Includes custom exceptions for error handling.
# */

#include "../../includes/mapHandler/MapBuilder.hpp"
#include <algorithm>

/**
 * @brief Constructs a MapBuilder object and loads the dictionary file.
 *
 * Determines input type and builds the map from file or string.
 * @param input Input string or file path.
 */
MapBuilder::MapBuilder(std::string &input): _dicPath("dictionary/dictionary24.fdf"){
    feedDictionary();

    if (checkInputType(input))
        buildMapFromPath(input);
    else
        buildMapFromString(input);
}

/**
 * @brief Destructor for MapBuilder. Cleans up resources if needed.
 */
MapBuilder::~MapBuilder(){}

std::vector<std::string> &MapBuilder::getMap(){
    return (this->_map);
}

/**
 * @brief Loads the character dictionary from the dictionary file.
 * @throws BadDicFileException if the file cannot be read.
 */
void MapBuilder::feedDictionary() {
    std::ifstream dicFile(this->_dicPath.c_str());
    
    if (dicFile.fail() || dicFile.bad()) {
        throw (BadDicFileException());
    }

    std::string line;
    while (std::getline(dicFile, line)) {
        if (line.size() >= 2 && line[0] == '~') {
            char c = line[1];
            
            std::vector<std::string> charLines;
            for (int j = 0; j < 24; j++) {
                if (!std::getline(dicFile, line)) {
                    throw BadDicFileException();
                }
                charLines.push_back(line);
            }
            
            this->_mapDictionary[static_cast<int>(c)] = charLines;
        }
    }
    dicFile.close();
}

/**
 * @brief Builds the map from an input string using the character dictionary.
 * @param str Input string to convert to map.
 * @throws StringTooLongException if the string is too long.
 */
void MapBuilder::buildMapFromString(std::string &str){
    if (str.size() > 100) {throw(StringTooLongException());}

    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    for (int i = 0; i < 24; i++) {
        std::string row;
        for (size_t j = 0; j < str.length(); j++) {
            char c = str.at(j);
            
            int charIdx = static_cast<int>(c);
            
            if (this->_mapDictionary.find(charIdx) != this->_mapDictionary.end() && 
                !this->_mapDictionary[charIdx].empty()) {
                row += this->_mapDictionary[charIdx].at(i);
            } else {
                row += "          ";
            }
            row += "  ";
        }
        this->_map.push_back(row);
    }
}

/**
 * @brief Builds the map from a file at the given path.
 * @param str Path to the map file.
 * @throws BadMapFileException if the file cannot be read.
 */
void MapBuilder::buildMapFromPath(std::string &str){
    std::ifstream mapFile(str.c_str());

    if (mapFile.fail() || mapFile.bad()){
        throw (BadMapFileException());
    }


    std::string line;
    while (std::getline(mapFile, line)){
        this->_map.push_back(line);
    }
    mapFile.close();
}

/**
 * @brief Checks if the input string is a valid map file path.
 * @param input Input string to check.
 * @return True if input is a valid map file path, false otherwise.
 * @throws BadExtensionException if the file extension is invalid.
 */
bool MapBuilder::checkInputType(std::string &input){
    if (input.length() < 8) return false;
    
    if (!input.empty()){
        size_t point = input.find('.');
        if (point == std::string::npos)
            return (false);
    }

    std::string prefix = "maps/";
    std::string suffix = ".fdf";
    std::string checkA = input.substr(0, prefix.length());
    std::string checkB = input.substr(input.length() - suffix.length());
    if (checkB != suffix)
        throw (BadExtensionException());
    return (checkA == prefix && checkB == suffix);
}

/**
 * @brief Prints the map data to standard output.
 */
void MapBuilder::mapPrinter(){
    for (std::vector<std::string>::iterator it = this->_map.begin(); it != this->_map.end(); it++)
        std::cout << *it <<  std::endl;
}

/**
 * @brief Prints the size of the loaded dictionary to standard output.
 */
void MapBuilder::dictionaryPrinter(){
    std::cout << "dictionary size is:" << _mapDictionary.size() << std::endl;
}

const char *MapBuilder::BadDicFileException::what() const throw(){
    return ("Bad dictionary file (check existance and premissions)");
}

const char *MapBuilder::StringTooLongException::what() const throw(){
    return ("String too long! (for now, try with a size 10 atmost)");
}

const char *MapBuilder::BadMapFileException::what() const throw(){
    return ("Bad map file! (check existance and premissions)");
}

const char *MapBuilder::BadExtensionException::what() const throw(){
    return ("Bad map file extension! (maps have to be .fdf)");
}