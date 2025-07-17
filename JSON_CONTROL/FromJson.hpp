#ifndef FROMJSON_HPP
#define FROMJSON_HPP

#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

class File_Generico;
class Biblioteca;

File_Generico* GesuSalvatore(QJsonObject&);
Biblioteca* GesuSalvatoreBiblioteca(QJsonObject&);

File_Generico* creaDaJson(const std::string&);
Biblioteca* creaDaJsonBiblioteca(const std::string&);


#endif //FROMJSON_HPP