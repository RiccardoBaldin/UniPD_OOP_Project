#include "main_window.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../JSON_CONTROL/ToJson.hpp"
#include "../visitor/MostraVisitor.hpp"
#include "../visitor/mostra_helper.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "add_episodio_widget.hpp"
#include "left_side.hpp"
#include "right_side.hpp"
#include "linea_verticale.hpp"
#include "add_file_widget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QApplication>
#include <QPushButton>
#include <QIcon>
#include <iostream>
 
MainWindow::MainWindow(Biblioteca* biblioteca, QWidget *parent) : QMainWindow(parent), biblioteca(biblioteca){
    
    setWindowTitle("Biblioteca");
    setMinimumSize(800, 600);

    stackedWidget = new QStackedWidget(this);
    
    principale = new QWidget(this);
    aggiuntaLibro = new AddFileWidget(biblioteca, 0, this);     //widget di aggiunta Libro
    aggiuntaFilm = new AddFileWidget(biblioteca, 1, this);      //widget di aggiunta Film
    aggiuntaSerie = new AddFileWidget(biblioteca, 2, this);     //widget di aggiunta Serie

    leftSide = new LeftSide(biblioteca);
    rightSide = new RightSide(biblioteca);
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
    

    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    
    connect(aggiuntaLibro, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);

    connect(aggiuntaFilm, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    
    connect(aggiuntaFilm, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);

    connect(aggiuntaSerie, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    
    connect(aggiuntaSerie, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);

    
    connect(rightSide, &RightSide::File_Clicked, this, &MainWindow::mostraWindow);
    connect(rightSide, &RightSide::elimina, this, &MainWindow::elimina);
    
}

void MainWindow::elimina(File_Generico* file){
    biblioteca->killFile(file);
    showMainWindow();
}

void MainWindow::mostraWindow(File_Generico* file){
    
    QWidget* mostra = new QWidget();

    MostraVisitorHelper* a = new MostraVisitorHelper(file, this);

    QPushButton* indietro = new QPushButton("Indietro");

    QPushButton* toggle_preferito = new QPushButton();
    toggle_preferito->setIcon(file->IsPreferito() ? *preferito_si : *preferito_no);
    toggle_preferito->setIconSize(QSize(24, 24));  
    toggle_preferito->setFixedSize(32, 32);        


    QHBoxLayout* sopra = new QHBoxLayout();
    sopra->addWidget(indietro, 0, Qt::AlignLeft);
    sopra->addWidget(toggle_preferito, 0, Qt::AlignRight);
    toggle_preferito->setFlat(true);
    toggle_preferito->setStyleSheet("background-color: transparent; border: none;");

    QVBoxLayout* intero = new QVBoxLayout();
    intero->addLayout(sopra);
    intero->addWidget(a);
    
    mostra->setLayout(intero);

    stackedWidget->addWidget(mostra);
    stackedWidget->setCurrentWidget(mostra);

    File_Serie* s = dynamic_cast<File_Serie*>(file);
    if(s){
        currentSerie = s;
        currentSerieWidget = mostra;
        connect(a, &MostraVisitorHelper::AggiuntaEpisodio, this, &MainWindow::showAddEpisodioWidget);
        connect(a, &MostraVisitorHelper::EpisodioSelezionato, this, &MainWindow::mostraEpisodio);
    }

    connect(indietro, &QPushButton::clicked, this, &MainWindow::showMainWindow);
    connect(toggle_preferito, &QPushButton::clicked, [this, file, toggle_preferito]() {
        file->togglePreferito();
        toggle_preferito->setIcon(file->IsPreferito() ? *preferito_si : *preferito_no);
    });
}

void MainWindow::mostraEpisodio(File_Episodio* ep) {
    if (!ep) return;
    
    QWidget* mostra = new QWidget();

    MostraVisitorHelper* episodio = new MostraVisitorHelper(static_cast<File_Generico*>(ep));

    QPushButton* indietro = new QPushButton("Indietro");

    QPushButton* toggle_preferito = new QPushButton();
    toggle_preferito->setIcon(ep->IsPreferito() ? *preferito_si : *preferito_no);
    toggle_preferito->setIconSize(QSize(24, 24));  
    toggle_preferito->setFixedSize(32, 32);

    QHBoxLayout* sopra = new QHBoxLayout();
    sopra->addWidget(indietro, 0, Qt::AlignLeft);
    sopra->addWidget(toggle_preferito, 0, Qt::AlignRight);
    toggle_preferito->setFlat(true);
    toggle_preferito->setStyleSheet("background-color: transparent; border: none;");

    QVBoxLayout* intero = new QVBoxLayout();
    intero->addLayout(sopra);
    intero->addWidget(episodio);

    mostra->setLayout(intero);

    stackedWidget->addWidget(mostra);
    stackedWidget->setCurrentWidget(mostra);

    connect(indietro, &QPushButton::clicked, [this]() {
        stackedWidget->removeWidget(this);
        stackedWidget->setCurrentWidget(currentSerieWidget);
    });

    connect(toggle_preferito, &QPushButton::clicked, [this, ep, toggle_preferito]() {
        ep->togglePreferito();
        toggle_preferito->setIcon(ep->IsPreferito() ? *preferito_si : *preferito_no);
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
        connect(episodioWidget, &AddEpisodioWidget::FileAggiunto, this, &MainWindow::showMainWindow);
        connect(episodioWidget, &AddEpisodioWidget::FileAnnullato, this, &MainWindow::showMainWindow);
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
    rightSide->updateLayout();
    leftSide->updateTree();
    QWidget *focus = QApplication::focusWidget();
    if(focus) focus->clearFocus();
    principale->setFocus();
}