#include "DeleteJson.hpp"
#include <QFile>

void deleteJson(File_Generico* file){
    std::string path = ":/DataBase/" + file->GetNome() + ".json";
    QFile json(QString::fromStdString(path));
    json.remove();
}