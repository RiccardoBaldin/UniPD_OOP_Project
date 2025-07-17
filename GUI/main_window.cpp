#include "main_window.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../JSON_CONTROL/ToJson.hpp"
#include "left_side.hpp"
#include "right_side.hpp"
#include "linea_verticale.hpp"
#include "add_file_widget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <iostream>

MainWindow::MainWindow(Biblioteca* biblioteca, QWidget *parent) : QMainWindow(parent), biblioteca(biblioteca){
    
    setWindowTitle("Biblioteca");
    setMinimumSize(800, 600);

    stackedWidget = new QStackedWidget(this);
    
    principale = new QWidget(this);
    aggiuntaLibro = new AddFileWidget(biblioteca, 0, this);
    aggiuntaFilm = new AddFileWidget(biblioteca, 1, this);
    aggiuntaSerie = new AddFileWidget(biblioteca, 2, this);

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

    connect(leftSide, &LeftSide::addFileSignal, this, &MainWindow::showAddFileWidget);

    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, leftSide, &LeftSide::updateTree);
    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, rightSide, &RightSide::updateLayout);

    connect(aggiuntaFilm, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaFilm, &AddFileWidget::FileAggiunto, leftSide, &LeftSide::updateTree);
    connect(aggiuntaFilm, &AddFileWidget::FileAggiunto, rightSide, &RightSide::updateLayout);

    connect(aggiuntaSerie, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaSerie, &AddFileWidget::FileAggiunto, leftSide, &LeftSide::updateTree);
    connect(aggiuntaSerie, &AddFileWidget::FileAggiunto, rightSide, &RightSide::updateLayout);

    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, leftSide, &LeftSide::resetComboBox);
    connect(aggiuntaFilm, &AddFileWidget::FileAggiunto, leftSide, &LeftSide::resetComboBox);
    connect(aggiuntaSerie, &AddFileWidget::FileAggiunto, leftSide, &LeftSide::resetComboBox);
}

void MainWindow::showAddFileWidget(int index){
    switch(index){
        case 0:
            std::cout << "aggiunta libro" << std::endl;
            stackedWidget->setCurrentWidget(aggiuntaLibro);
            break;
        case 1:
            std::cout << "aggiunta film" << std::endl;
            stackedWidget->setCurrentWidget(aggiuntaFilm);
            break;
        case 2:
            std::cout << "aggiunta serie" << std::endl;
            stackedWidget->setCurrentWidget(aggiuntaSerie);
            break;
        default:
            break;
    }
}

void MainWindow::showMainWindow() {
    stackedWidget->setCurrentWidget(principale);
    rightSide->updateLayout();
}