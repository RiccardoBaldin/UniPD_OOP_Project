#ifndef GRIGLIAVISITOR_HPP
#define GRIGLIAVISITOR_HPP

#include "FileVisitor.hpp"

class QLabel;
class QVBoxLayout;
class QIcon;

class GrigliaVisitor : public FileVisitor {
private:
    QVBoxLayout* layout;
    QIcon* icona;
    QLabel* label;


public:
    void Visit(File_Generico& file) override;
    void Visit(File_Video& video) override;
    void Visit(File_Film& film) override;
    void Visit(File_Episodio& episodio) override;
    void Visit(File_Serie& serie) override;
    void Visit(File_Libro& libro) override;
    void Visit(Biblioteca& ) override {;};

    QVBoxLayout* GetLayout() const;
};

#endif // GRIGLIAVISITOR_HPP