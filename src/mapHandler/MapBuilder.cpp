/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapBuilder.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:45:41 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/11 15:15:46 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mapHandler/MapBuilder.hpp"
#include <algorithm>

//Constructor and destructor
MapBuilder::MapBuilder(std::string &input): _dicPath("dictionary/dictionary.fdf"){
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
void MapBuilder::feedDictionary(){
	std::ifstream dicFile(this->_dicPath.c_str());
	
	if (dicFile.fail() || dicFile.bad()){
		throw (BadDicFileException());
	}

	for (int i = 0; i < 36; i++){
		std::string line;
		std::vector<std::string> tmp;
		std::getline(dicFile, line);
		if (line.at(0) == '~'){
			std::getline(dicFile,line);
		}
		for (int j = 0; j < 12; j++){
			tmp.push_back(line);
			std::getline(dicFile, line);
		}
		this->_mapDictionary[i] = tmp;
	}
	dicFile.close();
}

void MapBuilder::buildMapFromString(std::string &str){
	//Char maps are 12x28
	if (str.size() > 10) {throw(StringTooLongException());}

	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	for (int i = 0; i < 12; i++){
		std::string row;
		for (size_t j = 0; j < str.length(); j++){
			int idx = str.at(j) - 48;
			std::vector<std::string> tmp;
			if (idx > 9)
				tmp = this->_mapDictionary[idx - 7];
			else
				tmp = this->_mapDictionary[idx];
			row += tmp.at(i);
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