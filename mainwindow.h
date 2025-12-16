#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot/qcustomplot.h"
#include <QVector>

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
    void setLinearAxis();
    void setLogAxis();
    void openDataset();

private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;

    void setupPlot();
    void createMenu();
    void plotFromFile(const QString &filePath);
};

#endif // MAINWINDOW_H
