#ifndef ADD_FILE_WIDGET_HPP
#define ADD_FILE_WIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

class Biblioteca;
class QPushButton;
class QVBoxLayout;
class QCheckBox;
class QButtonGroup;

class File_Generico;

class AddFileWidget : public QWidget {
    Q_OBJECT

public:
    explicit AddFileWidget(Biblioteca* biblioteca = nullptr, int =0 , QWidget *parent = nullptr);

private:

    int tipo;

    Biblioteca *biblioteca;
    
    QPushButton *conferma;
    QPushButton *annulla;

    QVBoxLayout *layout;
    QHBoxLayout *layoutSotto = new QHBoxLayout();
    QHBoxLayout *layoutBig = new QHBoxLayout();
    QFormLayout *layoutSx = new QFormLayout();
    QFormLayout *layoutDx = new QFormLayout();
    QWidget *filler = new QWidget();

    QLabel *icona = new QLabel();

    //attributi generali
    QLineEdit *nome = new QLineEdit();
    QLineEdit *autore = new QLineEdit();
    QLineEdit *genere = new QLineEdit();
    QSpinBox *anno = new QSpinBox();

    //attributi libro
    QSpinBox *pagine;
    QLineEdit *editore;

    //attributi video
    QSpinBox *durata;
    QLineEdit *regista;
    QLineEdit *casa_di_produzione;

    //attributi film
    QCheckBox *oscar;

    //attributi serie
    QSpinBox *numero_stagioni;
    QSpinBox *numero_episodi;
    QLineEdit *casa_di_produzione_serie;

    //attributi episodio

    QSpinBox *numero_stagione;
    QSpinBox *numero_episodio;

protected:
    bool NonCampiVuoti();
    void SceltaTipo();
    void pulisciCampi();

public slots:
    void AggiungiLibro();
    void AggiungiFilm();
    void AggiungiSerie();
    
    void ConfermaAggiunta();
    void AnnullaAggiunta();

signals:
    void FileAggiunto();
    void FileAnnullato();
};

#endif //ADD_FILE_WINDOW_HPP