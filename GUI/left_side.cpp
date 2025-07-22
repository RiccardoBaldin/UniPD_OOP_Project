#include "left_side.hpp"
#include "tree.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../JSON_CONTROL/ToJson.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QTreeWidget>
#include <QPushButton>
#include <QComboBox>
#include <QShortcut>
#include <QKeySequence>


LeftSide::LeftSide(Biblioteca* biblioteca, QWidget *parent) : QWidget(parent), biblioteca(biblioteca) {
    setFixedWidth(220);


    QLabel *logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/IMMAGINI/LOGO.png"));
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setFixedHeight(100);
    

    tree = new Tree(biblioteca, this);
    aggiuntaFile = new QComboBox(this);
    

    aggiuntaFile->addItem("Aggiungi un libro");
    aggiuntaFile->addItem("Aggiungi un film");
    aggiuntaFile->addItem("Aggiungi una serie TV");

    aggiuntaFile->setPlaceholderText("Aggiungi un file");

    QShortcut* shortcut = new QShortcut(QKeySequence("Ctrl+N"), this);
    connect(shortcut, &QShortcut::activated, aggiuntaFile, &QComboBox::showPopup);
    
    connect(aggiuntaFile, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LeftSide::onComboBoxIndexChanged);
    connect(tree, &Tree::updateTreeSignal, this, &LeftSide::updateTree);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(logoLabel);
    layout->addWidget(tree);
    layout->addWidget(aggiuntaFile);

    setLayout(layout);
}

void LeftSide::updateTree() {
    tree->updateTree();
}

void LeftSide::resetComboBox(){
    aggiuntaFile->setCurrentIndex(-1);
    //non so perche non mostri il placeholder, su macOs funziona, fatto seguendo documentazione ufficiale Qt
}

void LeftSide::onComboBoxIndexChanged(int index) {
    emit addFileSignal(index);
    resetComboBox();
}