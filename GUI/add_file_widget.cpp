#include "add_file_widget.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QRadioButton>
#include "linea_orizzontale.hpp"
#include "JSON_CONTROL/ToJson.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"

AddFileWidget::AddFileWidget(Biblioteca* biblioteca, int index, QWidget *parent) : QWidget(parent), tipo(index), biblioteca(biblioteca){
   
    setWindowTitle("Add File");

    layout = new QVBoxLayout(this);
    layoutSotto = new QHBoxLayout();
    layoutBig = new QHBoxLayout();
    layoutSx = nullptr;
    layoutDx = nullptr;

    QWidget *filler = new QWidget();
    filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    annulla = new QPushButton("Annulla");
    conferma =  new QPushButton("Conferma");

    //attributi generici
    icona = new QLabel();

    nome = new QLineEdit();
    autore = new QLineEdit();
    genere = new QLineEdit();
    anno = new QLineEdit();

    //attributi libro
    pagine = new QLineEdit();
    editore = new QLineEdit();

    //attributi video
    durata = new QLineEdit();
    regista = new QLineEdit();
    casa_di_produzione = new QLineEdit();

    //attributi film
    oscar = new QCheckBox();

    //atributi episodio
    numero_stagione = new QLineEdit();
    numero_episodio = new QLineEdit();

    annulla->setFixedWidth(100);
    layoutSotto->addWidget(annulla);
    conferma->setFixedWidth(100);
    layoutSotto->addWidget(conferma);

    QLabel *testo = new QLabel("COMPILA I CAMPI PER AGGIUNGERE UN FILE");
    testo->setAlignment(Qt::AlignCenter);
    testo->setStyleSheet("font-size: 20px; color: red; font-weight: bold;");

    layout->addWidget(testo);
    layout->addWidget(new LineaOrizzontale());
    SceltaTipo(index);
    layout->addWidget(new LineaOrizzontale());
    layout->addLayout(layoutSotto);

    connect(conferma, &QPushButton::clicked, this, &AddFileWidget::checkValidita);
    connect(conferma, &QPushButton::clicked, this, &AddFileWidget::pulisciCampi);
    
    connect(annulla, &QPushButton::clicked, this, &AddFileWidget::annullamento);
    connect(annulla, &QPushButton::clicked, this, &AddFileWidget::pulisciCampi);
}

void AddFileWidget::annullamento() {
   emit FileAggiunto();
}

void AddFileWidget::checkValidita(){
    biblioteca->addFile(new File_Libro((nome->text().toStdString())));
    qDebug() << "Segnale FileAggiunto emesso";
    qDebug() << "File aggiunto. Ora la biblioteca ha " << biblioteca->getArchivio().size() << " file.";
    emit FileAggiunto();
}

// void AddFileWidget::seFileAggiunto(){
//     biblioteca->addFile(new File_Libro(nome->text().toStdString()));
//     saveAsJson(biblioteca);
//     pulisciCampi();

//     qDebug() << "Segnale FileAggiunto emesso da seFileAggiunto";

//     emit FileAggiunto();
// }

void AddFileWidget::SceltaTipo(int index) {
    switch(index){
        case 0:
            AggiungiLibro();
            break;
        case 1:
            AggiungiFilm();
            break;
        case 2:
            break;
    }
}


void AddFileWidget::AggiungiLibro(){
    icona = new QLabel();
    icona->setPixmap(QPixmap(":/IMMAGINI/Libro_Aggiungi.png"));
    icona->setFixedSize(300,300);
    icona->setAlignment(Qt::AlignCenter);

    layoutSx = new QFormLayout();
    layoutDx = new QFormLayout();

    layoutSx->addRow("Nome", nome);
    layoutSx->addRow("Autore", autore);
    layoutSx->addRow("Genere", genere);
    layoutSx->addRow("Anno", anno);

    layoutDx->addRow("Pagine", pagine);
    layoutDx->addRow("Editore", editore);

    QHBoxLayout* iconLayout = new QHBoxLayout();
    iconLayout->addStretch();
    iconLayout->addWidget(icona);
    iconLayout->addStretch();
    layout->addLayout(iconLayout);
    layoutBig->addLayout(layoutSx);
    layoutBig->addLayout(layoutDx);
    layout->addLayout(layoutBig);
}

void AddFileWidget::AggiungiFilm(){
    icona = new QLabel();
    icona->setPixmap(QPixmap(":/IMMAGINI/Film_Aggiungi.png"));
    icona->setFixedSize(300,300);
    icona->setAlignment(Qt::AlignCenter);

    layoutSx = new QFormLayout();
    layoutDx = new QFormLayout();

    layoutSx->addRow("Nome", nome);
    layoutSx->addRow("Autore", autore);
    layoutSx->addRow("Genere", genere);
    layoutSx->addRow("Anno", anno);

    layoutDx->addRow("Durata", durata);
    layoutDx->addRow("Regista", regista);
    layoutDx->addRow("Casa di produzione", casa_di_produzione);
    layoutDx->addRow("Oscar", oscar);

    layoutBig->addLayout(layoutSx);
    layoutBig->addLayout(layoutDx);
    layout->addWidget(icona);
    layout->addLayout(layoutBig);
}

void AddFileWidget::pulisciCampi() {
    nome->clear();
    autore->clear();
    genere->clear();
    anno->clear();
    pagine->clear();
    editore->clear();
    durata->clear();
    regista->clear();
    casa_di_produzione->clear();
    oscar->setChecked(false);
    numero_stagione->clear();
    numero_episodio->clear();
}