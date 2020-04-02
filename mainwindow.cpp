#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core.h"

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


void MainWindow::on_pushButton_clicked()
{
    // отримуємо випадкову кількість стовбців та рядків
    int count = randomBetween(1,12);

    // змінюємо значення компонентів на формі
    ui->lineEdit->setText(getRandom(count));
    ui->lineEdit_2->setText(getRandom(count));
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    buildTable(ui->lineEdit->text(),arg1);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    buildTable(arg1,ui->lineEdit_2->text());
}


// функція для перевірки чи є матриця квадратною
bool MainWindow::isSquare(QStringList input1, QStringList input2)
{
    // якщо в обох масивах однакова кількість елементів
    if (input1.length() == input2.length())
        return true;
    else
        return false;
}


// функція для побудови таблиці
void MainWindow::buildTable(QString input1, QString input2)
{

    returnState();
    // робимо два масиви
    QStringList inArr1 = input1.split(" ");
    QStringList inArr2 = input2.split(" ");

    if (inArr1[inArr1.length() - 1] == "")
        inArr1.removeAt(inArr1.length() - 1);
    if (inArr2[inArr2.length() - 1] == "")
        inArr2.removeAt(inArr2.length() - 1);

    // якщо матриця не квадратна
    if (!isSquare(inArr1, inArr2))
    {   // повідомлення про помилку
        ui->label_10->show();
        return;
    }
    ui->label_10->hide();
    // втсановлюємо розміри
    ui->tableWidget->setRowCount(inArr1.length());
    ui->tableWidget->setColumnCount(inArr1.length());
    // встановлюємо заголовки
    ui->tableWidget->setHorizontalHeaderLabels(inArr1);
    ui->tableWidget->setVerticalHeaderLabels(inArr2);
    // усього елементів
    int all = (inArr1.length()) * (inArr1.length());
    // проходимо через кожен елемент
    for (int i = 0; i < all;i++)
    {   // встановлюємо рядок і стовпець
        int row = i / (inArr1.length());
        int column = i % (inArr1.length());
        // встановлюємо значення
        QTableWidgetItem * item = new QTableWidgetItem(QString::number(compare(inArr1[column].toInt(),inArr2[row].toInt())));

        ui->tableWidget->setItem(row, column, item);
    }
    // змінюємо розміри таблиці
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();

    startTestCases();
}


// функція для порівняння
bool MainWindow::compare(int a, int b)
{
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A > B")
        return a > b;
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A >= B")
        return a >= b;
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A = B")
        return a == b;
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A MOD B = 0")
        return  (a % b == 0);
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A MOD 2 = 0 OR B MOD 2 = 0")
        return ((a%2==0) && (b %2 != 0)) || ((b%2==0) && (a%2 != 0));
    if ( ui->comboBox->itemText(ui->comboBox->currentIndex()) == "A MOD 2 = 0 AND B MOD 2 = 0")
        return ((a%2==0) && (b %2 == 0));
}


// Перевірка властивостей
void MainWindow::startTestCases()
{
    symmetrical();
    reflective();
    transitive();
    antireflecive();
    antisymmetric();
    asymmetric();
    linear();
    strictOrder();
    tolerance();
    equivalence();
}

// Повернення у початковий стан
void MainWindow::returnState()
{
    ui->label_3->setText("SYMMETRICAL");
    ui->label_4->setText("REFLECTIVE");
    ui->label_5->setText("TRANSITIVE");
    ui->label_6->setText("LINEAR");
    ui->label_7->setText("ANTIREFLEXIVE");
    ui->label_8->setText("ANTISYMMETRIC");
    ui->label_9->setText("ASYMMETRIC");
    ui->label_11->setText("EQUIVALENCE");
    ui->label_12->setText("TOLERANCE");
    ui->label_13->setText("STRICT ORDERING");
}


// Перевірка на симетричність
void MainWindow::symmetrical(){
    // отримуємо рядки і стовпці
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();

    for (int i=0; i<rows; i++)
    {
        for (int j=i; j<columns; j++)
        {   // якщо хоча б один не симетричний
            if (ui->tableWidget->item(i,j)->text() != ui->tableWidget->item(j,i)->text()){
                ui->label_3->setText(ui->label_3->text() + " - ");
                return;
            }
        }

    }
    ui->label_3->setText(ui->label_3->text() + " + ");
}

void MainWindow::reflective(){
    int rows = ui->tableWidget->rowCount();
    // проходимо по головній діагоналі
    for (int i=0; i<rows; i++){
        if(ui->tableWidget->item(i,i)->text()=="0"){
            ui->label_4->setText(ui->label_4->text() + " - ");return;
        }
    }
    ui->label_4->setText(ui->label_4->text() + " + ");
}

void MainWindow::transitive(){
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();
    for(int i = 0; i <columns; i++) {
        for(int j = 0; j < rows; j++) {
            if(ui->tableWidget->item(i,j)->text()=="1") {
                for(int g= 0; g < columns; g++) {
                    if(ui->tableWidget->item(j,g)->text()=="1"&& ui->tableWidget->item(i,g)->text()=="0") {
                        ui->label_5->setText(ui->label_5->text() + " - ");return;
                    }
                }
            }
        }
    }
    ui->label_5->setText(ui->label_5->text() + " + ");
}

void MainWindow::antireflecive(){
    int rows = ui->tableWidget->rowCount();

    // проходимо по головній діагоналі
    for (int i=0; i<rows; i++){
        if(ui->tableWidget->item(i,i)->text()=="1"){
            ui->label_7->setText(ui->label_7->text() + " - ");return;
        }
    }
    ui->label_7->setText(ui->label_7->text() + " + ");
}

void MainWindow::asymmetric(){
    // отримуємо рядки і стовпці
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++){
            if(i==j&&j==i){
                if(ui->tableWidget->item(i,j)->text()=="1"){
                    ui->label_9->setText(ui->label_9->text() + " - ");
                    return;
                }else continue;
            }else continue;

            if (ui->tableWidget->item(i,j)->text() != ui->tableWidget->item(j,i)->text()){
                ui->label_9->setText(ui->label_9->text() + " + ");
                return;
            }
        }
    }
    ui->label_9->setText(ui->label_9->text() + " + ");
}

void MainWindow::antisymmetric(){
    // отримуємо рядки і стовпці
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();

    // перевірка головної діагоналі. Якщо усі нулі - це асиметричне відношення. Виключаємо цей варіант.
    int n=0;
    for(int k=0;k<rows;k++){
        if(ui->tableWidget->item(k,k)->text()=="0"){
            n++;
        }
    }
    if(n==rows){
        ui->label_8->setText(ui->label_8->text() + " - ");
        return;
    }


    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++){
            if (ui->tableWidget->item(i,j)->text() != ui->tableWidget->item(j,i)->text() ){
                ui->label_8->setText(ui->label_8->text() + " + ");
                return;
            }
        }
    }
    ui->label_8->setText(ui->label_8->text() + " - ");
}


// перевірка на лінійність
void MainWindow::linear(){
    // якщо усі три вимоги виконуються
    if (ui->label_8->text() == "ANTISYMMETRIC + " && ui->label_5->text() == "TRANSITIVE + " && ui->label_4->text() == "REFLECTIVE + ")
        ui->label_6->setText(ui->label_6->text() + " + ");
    else
        ui->label_6->setText(ui->label_6->text() + " - ");
}


// перевірка на ЕКВІВАЛЕНТНІСТЬ
void MainWindow::equivalence(){
    // якщо усі три вимоги виконуються
    if (ui->label_4->text() == "REFLECTIVE + " && ui->label_3->text() == "SYMMETRICAL + " && ui->label_5->text() == "TRANSITIVE + ")
        ui->label_11->setText(ui->label_11->text() + " + ");
    else
        ui->label_11->setText(ui->label_11->text() + " - ");
}

// перевірка на толерантність
void MainWindow::tolerance(){
    // якщо усі вимоги виконуються
    if (ui->label_4->text() == "REFLECTIVE + " && ui->label_3->text() == "SYMMETRICAL + ")
        ui->label_12->setText(ui->label_12->text() + " + ");
    else
        ui->label_12->setText(ui->label_12->text() + " - ");
}


// перевірка на строгий порядок
void MainWindow::strictOrder(){
    // якщо усі три вимоги виконуються
    if (ui->label_8->text() == "ANTISYMMETRIC + " && ui->label_5->text() == "TRANSITIVE + " && ui->label_7->text() == "ANTIREFLEXIVE + ")
        ui->label_13->setText(ui->label_13->text() + " + ");
    else
        ui->label_13->setText(ui->label_13->text() + " - ");
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    buildTable(ui->lineEdit->text(),ui->lineEdit_2->text());
}
