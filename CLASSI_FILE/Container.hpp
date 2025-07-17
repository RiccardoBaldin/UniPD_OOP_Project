#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
#include <vector>

class FileVisitor;

class File_Generico;

class Biblioteca{
    private:
        std::vector<File_Generico*> archivio;

    public:
        Biblioteca() = default;
        ~Biblioteca();
        std::vector<File_Generico*> getArchivio() const;
        void addFile(File_Generico*); //AGGIUNGE UN FILE IN CODA ALL'ARCHIVIO 
        void killFile(File_Generico*); //ELIMINA UN FILE DALL'ARCHIVIO
        int check(const File_Generico*) const; //CONTROLLA SE UN FILE E' PRESENTE NELL'ARCHIVIO
        std::vector<File_Generico*> finder(const std::string&) const; //RITORNA LISTA DI FILE 
                                                                     //CONTENETNI LE LETTERE PASSATE
                                                                     //QT DOVRA METTERE IN MINUSCOLO


        std::vector<File_Generico*> getLibri() const; //RITORNA LISTA DEI LIBRI
        std::vector<File_Generico*> getFilm() const; //RITORNA LISTA DEI FILM
        std::vector<File_Generico*> getSerie() const; //RITORNA LISTA DELLE SERIE
        
        void sort_nome(); //ORDINA L'ARCHIVIO PER NOME
        void sort_anno(); //ORDINA L'ARCHIVIO PER ANNO
        void sort_genere(); //ORDINA L'ARCHIVIO PER GENERE

        std::vector<File_Generico*> preferiti() const; //RITORNA LISTA DEI FILE PREFERITI

        void print() const; //STAMPA L'ARCHIVIO PER DEBUG

        //metodo per le visite
        void Accept(FileVisitor& visitor);
};

#endif // CONTAINER_HPP