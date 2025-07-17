#include "upper_bar.hpp"
#include "disposizione_griglia.hpp"
#include "disposizione_linee.hpp"

#include <QStackedWidget>
#include <iostream>

UpperBar::UpperBar(Biblioteca *biblioteca, QWidget *parent) : QWidget(parent), biblioteca(biblioteca) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    setMaximumHeight(50);


    changeLayout = new QComboBox();
    changeLayout->setMaximumWidth(100);
    changeLayout->setMinimumWidth(100);

    sortComboBox = new QComboBox(this);
    sortComboBox->setMaximumWidth(150);
    sortComboBox->setMinimumWidth(150);

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca...");
    searchBar->setMinimumWidth(200);
    searchBar->setMaximumWidth(200);


    changeLayout->addItem("Griglia");
    changeLayout->addItem("Lista");


    sortComboBox->addItem("ordina per nome");
    sortComboBox->addItem("ordina per data");

    layout->addWidget(changeLayout);
    layout->addStretch();
    layout->addWidget(sortComboBox);
    layout->addStretch();
    layout->addWidget(searchBar);

    setLayout(layout);

    connect(changeLayout, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &UpperBar::handleLayoutChange);
}

void UpperBar::handleLayoutChange(int index) {
    emit layoutChanged(index);
}