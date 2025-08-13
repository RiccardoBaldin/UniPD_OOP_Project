#ifndef TOJSON_HPP
#define TOJSON_HPP

#include <fstream>
#include "../visitor/JSonVisitor.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/Container.hpp"

void saveAsJson(File_Generico*, const std::string&);
void saveAsJson(Biblioteca*, const std::string&);

#endif //TOJSON_HPP