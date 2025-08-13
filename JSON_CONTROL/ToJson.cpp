#include "ToJson.hpp"
#include <QJsonDocument>
#include <QCoreApplication>

void saveAsJson(File_Generico* file, const std::string& filePath) {
    JsonVisitor visitor;
    file->Accept(visitor);
    QJsonObject jsonVisitor = visitor.GetJson();

    std::ofstream file_1(filePath);
    if (!file_1) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura.");
    }
    file_1 << QJsonDocument(jsonVisitor)
               .toJson(QJsonDocument::Indented)
               .toStdString();
    file_1.close();
}

void saveAsJson(Biblioteca* biblioteca, const std::string& filePath) {
    JsonVisitor visitor;
    biblioteca->Accept(visitor);
    QJsonObject jsonVisitor = visitor.GetJson();

    std::ofstream file_1(filePath);
    if (!file_1) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura.");
    }
    file_1 << QJsonDocument(jsonVisitor)
               .toJson(QJsonDocument::Indented)
               .toStdString();
    file_1.close();
}