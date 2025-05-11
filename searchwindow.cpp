#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QString>
#include <fstream>
#include <QDebug>
#include "data.h"
#include <string>
#include "tool.h"

Data da;
Tool tool;
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
/*
    clock_t startTime,endTime;        测试查找时间
    startTime = clock();
*/
    QString s=ui->goalWord->text();
    ui->goalWordShow->append("查找词条 "+s+":");
    std::fstream tLine;
    std::string lineBook[8]={"J.K.Rowling - HP 0 - Harry Potter Prequel.txt","J.K. Rowling - Quidditch Through the Ages.txt","HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt","J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt","J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire.txt","J.K. Rowling - The Tales of Beedle the Bard.txt","J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince.txt","HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_.txt"};

    for(int i=0;i<8;i++){
        tLine.open(lineBook[i],std::ios::in);
        da.BookName=lineBook[i];
        if(!tLine.is_open()){
            qDebug()<<"文件打开失败";
        }
        std::string buf;
        std::string strs=s.toStdString();
        int length=0;

        while (std::getline(tLine,buf)){
            da.Line++;
            length=buf.length();
            if(length>0&&length<=20&&(tool.search("CHAPTER",buf)||tool.search("Chapter",buf))){
                da.Chapter++;
            }
            if(length>0&&length<=4&&tool.isNumber(length,buf)){
                da.Page=std::stoi(buf)+1;
            }
            if(tool.search(strs,buf)){
                da.No++;
                QString qNo=QString::number(da.No);
                QString qPage=QString::number(da.Page);
                QString qChapter=QString::number(da.Chapter);
                std::string stdLineBook=lineBook[i].substr(0,lineBook[i].length()-5);
                QString qStdLineBook=QString::fromStdString(stdLineBook);
                ui->goalWordShow->append("NO:"+qNo+" name:"+s+" page:"+qPage+" chapter:"+qChapter+" bookName:"+qStdLineBook);
            }
        }
        tLine.close();
        da.reset();
    }
/*
    endTime = clock();
    double tempp=(double)(endTime- startTime) /CLOCKS_PER_SEC;
    ui->debugShow->append( "Totle Time : "+QString::number(tempp)+ "s" );
*/
    da.No=0;
}
void SearchWindow::on_Butt_goalNo_clicked()
{
    /*
    clock_t startTime,endTime;        测试查找时间
    startTime = clock();
    */
    QString text =ui->noInPut->toPlainText();
    bool ok;
    int tnumber = text.toInt(&ok);

    if (ok) {
        qDebug() << "转换成功，数字是:" << tnumber;
    } else {
        qDebug() << "转换失败，输入不是有效的整数";
        return;
    }
    QString s=ui->goalWord->text();
    ui->debugShow->append("查找第"+QString::number(tnumber)+"个词条" +s+":");
    std::fstream tLine;
    std::string lineBook[8]={"J.K.Rowling - HP 0 - Harry Potter Prequel.txt","J.K. Rowling - Quidditch Through the Ages.txt","HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt","J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt","J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire.txt","J.K. Rowling - The Tales of Beedle the Bard.txt","J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince.txt","HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_.txt"};

    bool okk=false,okkNextPara=false;
    for(int i=0;i<8;i++){
        tLine.open(lineBook[i],std::ios::in);
        da.BookName=lineBook[i];
        if(!tLine.is_open()){
            qDebug()<<"文件打开失败";
        }
        std::string buf;
        std::string strs=s.toStdString();
        int length=0;
        std::string foreLine="";
        int foreSet=1;

        while (std::getline(tLine,buf)){
            if(okk){
                if(buf.length()>3&&buf.substr(0,7)!="Chapter"&&buf.substr(0,7)!="CHAPTER"){
                    ui->debugShow->append("这是目标段的下一段:\n"+QString::fromStdString(buf));
                    okkNextPara=true;
                    break;
                }
                else{
                    continue;
                }
            }
            length=buf.length();

            if(length>0&&length<=4&&tool.isNumber(length,buf)){
                da.Page=std::stoi(buf)+1;
            }
            if(tool.search(strs,buf)){
                da.No++;
                QString qNo=QString::number(da.No);
                std::string stdLineBook=lineBook[i].substr(0,lineBook[i].length()-5);
                QString qStdLineBook=QString::fromStdString(stdLineBook);
                if(foreLine.length()==0&&da.Page==1&&da.No==tnumber){
                    ui->debugShow->append("目标段即为本书第一段\n这是目标段:\n"+QString::fromStdString(buf));
                    okk=true;
                }
                else{
                    if(foreLine.length()!=0&&da.No==tnumber){
                        ui->debugShow->append("这是目标段的上一段:\n"+QString::fromStdString(foreLine)+"\n这是目标段:\n"+QString::fromStdString(buf));
                        okk=true;
                    }
                }
            }
            if(buf.length()>3&&buf.substr(0,7)!="Chapter"&&buf.substr(0,7)!="CHAPTER"){
                foreLine=buf;
            }
        }
        if(okk){
            if(!okkNextPara){
                ui->debugShow->append("目标段即为本书最后一段");
            }
            break;
        }
        tLine.close();
        da.reset();
    }
    /*
    endTime = clock();
    double tempp=(double)(endTime- startTime) /CLOCKS_PER_SEC;
    ui->debugShow->append( "Totle Time : "+QString::number(tempp)+ "s" );
    */
    da.No=0;
}
