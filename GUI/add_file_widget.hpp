#ifndef ADD_FILE_WIDGET_HPP
#define ADD_FILE_WIDGET_HPP

#include <QWidget>

class Biblioteca;
class QPushButton;
class QLabel;
class QFormLayout;
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QCheckBox;
class QButtonGroup;


class AddFileWidget : public QWidget {
    Q_OBJECT

public:
    explicit AddFileWidget(Biblioteca* biblioteca = nullptr, int =0 , QWidget *parent = nullptr);
    void pulisciCampi();

private:

    int tipo;

    Biblioteca *biblioteca;
    
    QPushButton *conferma;
    QPushButton *annulla;

    QVBoxLayout *layout;
    QFormLayout *layoutSx;
    QFormLayout *layoutDx;
    QHBoxLayout *layoutSotto;
    QHBoxLayout *layoutBig;

    QLabel *icona;

    QLineEdit *nome;
    QLineEdit *autore;
    QLineEdit *genere;
    QLineEdit *anno;

    //attributi libro
    QLineEdit *pagine;
    QLineEdit *editore;

    //attributi video
    QLineEdit *durata;
    QLineEdit *regista;
    QLineEdit *casa_di_produzione;

    //attributi film
    QCheckBox *oscar;

    //attributi episodio

    QLineEdit *numero_stagione;
    QLineEdit *numero_episodio;

    void seFileAggiunto();
    void annullamento();
    void SceltaTipo(int);
    void checkValidita();

public slots:
    void AggiungiLibro();
    void AggiungiFilm();
    //void AggiungiSerie();

signals:
    void FileAggiunto();
};

#endif //ADD_FILE_WINDOW_HPP