#include "FromJson.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Video.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/Container.hpp"

File_Generico* GesuSalvatore(QJsonObject& obj){
    std::string tipo = obj["tipo"].toString().toStdString();
    std::string nome = obj["nome"].toString().toStdString();
    std::string autore = obj["autore"].toString().toStdString();
    std::string genere = obj["genere"].toString().toStdString();
    unsigned int anno = obj["anno"].toInt();
    if(tipo == "episodio"){
        unsigned int durata = obj["durata"].toInt();
        std::string casa_di_produzione = obj["casa_di_produzione"].toString().toStdString();
        std::string regista = obj["regista"].toString().toStdString();
        unsigned int numero_stagione = obj["numero_stagione"].toInt();
        unsigned int numero_episodio = obj["numero_episodio"].toInt();
        std::string serieTV = obj["serie"].toString().toStdString();
        return new File_Episodio(nome, autore, genere, anno, durata, casa_di_produzione, regista, numero_stagione, numero_episodio, serieTV);
    }
    if(tipo == "film"){
        unsigned int durata = obj["durata"].toInt();
        std::string casa_di_produzione = obj["casa_di_produzione"].toString().toStdString();
        std::string regista = obj["regista"].toString().toStdString();
        bool oscar = obj["oscar"].toBool();
        return new File_Film(nome, autore, genere, anno, durata, casa_di_produzione, regista, oscar);
    }
    if(tipo == "libro"){
        unsigned int pagine = obj["pagine"].toInt();
        std::string editore = obj["editore"].toString().toStdString();
        return new File_Libro(nome, autore, genere, anno, pagine, editore);
    }
    if(tipo == "serie"){
        unsigned int numero_stagioni = obj["numero_stagioni"].toInt();
        unsigned int numero_episodi = obj["numero_episodi"].toInt();
        return new File_Serie(nome, autore, genere, anno, numero_stagioni, numero_episodi);
    }
    return nullptr;
}

Biblioteca* GesuSalvatoreBiblioteca(QJsonObject& obj){
    Biblioteca* biblioteca = new Biblioteca();
    QJsonArray archivio = obj["library"].toArray();
    for(auto a : archivio){
        QJsonObject file = a.toObject();
        biblioteca->addFile(GesuSalvatore(file));
    }
    return biblioteca;
}

Biblioteca* creaDaJsonBiblioteca(const std::string& path){
    QFile file(QString::fromStdString(path));
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    return GesuSalvatoreBiblioteca(obj);
}

File_Generico* creaDaJson(const std::string& path){
    QFile file(QString::fromStdString(path));
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    return GesuSalvatore(obj);

}