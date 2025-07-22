#ifndef CONSTFILEVISITOR_HPP
#define CONSTFILEVISITOR_HPP

class File_Video;
class File_Film;
class File_Episodio;
class File_Serie;
class File_Libro;

class ConstFileVisitor{
    public:
        virtual ~ConstFileVisitor() = default;
        
        virtual void Visit(const File_Video& video) = 0;
        virtual void Visit(const File_Film& film) = 0;
        virtual void Visit(const File_Episodio& episodio) = 0;
        virtual void Visit(const File_Serie& serie) = 0;
        virtual void Visit(const File_Libro& libro) = 0;
};


#endif // CONSTFILEVISITOR_HPP