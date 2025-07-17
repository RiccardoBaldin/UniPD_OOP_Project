#include "ToJson.hpp"
#include <QJsonDocument>
#include <QCoreApplication>

void saveAsJson(File_Generico* file) {
    JsonVisitor visitor;
    file->Accept(visitor);
    QJsonObject jsonVISITANTE = visitor.GetJson();
    std::ofstream file_1("DataBase/" + file->GetNome() + ".json");
    file_1 << QJsonDocument(jsonVISITANTE).toJson(QJsonDocument::Indented).toStdString();
    file_1.close();
}

void saveAsJson(Biblioteca* biblioteca) {
    JsonVisitor visitor;
    biblioteca->Accept(visitor);
    QJsonObject jsonVISITANTE = visitor.GetJson();
    std::ofstream file_1("DataBase/Biblioteca.json");
    file_1 << QJsonDocument(jsonVISITANTE).toJson(QJsonDocument::Indented).toStdString();
    file_1.close();
    std::cout << "Salvato" << std::endl;
}