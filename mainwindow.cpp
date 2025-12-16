#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QtMath>       // for qSin
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    customPlot = new QCustomPlot(this);
    setCentralWidget(customPlot);

    setupPlot();
    createMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Initial sine curve plot
void MainWindow::setupPlot()
{
    customPlot->addGraph();

    QVector<double> x(101), y(101);
    for (int i = 0; i < 101; ++i)
    {
        x[i] = i/10.0;
        y[i] = qSin(x[i]);
    }

    customPlot->graph(0)->setData(x, y);

    customPlot->xAxis->setLabel("X Axis");
    customPlot->yAxis->setLabel("Y Axis");

    customPlot->xAxis->setRange(0, 10);
    customPlot->yAxis->setRange(-1, 1);

    customPlot->xAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->grid()->setSubGridVisible(true);
}

// Menu creation
void MainWindow::createMenu()
{
    QMenu *axisMenu = menuBar()->addMenu("Axis");
    QAction *linearAction = new QAction("Linear", this);
    QAction *logAction = new QAction("Logarithmic", this);
    axisMenu->addAction(linearAction);
    axisMenu->addAction(logAction);
    connect(linearAction, &QAction::triggered, this, &MainWindow::setLinearAxis);
    connect(logAction, &QAction::triggered, this, &MainWindow::setLogAxis);

    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *loadAction = new QAction("Load Dataset", this);
    fileMenu->addAction(loadAction);
    connect(loadAction, &QAction::triggered, this, &MainWindow::openDataset); // NEW
}

// Axis slots
void MainWindow::setLinearAxis()
{
    customPlot->yAxis->setScaleType(QCPAxis::stLinear);
    customPlot->replot();
}

void MainWindow::setLogAxis()
{
    customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    customPlot->replot();
}

// Open dataset dialog
void MainWindow::openDataset()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Dataset", "data/", "Text Files (*.txt)");
    if (!fileName.isEmpty())
        plotFromFile(fileName);
}

// Load from .txt file and plot
void MainWindow::plotFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    QVector<double> x, y;

    if (!in.atEnd()) {
        QString firstLine = in.readLine().trimmed();
        QStringList parts = firstLine.split(',');
        bool ok1, ok2;
        firstLine = firstLine.trimmed();
        if (parts.size() >= 2) {
            parts[0].toDouble(&ok1);
            parts[1].toDouble(&ok2);
            if (!(ok1 && ok2)) {
                // First line is not numeric, skip as header
            } else {
                // First line is numeric, process it
                x.append(parts[0].toDouble());
                y.append(parts[1].toDouble());
            }
        }
    }

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList fields = line.split(',');
        if (fields.size() >= 2) {
            bool okX, okY;
            double xv = fields[0].toDouble(&okX);
            double yv = fields[1].toDouble(&okY);
            if (okX && okY) {
                x.append(xv);
                y.append(yv);
            }
        }
    }

    if (!customPlot->graphCount())
        customPlot->addGraph();

    customPlot->graph(0)->setData(x, y);

    customPlot->xAxis->rescale();
    customPlot->yAxis->rescale();
    customPlot->xAxis->setLabel("X Axis");
    customPlot->yAxis->setLabel("Y Axis");
    customPlot->replot();
}
