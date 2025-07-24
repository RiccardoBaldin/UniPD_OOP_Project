#include "File_Serie.hpp"
#include "File_Episodio.hpp"
#include "visitor/FileVisitor.hpp"

File_Serie::File_Serie(const std::string& nome, const std::string& autore, const std::string& genere, unsigned int anno, unsigned int numero_stagioni, unsigned int numero_episodi, const std::string& casa_di_produzione) : File_Generico(nome, autore, genere, anno){
    this -> numero_stagioni = numero_stagioni;
    this -> numero_episodi = numero_episodi;
    this -> casa_di_produzione = casa_di_produzione;
    episodi = std::vector<File_Episodio*>();
}

File_Serie::~File_Serie(){
}


//GETTERS

unsigned int File_Serie::GetNumeroStagioni() const {
    return numero_stagioni;
}  

unsigned int File_Serie::GetNumeroEpisodi() const {
    return numero_episodi;
}

std::string File_Serie::GetCasaDiProduzione() const {
    return casa_di_produzione;
}

std::vector<File_Episodio*> File_Serie::GetEpisodi() const {
    return episodi;
}

//SETTERS

void File_Serie::SetCasaDiProduzione(const std::string& casa_di_produzione){
    this->casa_di_produzione = casa_di_produzione;
}

void File_Serie::AggiornaNumStagioni(){
    this->numero_stagioni = episodi.back()->GetNumeroStagione();
}

void File_Serie::AggiornaNumEpisodi(){
    this->numero_episodi = episodi.size();
    
}


//METODI AGGIUNTIVI

void File_Serie::AggiungiEpisodio(File_Episodio* episodio){
    if (episodi.empty()) {
        episodio->SetSerieTV(this);
        episodio->SetAutore(this);
        episodio->SetCasaDiProduzione(this);
        episodio->SetGenere(this);
        episodi.push_back(episodio);
        AggiornaNumEpisodi();
        AggiornaNumStagioni();
        return;
    }

    auto it = episodi.begin();
    while (it != episodi.end()) {
        if (episodio->GetNumeroStagione() < (*it)->GetNumeroStagione()) {
            break;
        }
        else if (episodio->GetNumeroStagione() == (*it)->GetNumeroStagione()) {
            if (episodio->GetNumeroEpisodio() < (*it)->GetNumeroEpisodio()) {
                break;
            }
        }
        ++it;
    }

    if (it != episodi.end() && 
        episodio->GetNumeroStagione() == (*it)->GetNumeroStagione() && 
        episodio->GetNumeroEpisodio() == (*it)->GetNumeroEpisodio()) {
        return;
    }

    episodio->SetSerieTV(this);
    episodio->SetAutore(this);
    episodio->SetCasaDiProduzione(this);
    episodio->SetGenere(this);
    episodi.insert(it, episodio);

    AggiornaNumEpisodi();
    AggiornaNumStagioni();
}

void File_Serie::RimuoviEpisodio(File_Episodio* episodio){
    for(auto it = episodi.begin(); it != episodi.end(); it++){
        if(*it == episodio){
            episodi.erase(it);
            break;
        }
    }
}

bool File_Serie::check(const File_Episodio* a) const {
    for(auto cit : episodi){
        if(cit->GetNome() == a->GetNome() && 
           cit->GetAnno() == a->GetAnno() && 
           cit->GetAutore() == a->GetAutore()) return false;
    } 
    return true;
}; 


//METODO PER VISITE

void File_Serie::Accept(FileVisitor& visitor){
    visitor.Visit(*this);
}

void File_Serie::Accept(ConstFileVisitor& visitor) const {
    visitor.Visit(*this);
}