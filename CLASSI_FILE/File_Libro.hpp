#ifndef FILE_LIBRO_HPP
#define FILE_LIBRO_HPP

#include <iostream>
#include "File_Generico.hpp"

class File_Libro : public File_Generico{

    private:
        unsigned int pagine;
        std::string editore;

    public:
        File_Libro(const std::string& = "", const std::string& = "",
                   const std::string& = "", unsigned int = 0,
                   unsigned int = 0, const std::string& = "");
                   
        unsigned int GetPagine() const;
        std::string GetEditore() const;

        void SetPagine(unsigned int);
        void SetEditore(const std::string&);

        //metodo per visite
        virtual void Accept(FileVisitor& visitor);
        virtual void Accept(ConstFileVisitor& visitor) const;
};


#endif // FILE_LIBRO_HPP