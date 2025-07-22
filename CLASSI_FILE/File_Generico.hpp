#ifndef FILE_GENERICO_HPP
#define FILE_GENERICO_HPP

#include <iostream>

#include "../visitor/ConstFileVisitor.hpp"
#include "../visitor/FileVisitor.hpp"
#include "../visitor/MostraVisitor.hpp"

class File_Generico{

    protected:
        std::string nome;
        std::string autore;
        std::string genere;
        unsigned int anno;
        bool preferito = false;

    public:
        File_Generico(const std::string& = "", const std::string& = "", const std::string& = "", unsigned int = 0);
        virtual ~File_Generico() = default;

        std::string GetNome() const;
        std::string GetAutore() const;
        std::string GetGenere() const;
        unsigned int GetAnno() const;

        void togglePreferito() {preferito = !preferito;}

        bool IsPreferito() const;

        void SetNome(const std::string&);
        void SetAutore(const std::string&);
        void SetGenere(const std::string&);
        void SetAnno(unsigned int);

        //metodi per accettare le visite
        virtual void Accept(FileVisitor& visitor);
        virtual void Accept(ConstFileVisitor& visitor) const;
        virtual void Accept(MostraVisitor& visitor);
        
};


#endif // FILE_GENERICO_HPP