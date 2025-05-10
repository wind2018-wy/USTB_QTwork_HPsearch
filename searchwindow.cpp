#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QString>
#include <fstream>
#include <QDebug>

SearchWindow::SearchWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}
void SearchWindow::recv(){
    this->show();
}

void SearchWindow::on_Butt_goalWord_clicked()
{
    QString s=ui->goalWord->text();
    ui->goalWordShow->append("查找词条 "+s+":");
    std::fstream tLine;
    tLine.open("HP0.txt",std::ios::in);
    if(!tLine.is_open()){
        qDebug()<<"文件打开失败";
    }
    char buf[1024];
    while (tLine.getline(buf,sizeof(buf))){
        ui->goalWordShow->append(QString::fromStdString(buf));
    }
}
