#ifndef DISPOSIZIONE_LINEE_HPP
#define DISPOSIZIONE_LINEE_HPP

#include <QWidget>

class Biblioteca;
class File_Generico;
class QListWidget;
class QScrollArea;
class QVBoxLayout;

class DisposizioneLinee : public QWidget {
    Q_OBJECT

public:
    explicit DisposizioneLinee(Biblioteca* biblioteca = nullptr, QWidget *parent = nullptr);
    void updateLayout();

private:
    Biblioteca* biblioteca;
    QListWidget* listWidget;

signals:
    void File_Clicked(File_Generico*);
    void lista_modifica(File_Generico*);
    void lista_elimina(File_Generico*);
    void lista_salva(File_Generico*);
};



#endif