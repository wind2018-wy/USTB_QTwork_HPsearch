#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "searchwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_SearchStart_clicked()
{
    static SearchWindow serWin_0;
    QObject::connect(this,SIGNAL(showSerwin()),&serWin_0,SLOT(recv()));

    emit showSerwin();
}

