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

    std::vector<File_Generico*> lista;

private slots:
    void File_Clicked(File_Generico*);
};



#endif