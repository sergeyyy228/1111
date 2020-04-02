#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    bool isSquare(QStringList input1, QStringList input2);


    void buildTable(QString input1, QString input2);

    bool compare(int a, int b);

    void symmetrical();

    void  reflective();

    void transitive();

    void linear();

    void antisymmetric();

    void asymmetric();

    void startTestCases();

    void returnState();

    void antireflecive();

    void strictOrder();

    void tolerance();

    void equivalence();
};
#endif // MAINWINDOW_H
