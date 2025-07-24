#ifndef FILE_SERIE_HPP
#define FILE_SERIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include "File_Generico.hpp"

class File_Episodio;

class File_Serie : public File_Generico{

    private:
        unsigned int numero_stagioni;
        unsigned int numero_episodi;
        std::string casa_di_produzione;
        std::vector<File_Episodio*> episodi;
    
    public:
        File_Serie(const std::string& = "", const std::string& = "", const std::string& = "", unsigned int = 0, unsigned int = 0, unsigned int = 0, const std::string& = "");
        ~File_Serie();

        unsigned int GetNumeroStagioni() const;
        unsigned int GetNumeroEpisodi() const;
        std::string GetCasaDiProduzione() const;
        std::vector<File_Episodio*> GetEpisodi() const;

        void SetCasaDiProduzione(const std::string&);

        void AggiornaNumStagioni();
        void AggiornaNumEpisodi();

        void AggiungiEpisodio(File_Episodio*);
        void RimuoviEpisodio(File_Episodio*);

        bool check(const File_Episodio*) const;
        //metodo per visite
        void Accept(FileVisitor& visitor);
        void Accept(ConstFileVisitor& visitor) const ;
};


#endif // FILE_SERIE_HPP