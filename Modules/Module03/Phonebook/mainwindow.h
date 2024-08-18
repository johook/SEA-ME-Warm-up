#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>
#include "contact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void AddContact(); // Function for the adding contact.
    void SearchContact(); // Function for the searching contact.
    void RemoveContact(); // Function for the Removing contact.



private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QVector<Contact> contacts; // Contact Vector(list).

    void UpdateTableView(); // Fuction for the updating contact, because of the RemoveContact.
};
#endif // MAINWINDOW_H
