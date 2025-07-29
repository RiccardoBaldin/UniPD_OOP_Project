#include "GrigliaVisitor.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"

#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QVBoxLayout>

void GrigliaVisitor::Visit(File_Generico& file) {
    layout = new QVBoxLayout();
    label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(file.GetNome()));

    nome->setAlignment(Qt::AlignLeft);
    nome->setStyleSheet("color: black;");
    layout->addWidget(nome);
}

void GrigliaVisitor::Visit(File_Video& video){}

void GrigliaVisitor::Visit(File_Film& film) {
    Visit(static_cast<File_Generico&>(film));
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    label->setPixmap(icona->pixmap(65, 65));
}


void GrigliaVisitor::Visit(File_Episodio& episodio) {}


void GrigliaVisitor::Visit(File_Serie& serie) {
    Visit(static_cast<File_Generico&>(serie));
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    label->setPixmap(icona->pixmap(69,69));
}


void GrigliaVisitor::Visit(File_Libro& libro) {
    Visit(static_cast<File_Generico&>(libro));
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    label->setPixmap(icona->pixmap(69, 69));
}


QVBoxLayout* GrigliaVisitor::GetLayout() const {
    return layout;
}