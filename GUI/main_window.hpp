#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>


class LeftSide;
class RightSide;
class Biblioteca;
class File_Generico;
class File_Episodio;
class File_Serie;
class LineaVerticale;
class QStackedWidget;
class AddFileWidget;
class AddEpisodioWidget;
class QIcon;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(Biblioteca* biblioteca ,QWidget *parent = nullptr);
private:

    QStackedWidget *stackedWidget;
    QWidget *principale;
    AddFileWidget *aggiuntaLibro=nullptr;
    AddFileWidget *aggiuntaFilm=nullptr;
    AddFileWidget *aggiuntaSerie=nullptr;
    AddEpisodioWidget* episodioWidget=nullptr;

    File_Serie* currentSerie;
    QWidget* currentSerieWidget;

    LeftSide *leftSide;
    RightSide *rightSide;
    Biblioteca *biblioteca;
    LineaVerticale *linea;

    QIcon* preferito_si;
    QIcon* preferito_no;

private slots:
    void showAddFileWidget(int index);
    void showMainWindow();
    void DettagliIndietro();
    void mostraWindow(File_Generico* file);
    void showAddEpisodioWidget();
    void mostraEpisodio(File_Episodio* episodio);

    void elimina(File_Generico*);

signals:
    void bibliotecaChanged();

};


#endif // MAIN_WINDOW_HPP