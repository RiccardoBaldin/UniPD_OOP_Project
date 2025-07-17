#include "quadratini.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../visitor/GrigliaVisitor.hpp"

#include <QLabel>
#include <QPixmap>
#include <QIcon>

Quadratini::Quadratini(File_Generico* file, QWidget *parent) : QWidget(parent), file(file) {
    
    setFixedSize(120, 120);
    setStyleSheet("background-color: #BEBEBE; border: 2px solid black; border-radius: 5px;");

    GrigliaVisitor visitor;
    file->Accept(visitor);
    QVBoxLayout *layout= visitor.GetLayout();

    
    setLayout(layout);
}

void Quadratini::mousePressEvent(QMouseEvent *) {
    emit QuadratinoClicked(file);
}