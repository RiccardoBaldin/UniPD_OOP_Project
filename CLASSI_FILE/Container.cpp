#include "Container.hpp"
#include "File_Generico.hpp"
#include "File_Libro.hpp"
#include "File_Film.hpp"
#include "File_Serie.hpp"
#include "visitor/FileVisitor.hpp"
#include <algorithm>

Biblioteca::~Biblioteca(){
    for(auto x : archivio) delete x;
}

std::vector<File_Generico*> Biblioteca::getArchivio() const{
    return archivio;
}

void Biblioteca::addFile(File_Generico* file){
    archivio.push_back(file);
}


void Biblioteca::killFile(File_Generico* file){
    for(auto it = archivio.begin(); it != archivio.end(); ++it){
        if(*it == file){
            archivio.erase(it);
            return;
        }
    }
}

void Biblioteca::sort_nome() {
    if(archivio.empty()) return;
    std::sort(archivio.begin(), archivio.end(), [](File_Generico* a, File_Generico* b) {
        return a->GetNome() < b->GetNome();
    });
}

void Biblioteca::sort_anno() {
    if(archivio.empty()) return;
    std::sort(archivio.begin(), archivio.end(), [](File_Generico* a, File_Generico* b) {
        return a->GetAnno() < b->GetAnno();
    });
}

void Biblioteca::sort_genere() {
    if(archivio.empty()) return;
    std::sort(archivio.begin(), archivio.end(), [](File_Generico* a, File_Generico* b) {
        return a->GetGenere() < b->GetGenere();
    });
}

std::vector<File_Generico*> Biblioteca::finder(const std::string& s) const{
    std::vector<File_Generico*> trovati;
    for(auto it : archivio){
        if(it->GetNome().find(s) != std::string::npos){
            trovati.push_back(it);
        }
    }
    return trovati;
}

std::vector<File_Generico*> Biblioteca::getLibri() const{
    std::vector<File_Generico*> libri;
    for(auto it : archivio){
        File_Libro* l = dynamic_cast<File_Libro*>(it);
        if(l){
            libri.push_back(it);
        }
    }
    return libri;
}

std::vector<File_Generico*> Biblioteca::getFilm() const{
    std::vector<File_Generico*> film;
    for(auto it : archivio){
        File_Film* f = dynamic_cast<File_Film*>(it);
        if(f){
            film.push_back(it);
        }
    }
    return film;
}

std::vector<File_Generico*> Biblioteca::getSerie() const{
    std::vector<File_Generico*> serie;
    for(auto it : archivio){
        File_Serie* s = dynamic_cast<File_Serie*>(it);
        if(s){
            serie.push_back(it);
        }
    }
    return serie;
}

std::vector<File_Generico*> Biblioteca::preferiti() const{
    std::vector<File_Generico*> preferiti;
    for(auto it : archivio){
        if(it->IsPreferito()){
            preferiti.push_back(it);
        }
    }
    return preferiti;
}

bool Biblioteca::check(const File_Generico* a) const {
    for(auto cit : archivio){
        if(typeid(*cit)==typeid(*a) &&
           cit->GetNome() == a->GetNome() && 
           cit->GetAnno() == a->GetAnno() && 
           cit->GetAutore() == a->GetAutore()) return false;
    } 
    return true;
}; 

void Biblioteca::print() const{
    for(auto it : archivio){
        std::cout << it->GetNome() << std::endl;
    }
}

void Biblioteca::Accept(FileVisitor& visitor){
    //visitor.Visit(*this);
}

void Biblioteca::Accept(ConstFileVisitor& visitor) const {
    //visitor.Visit(*this);
}