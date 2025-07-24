#ifndef ADD_EPISODIO_WIDGET_HPP
#define ADD_EPISODIO_WIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

class File_Serie;

class QPushButton;
class QVBoxLayout;
class QCheckBox;
class QButtonGroup;

class AddEpisodioWidget : public QWidget{
        Q_OBJECT

public:
    explicit AddEpisodioWidget(File_Serie* serie = nullptr, QWidget *parent = nullptr);

private:
    File_Serie *serie;

    QPushButton *conferma;
    QPushButton *annulla;

    QVBoxLayout *layout;
    QHBoxLayout *layoutSotto = new QHBoxLayout();
    QHBoxLayout *layoutBig = new QHBoxLayout();
    QFormLayout *layoutSx = new QFormLayout();
    QFormLayout *layoutDx = new QFormLayout();

    QLabel *icona = new QLabel();

    //attributi episodio
    QLineEdit *nome = new QLineEdit();
    QLabel *autore = new QLabel();
    QLabel *genere = new QLabel();
    QSpinBox *anno = new QSpinBox();
    QSpinBox *durata = new QSpinBox();
    QLineEdit *regista = new QLineEdit();
    QLineEdit *casa_di_produzione = new QLineEdit();
    QSpinBox *numero_stagione = new QSpinBox();
    QSpinBox *numero_episodio = new QSpinBox();

    QLabel *nomeSerie = new QLabel();

protected:
    void NonCampiVuoti();
    void pulisciCampi();

public slots:
    void AggiungiEpisodio();

    void ConfermaAggiunta();
    void AnnullaAggiunta();

signals:
    void FileAggiunto();
    void FileAnnullato();

};


#endif //ADD_EPISODIO_WIDGET_HPP