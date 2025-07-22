#ifndef MOSTRAVISITOR_HPP
#define MOSTRAVISITOR_HPP

#include "FileVisitor.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>

class File_Generico;
class File_Video;
class File_Film;
class File_Episodio;
class File_Serie;
class File_Libro;

class MostraVisitor : public FileVisitor {
private:
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* sopra = new QHBoxLayout();
    QHBoxLayout* sotto = new QHBoxLayout();
    QVBoxLayout* sopraDx = new QVBoxLayout();
    QVBoxLayout* sottoSx = new QVBoxLayout();
    QVBoxLayout* sottoDx = new QVBoxLayout();


    //attributi generali
    QIcon *icona;
    QLabel *widgetIcona;
    QLabel *nome = new QLabel();
    QLabel *autore = new QLabel();
    QLabel *genere = new QLabel();
    QLabel *anno = new QLabel();

    //attributi libro
    QLabel *pagine;
    QLabel *editore;

    //attributi video
    QLabel *durata;
    QLabel *regista;
    QLabel *casa_di_produzione;

    //attributi film
    QIcon *oscar;

    //attributi serie
    QLabel *numero_stagioni;
    QLabel *numero_episodi;
    QLabel *casa_di_produzione_serie;

    //attributi episodio
    QLabel *serie;
    QLabel *numero_stagione;
    QLabel *numero_episodio;


public:

    MostraVisitor() = default;
    ~MostraVisitor() = default;

    void Visit(File_Generico& file) override;
    void Visit(File_Video& video) override;
    void Visit(File_Film& film) override;
    void Visit(File_Episodio& episodio) override;
    void Visit(File_Serie& serie) override;
    void Visit(File_Libro& libro) override;

    QVBoxLayout* GetLayout();
};

#endif // MOSTRAVISITOR_HPP