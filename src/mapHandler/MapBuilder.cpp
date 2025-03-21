/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapBuilder.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:45:41 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/20 18:05:27 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mapHandler/MapBuilder.hpp"
#include <algorithm>

//Constructor and destructor
MapBuilder::MapBuilder(std::string &input): _dicPath("dictionary/dictionary24.fdf"){
	feedDictionary();

	if (checkInputType(input))
		buildMapFromPath(input);
	else
		buildMapFromString(input);
}

MapBuilder::~MapBuilder(){}

//Getters
std::vector<std::string> &MapBuilder::getMap(){
	return (this->_map);
}

//Methods
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

void MapBuilder::buildMapFromString(std::string &str){
    // Char maps are 12x28
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

//Helpers
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

//Debuggers
void MapBuilder::mapPrinter(){
	for (std::vector<std::string>::iterator it = this->_map.begin(); it != this->_map.end(); it++)
		std::cout << *it <<  std::endl;
}

void MapBuilder::dictionaryPrinter(){
	std::cout << "dictionary size is:" << _mapDictionary.size() << std::endl;
	/*for (std::map<int, std::vector<std::string> >::iterator it = this->_mapDictionary.begin(); it != this->_mapDictionary.end(); it++) {

	}*/
}


//Exception messages
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