#ifndef QUADRATINI_HPP
#define QUADRATINI_HPP

#include <QWidget>
#include <QVBoxLayout>

class File_Generico;
class QLabel;

class Quadratini : public QWidget {
    Q_OBJECT

public:
    explicit Quadratini(File_Generico* file, QWidget *parent = nullptr);

signals:
    void QuadratinoClicked(File_Generico* file);

private:
    File_Generico* file;

protected:
    void mousePressEvent(QMouseEvent *event) override;

};


#endif // QUADRATINI_HPP