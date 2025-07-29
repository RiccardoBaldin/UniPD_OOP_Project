#ifndef RIGA_LISTA_HPP
#define RIGA_LISTA_HPP

#include <QWidget>

class File_Generico;

class Riga_Lista : public QWidget {
    Q_OBJECT

public:
    explicit Riga_Lista(File_Generico* file, QWidget *parent = nullptr);

private:
    File_Generico* file;

signals:
    void RigaClicked(File_Generico*);
    void RigaModifica(File_Generico*);
    void RigaElimina(File_Generico*);
    void RigaSalva(File_Generico*);


};

#endif //RIGA_LISTA_HPP