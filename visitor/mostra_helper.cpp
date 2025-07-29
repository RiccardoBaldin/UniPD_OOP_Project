#include "mostra_helper.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "episodio_item.hpp"


#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

MostraVisitorHelper::MostraVisitorHelper(File_Generico* file, QWidget *parent) : QWidget(parent), serie(dynamic_cast<File_Serie*>(file)){
    if(file == nullptr) return;
    
    layout= new QVBoxLayout(this);
    MostraVisitor* visitor= new MostraVisitor();
    file->Accept(*visitor);

    if(serie){

        QTreeWidget* albero = visitor->GetAlberoEpisodi();
        if(albero){
            connect(albero, &QTreeWidget::itemClicked, this, &MostraVisitorHelper::Episodio_Clicked);
        }

        QPushButton* BottoneAggiunta = new QPushButton("Aggiungi Episodio");
        connect(BottoneAggiunta, &QPushButton::clicked, this, [this](){ emit AggiuntaEpisodio();});
        layout->addWidget(BottoneAggiunta);
    }

    QWidget* container = visitor->GetWidget();
    layout->addWidget(container);

    setLayout(layout);
}


void MostraVisitorHelper::Episodio_Clicked(QTreeWidgetItem* item){
    if(auto epItem = dynamic_cast<EpisodioItem*>(item))
        if(epItem->getEpisodio())
            emit EpisodioSelezionato(epItem->getEpisodio());    
}