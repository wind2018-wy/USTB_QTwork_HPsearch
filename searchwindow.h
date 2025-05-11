#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

private slots:
    void recv();

    void on_Butt_goalWord_clicked();

    void on_Butt_goalNo_clicked();

    void on_Butt_clear_clicked();

private:
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
