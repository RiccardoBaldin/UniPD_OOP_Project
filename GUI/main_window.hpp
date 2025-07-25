#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>


class LeftSide;
class RightSide;
class Biblioteca;
class File_Generico;
class LineaVerticale;
class QStackedWidget;
class AddFileWidget;
class MostraVisitorHelper; 

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(Biblioteca* biblioteca ,QWidget *parent = nullptr);
private:

    QStackedWidget *stackedWidget;
    QWidget *principale;
    AddFileWidget *aggiuntaLibro;
    AddFileWidget *aggiuntaFilm;
    AddFileWidget *aggiuntaSerie;
    MostraVisitorHelper* aggiuntaEpisodio;

    LeftSide *leftSide;
    RightSide *rightSide;
    Biblioteca *biblioteca;
    LineaVerticale *linea;

private slots:
    void showAddFileWidget(int index);
    void showMainWindow();
    void DettagliIndietro();
    void mostraWindow(File_Generico* file);
    void showAddEpisodioWidget();

signals:
    void bibliotecaChanged();

};


#endif // MAIN_WINDOW_HPP