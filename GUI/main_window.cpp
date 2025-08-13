#include "main_window.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../JSON_CONTROL/ToJson.hpp"
#include "../visitor/MostraVisitor.hpp"
#include "../visitor/mostra_helper.hpp"
#include "../visitor/ModificaVisitor.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../JSON_CONTROL/FromJson.hpp"
#include "add_episodio_widget.hpp"
#include "left_side.hpp"
#include "right_side.hpp"
#include "linea_verticale.hpp"
#include "add_file_widget.hpp"
#include "upper_bar.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QApplication>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
 
MainWindow::MainWindow(Biblioteca* biblioteca, QWidget *parent) : QMainWindow(parent), biblioteca(biblioteca), lista(biblioteca->getArchivio()){

    setWindowTitle("Biblioteca");
    setMinimumSize(800, 600);

    stackedWidget = new QStackedWidget(this);
    
    principale = new QWidget(this);
    aggiuntaLibro = new AddFileWidget(biblioteca, 0, this);  
    aggiuntaFilm = new AddFileWidget(biblioteca, 1, this);    
    aggiuntaSerie = new AddFileWidget(biblioteca, 2, this);  

    leftSide = new LeftSide(biblioteca);
    rightSide = new RightSide(lista);
    linea = new LineaVerticale(this);

    linea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QHBoxLayout *layoutPrincipale = new QHBoxLayout(principale);
    layoutPrincipale->setContentsMargins(0, 0, 0, 0);
    layoutPrincipale->setSpacing(0);

    layoutPrincipale->addWidget(leftSide);
    layoutPrincipale->addWidget(linea);
    layoutPrincipale->addWidget(rightSide);

    principale->setLayout(layoutPrincipale);

    stackedWidget->addWidget(principale);
    stackedWidget->addWidget(aggiuntaLibro);
    stackedWidget->addWidget(aggiuntaFilm);
    stackedWidget->addWidget(aggiuntaSerie);

    setCentralWidget(stackedWidget);

    preferito_si = new QIcon(":/IMMAGINI/preferito_si.png");
    preferito_no = new QIcon(":/IMMAGINI/preferito_no.png");   

    connect(leftSide, &LeftSide::addFileSignal, this, &MainWindow::showAddFileWidget);
    connect(leftSide, &LeftSide::importaBiblioteca, this, &MainWindow::importaBiblioteca);
    connect(leftSide, &LeftSide::importaFile, this, &MainWindow::importaFile);
    connect(leftSide, &LeftSide::salvaBiblioteca, this, &MainWindow::salvaBiblioteca);
    
    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, this, [this](){this->biblioteca->isSaved = false;});

    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaLibro, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);
    connect(aggiuntaFilm, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaFilm, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);
    connect(aggiuntaSerie, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaSerie, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);
    
    connect(rightSide, &RightSide::File_Clicked, this, &MainWindow::mostraWindow);
    connect(rightSide, &RightSide::elimina, this, &MainWindow::elimina);
    connect(rightSide, &RightSide::modifica, this, &MainWindow::modifica);
    connect(rightSide, &RightSide::salva, this, &MainWindow::salva);
    connect(rightSide, &RightSide::preferito, this, &MainWindow::preferito);

    connect(rightSide, &RightSide::sortNome, this, [this, biblioteca](){ biblioteca->sort_nome(); showMainWindow(); });
    connect(rightSide, &RightSide::sortData, this, [this, biblioteca](){ biblioteca->sort_anno(); showMainWindow(); });

    connect(rightSide, &RightSide::showPreferiti, this, [this,biblioteca](){rightSide->setLista(biblioteca->preferiti()); 
        this->p = true; });
    connect(rightSide, &RightSide::showGenerale, this, [this,biblioteca](){rightSide->setLista(biblioteca->getArchivio());
        this->p = false;});

    connect(leftSide, &LeftSide::aaaLibri, this, [this, biblioteca]{rightSide->setLista(biblioteca->getLibri());
        (rightSide->getBarra())->pulisci();});
    connect(leftSide, &LeftSide::aaaFilm, this, [this, biblioteca]{rightSide->setLista(biblioteca->getFilm());
        (rightSide->getBarra())->pulisci();});
    connect(leftSide, &LeftSide::aaaSerie, this, [this, biblioteca]{rightSide->setLista(biblioteca->getSerie());
        (rightSide->getBarra())->pulisci();});
    connect(leftSide, &LeftSide::aaaGesuCristo, this, [this, biblioteca]{rightSide->setLista(biblioteca->getArchivio());
        (rightSide->getBarra())->pulisci();});

    connect(rightSide, &RightSide::layoutChanged, this, &MainWindow::showMainWindow);

    connect(rightSide, &RightSide::testoCercato, this, &MainWindow::cercazioneFiles);
}

void MainWindow::cercazioneFiles(const QString& t){
    rightSide->setLista(biblioteca->finder(t.toStdString()));
}


void MainWindow::modifica(File_Generico* file){

    QWidget *modifica = new QWidget();
    QHBoxLayout *sotto = new QHBoxLayout();
    QPushButton *annulla = new QPushButton("Annulla");
    QPushButton *conferma = new QPushButton("Conferma");
    sotto->addWidget(annulla, 0, Qt::AlignLeft);
    sotto->addWidget(conferma, 0, Qt::AlignRight);

    ModificaVisitor *visitor = new ModificaVisitor();
    file->Accept(*visitor);
    QVBoxLayout* intero = new QVBoxLayout();
    intero->addWidget(visitor->GetWidget());
    intero->addLayout(sotto);
    modifica->setLayout(intero);
    
    stackedWidget->addWidget(modifica);
    stackedWidget->setCurrentWidget(modifica);

    connect(annulla, &QPushButton::clicked, this, [this, modifica, file]() {
        stackedWidget->removeWidget(modifica);
        modifica->deleteLater();
        rightSide->updateLayout(biblioteca->getArchivio());
        leftSide->updateTree();

        if(auto e = dynamic_cast<File_Episodio*>(file)){
            mostraEpisodio(e);  
        } else {
            mostraWindow(file);
        }
    });

    connect(conferma, &QPushButton::clicked, this, [this, file, visitor, modifica]() {
        if (visitor->confermaModifiche(file, biblioteca)) {
            stackedWidget->removeWidget(modifica);
            modifica->deleteLater();
            rightSide->updateLayout(biblioteca->getArchivio());
            leftSide->updateTree();
            biblioteca->isSaved = false;
            if(auto e = dynamic_cast<File_Episodio*>(file)){
                mostraEpisodio(e);
            } else {
                mostraWindow(file);
            }
        }
    });



}


void MainWindow::preferito(File_Generico* file){
    file->togglePreferito();
    biblioteca->isSaved = false;
    if(!file->IsPreferito() && p) rightSide->showPreferiti();
}

void MainWindow::elimina(File_Generico* file){

    QMessageBox::StandardButton conferma;
    conferma = QMessageBox::question(this,
                                "Conferma eliminazione",
                                "Sei sicuro di voler eliminare questo elemento?",
                                QMessageBox::Yes | QMessageBox::No);

    if (conferma == QMessageBox::No) {
        return;
    }

    if(auto e = dynamic_cast<File_Episodio*>(file)){
        File_Serie* s = e->GetSerieFile();
        s->RimuoviEpisodio(e);
        delete e;
        mostraWindow(s);
    }else{
        biblioteca->killFile(file);
        showMainWindow();
    }
    biblioteca->isSaved = false;
}

void MainWindow::mostraWindow(File_Generico* file){
    
    if (currentMostraWidget) {
        stackedWidget->removeWidget(currentMostraWidget);
        currentMostraWidget->deleteLater();
        currentMostraWidget = nullptr;
    }

    QWidget* mostra = new QWidget();

    MostraVisitorHelper* a = new MostraVisitorHelper(file, mostra);

    QPushButton* indietro = new QPushButton("Indietro");
    QPushButton* modificaBtn = new QPushButton("Modifica");
    QPushButton* toggle_preferito = new QPushButton();
    toggle_preferito->setIcon(file->IsPreferito() ? *preferito_si : *preferito_no);
    toggle_preferito->setIconSize(QSize(24, 24));  
    toggle_preferito->setFixedSize(32, 32);        

    QHBoxLayout* sopra = new QHBoxLayout();
    sopra->addWidget(indietro, 0, Qt::AlignLeft);
    sopra->addWidget(modificaBtn, 0, Qt::AlignCenter);
    sopra->addWidget(toggle_preferito, 0, Qt::AlignRight);

    toggle_preferito->setFlat(true);
    toggle_preferito->setStyleSheet("background-color: transparent; border: none;");

    QVBoxLayout* intero = new QVBoxLayout();
    intero->addLayout(sopra);
    intero->addWidget(a);
    mostra->setLayout(intero);

    stackedWidget->addWidget(mostra);
    stackedWidget->setCurrentWidget(mostra);

    currentMostraWidget = mostra;

    File_Serie* s = dynamic_cast<File_Serie*>(file);
    if(s){
        currentSerie = s;
        currentSerieWidget = mostra;
        connect(a, &MostraVisitorHelper::AggiuntaEpisodio, this, &MainWindow::showAddEpisodioWidget);
        connect(a, &MostraVisitorHelper::EpisodioSelezionato, this, &MainWindow::mostraEpisodio);
        connect(a, &MostraVisitorHelper::EpisodioElimina, this, &MainWindow::elimina);
        connect(a, &MostraVisitorHelper::EpisodioModifica, this, &MainWindow::modifica);
        connect(a, &MostraVisitorHelper::EpisodioSalva, this, &MainWindow::salva);
    }

    connect(indietro, &QPushButton::clicked, this, [this, mostra](){
        stackedWidget->removeWidget(mostra);
        mostra->deleteLater();   
        currentMostraWidget = nullptr;
        rightSide->updateLayout(biblioteca->getArchivio());
        leftSide->updateTree();
        stackedWidget->setCurrentWidget(principale);
    });
    connect(toggle_preferito, &QPushButton::clicked, [this, file, toggle_preferito]() {
        file->togglePreferito();
        toggle_preferito->setIcon(file->IsPreferito() ? *preferito_si : *preferito_no);
    });
    connect(modificaBtn, &QPushButton::clicked, this, [this, file]() {
    modifica(file);
    });

}

void MainWindow::mostraEpisodio(File_Episodio* ep) {
    if (!ep) return;

    if (currentEpisodioWidget) {
        stackedWidget->removeWidget(currentEpisodioWidget);
        currentEpisodioWidget->deleteLater();
        currentEpisodioWidget = nullptr;
    }
    
    QWidget* mostra = new QWidget();

    MostraVisitorHelper* episodio = new MostraVisitorHelper(static_cast<File_Generico*>(ep), mostra);

    QPushButton* indietro = new QPushButton("Indietro");
    QPushButton* modificaBtn = new QPushButton("Modifica");
    QPushButton* toggle_preferito = new QPushButton();
    toggle_preferito->setIcon(ep->IsPreferito() ? *preferito_si : *preferito_no);
    toggle_preferito->setIconSize(QSize(24, 24));  
    toggle_preferito->setFixedSize(32, 32);

    QHBoxLayout* sopra = new QHBoxLayout();
    sopra->addWidget(indietro, 0, Qt::AlignLeft);
    sopra->addWidget(modificaBtn, 0, Qt::AlignCenter);
    sopra->addWidget(toggle_preferito, 0, Qt::AlignRight);

    toggle_preferito->setFlat(true);
    toggle_preferito->setStyleSheet("background-color: transparent; border: none;");

    QVBoxLayout* intero = new QVBoxLayout();
    intero->addLayout(sopra);
    intero->addWidget(episodio);
    mostra->setLayout(intero);

    stackedWidget->addWidget(mostra);
    stackedWidget->setCurrentWidget(mostra);

    currentEpisodioWidget = mostra;

    connect(indietro, &QPushButton::clicked, [this, mostra]() {
        stackedWidget->removeWidget(mostra);
        mostra->deleteLater();
        currentEpisodioWidget = nullptr;
        rightSide->updateLayout(biblioteca->getArchivio());
        leftSide->updateTree();
        stackedWidget->setCurrentWidget(currentSerieWidget);
    });

    connect(toggle_preferito, &QPushButton::clicked, [this, ep, toggle_preferito]() {
        ep->togglePreferito();
        toggle_preferito->setIcon(ep->IsPreferito() ? *preferito_si : *preferito_no);
    });

    connect(modificaBtn, &QPushButton::clicked, this, [this, ep]() {
        modifica(ep);
    });


}

void MainWindow::showAddFileWidget(int index){
    switch(index){
        case 0:
            stackedWidget->setCurrentWidget(aggiuntaLibro);
            break;
        case 1:
            stackedWidget->setCurrentWidget(aggiuntaFilm);
            break;
        case 2:
            stackedWidget->setCurrentWidget(aggiuntaSerie);
            break;
        default:
            break;
    }
}

void MainWindow::showAddEpisodioWidget(){
    if(!episodioWidget){
        episodioWidget = new AddEpisodioWidget(currentSerie, this);
        connect(episodioWidget, &AddEpisodioWidget::FileAggiunto, this, [this]() {
            stackedWidget->removeWidget(episodioWidget);
            episodioWidget->deleteLater();
            rightSide->updateLayout(biblioteca->getArchivio());
            leftSide->updateTree();
            episodioWidget = nullptr;
            mostraWindow(currentSerie);
        });
        connect(episodioWidget, &AddEpisodioWidget::FileAnnullato, this, [this]() {
            stackedWidget->removeWidget(episodioWidget);
            episodioWidget->deleteLater();
            rightSide->updateLayout(biblioteca->getArchivio());
            leftSide->updateTree();
            episodioWidget = nullptr;
            mostraWindow(currentSerie);
        });
        stackedWidget->addWidget(episodioWidget);
    }else{
        episodioWidget->setSerie(currentSerie);
    }
    stackedWidget->setCurrentWidget(episodioWidget);
}

void MainWindow::DettagliIndietro(){
    stackedWidget->setCurrentWidget(principale);
}

void MainWindow::showMainWindow() {
    stackedWidget->setCurrentWidget(principale);
    rightSide->setLista(biblioteca->getArchivio());
    leftSide->updateTree();
    QWidget *focus = QApplication::focusWidget();
    if(focus) focus->clearFocus();
    principale->setFocus();
    
}

void MainWindow::importaBiblioteca() {
    if (!biblioteca->isSaved) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Salva biblioteca?", "La biblioteca corrente non è salvata. Vuoi salvarla prima di importare una nuova biblioteca?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel) return;
        if (reply == QMessageBox::Yes) {
            QString savePath = QFileDialog::getSaveFileName(this, "Salva biblioteca", "", "File JSON (*.json)");
            if (!savePath.isEmpty()) {
                try {
                    saveAsJson(biblioteca, savePath.toStdString());
                } catch (const std::exception& e) {
                    QMessageBox::warning(this, "Errore", QString::fromStdString(e.what()));
                    return;
                }
            } else {
                return;
            }
        }
    }

    QString filePath = QFileDialog::getOpenFileName(this, "Importa biblioteca", "", "File JSON (*.json)");
    if (filePath.isEmpty()) return;

    Biblioteca* nuovaBib = creaBibliotecaDaJson(filePath.toStdString());
    if (!nuovaBib) {
        QMessageBox::warning(this, "Errore", "Impossibile caricare la biblioteca.");
        return;
    }

    biblioteca->clear();

    for (auto f : nuovaBib->getArchivio()) {
        if (f) {
            biblioteca->addFile(f->clone());
        }
    }
    biblioteca->isSaved = true;

    delete nuovaBib;

    rightSide->updateLayout(biblioteca->getArchivio());
    leftSide->updateTree();
}

void MainWindow::importaFile() {
    QString filePath = QFileDialog::getOpenFileName(
        this, "Importa file", "", "File JSON (*.json)");
    if (filePath.isEmpty()) return;

    File_Generico* nuovoFile = creaFileDaJson(filePath.toStdString());
    if (!nuovoFile) {
        QMessageBox::warning(this, "Errore", "Impossibile caricare il file.");
        return;
    }

    if (!biblioteca->check(nuovoFile)) {
        std::string tipo;
        if (dynamic_cast<File_Libro*>(nuovoFile)) tipo = "Il libro";
        else if (dynamic_cast<File_Film*>(nuovoFile)) tipo = "Il film";
        else if (dynamic_cast<File_Serie*>(nuovoFile)) tipo = "La serie";
        else tipo = "File";

        QMessageBox::warning(this, "Errore", 
            QString::fromStdString(tipo + " \"" + nuovoFile->GetNome() + "\" è già presente nella biblioteca."));
        delete nuovoFile; 
        return;
    }

    biblioteca->addFile(nuovoFile);

    rightSide->updateLayout(biblioteca->getArchivio());
    leftSide->updateTree();
}

void MainWindow::salvaBiblioteca() {
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Salva biblioteca",
        "",
        "File JSON (*.json)"
    );

    if (filePath.isEmpty()) return;

    try {
        saveAsJson(biblioteca, filePath.toStdString());
        biblioteca->isSaved = true;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", QString::fromStdString(e.what()));
    }
}

void MainWindow::salva(File_Generico* file){
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Salva file singolo",
        "",
        "File JSON (*.json)"
    );

    if (filePath.isEmpty()) return;

    try {
        saveAsJson(file, filePath.toStdString());
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", QString::fromStdString(e.what()));
    }
}