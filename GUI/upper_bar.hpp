#ifndef UPPER_BAR_HPP
#define UPPER_BAR_HPP

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>

class QStackedWidget;
class Biblioteca;

class UpperBar : public QWidget {
    Q_OBJECT

public:
    explicit UpperBar(Biblioteca *biblioteca = nullptr, QWidget *parent = nullptr);

private:

    Biblioteca *biblioteca;

    QComboBox *changeLayout;

    QComboBox *sortComboBox;

    QLineEdit *searchBar;

signals:
    void layoutChanged(int index);   

private slots:  
    void handleLayoutChange(int index);
};


#endif // UPPER_BAR_HPP