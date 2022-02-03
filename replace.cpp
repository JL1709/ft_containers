/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:43:50 by jludt             #+#    #+#             */
/*   Updated: 2021/12/09 14:10:45 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main (int argc, char *argv[])
{
	std::ifstream		inFile;
	std::ofstream		outFile;
	std::string			contentOfInfile;
	std::stringstream	strStream;
	std::size_t			found;
	std::string			nameOfOutfile;

	if (argc != 4)
	{
		std::cout << "Program needs 3 arguments" << std::endl;
		std::cout << "argument 1: name of input file" << std::endl;
		std::cout << "argument 2: string1 that will be replaced by..." << std::endl;
		std::cout << "argument 3: ...string2 in input file" << std::endl;
		return (1);
	}
	if (!argv[1] || !argv[2] || !argv[3])
	{
		std::cout << "arguments shouldn't be empty" << std::endl;
		return (1);
	}
	inFile.open(argv[1]);									//open input file
	if (inFile.good() == false)
	{
		std::cout << "Failed to open infile" << std::endl;
		return(1);
	}
	strStream << inFile.rdbuf();							//read the file
	contentOfInfile = strStream.str();						//contentOfInfile holds now content of infile
	found = contentOfInfile.find(argv[2]);
	while (found != std::string::npos)						//return value if no find = std::string::npos = -1
	{
		contentOfInfile.erase(found, strlen(argv[2]));
		contentOfInfile.insert(found, argv[3]);
		found = contentOfInfile.find(argv[2]);
	}
	nameOfOutfile = argv[1];
	nameOfOutfile.append(".replace");
	outFile.open(nameOfOutfile);
	if (outFile.good() == false)
	{
		std::cout << "Error with outfile" << std::endl;
		return(1);
	}
	outFile << contentOfInfile;
	inFile.close();
	outFile.close();
	return (0);
}