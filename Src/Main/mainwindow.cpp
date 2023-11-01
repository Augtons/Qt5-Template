#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->aboutBtn, &QPushButton::clicked, this, [this] {
        QMessageBox::aboutQt(this);
    });

    connect(ui->helloBtn, &QPushButton::clicked, this, [this] {
        static uint32_t count = 0;
        ui->helloLabel->setText(tr("Hello World, %1").arg(++count));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
