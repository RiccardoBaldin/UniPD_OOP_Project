#include "disposizione_linee.hpp"

#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../visitor/ListaVisitor.hpp"

#include <QListWidget>
#include <QVBoxLayout>

DisposizioneLinee::DisposizioneLinee(Biblioteca* biblioteca, QWidget *parent) : QWidget(parent), biblioteca(biblioteca) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);


    listWidget = new QListWidget(this);
    listWidget->setAlternatingRowColors(true);
    listWidget->setStyleSheet("QListWidget::item { border-bottom: 1px solid green; }");

    mainLayout->addWidget(listWidget);

    setLayout(mainLayout);

    updateLayout();
}

void DisposizioneLinee::updateLayout() {
    listWidget->clear();

    for(File_Generico* file : biblioteca->getArchivio()){
        QWidget* widget = new QWidget(this);
        
        ListaVisitor visitor;
        file->Accept(visitor);
        QHBoxLayout* layout = visitor.GetLayout();
        widget->setLayout(layout);

        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, widget);
        
        connect(listWidget, &QListWidget::itemClicked, this, [this, file, widget](QListWidgetItem* clickedItem) {
                if (listWidget->itemWidget(clickedItem) == widget) {
                    emit File_Clicked(file);
                }
            }
        );
    }
}