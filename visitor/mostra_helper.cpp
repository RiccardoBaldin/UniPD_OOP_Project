#include "mostra_helper.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"


#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

MostraVisitorHelper::MostraVisitorHelper(File_Generico* file, QWidget *parent) : QWidget(parent), serie(dynamic_cast<File_Serie*>(file)){
    if(file == nullptr) return;
    file->Accept(visitor);

    if(serie){
        QPushButton* BottoneAggiunta = new QPushButton("Aggiungi Episodio");
        connect(BottoneAggiunta, &QPushButton::clicked, this, &MostraVisitorHelper::Aggiungi_Clicked);
        layout->addWidget(BottoneAggiunta);
    }

    layout->addLayout(visitor.GetLayout());

}

QVBoxLayout* MostraVisitorHelper::GetLayout(){
    return layout;
}

void MostraVisitorHelper::Aggiungi_Clicked(){
    emit AggiuntaEpisodio();
}