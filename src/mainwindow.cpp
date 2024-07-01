/*!
 * \file
 * \brief plik klasa MainWindow
 *
 * zawiera funkcje klasowe
 */
#include "../inc/mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QTextStream>
#include <QApplication>
/*#include <Qt3DExtras>
#include <Qt3DCore>
#include <Qt3DRender>*/

#define CRC8_INIT        0
#define CRC8_POLYNOMIAL  0x39

#define CRC16_INIT        0
#define CRC16_POLYNOMIAL  0x8005

#define CRC32_INIT        0
#define CRC32_POLYNOMIAL  0x04C11DB7


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);

    wyk = new Wykresy;
    wyk->set_XYZWykres(3);
    LabKulk = new Gra;
    LabKulk->set_Zlozonosc(1);
    translator = new QTranslator;

    for (int i=0; i<50; i++){
        daneX[i] = 0;
        daneY[i] = 0;
        daneZ[i] = 0;
    }

    //this->setWindowTitle("Ball Maze");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
        return;
    }
    QMainWindow::changeEvent(event);
}


void MainWindow::changeLanguage(const QString& language)
{
    QApplication::removeTranslator(translator);
    if (language == "pl"){
        if(translator->load("D:/c/0QT/LabiryntKulkowy/LabiryntKulkowy_pl_PL.qm")){
            qApp->installTranslator(translator);
        } else {
            qDebug() << "Plik 'LabiryntKulkowy_pl_PL.qm' nie zostal zaladowany";
        }
    } else if(language == "ru"){
        if(translator->load("D:/c/0QT/LabiryntKulkowy/LabiryntKulkowy_ru_RU.qm")){
            qApp->installTranslator(translator);
        } else {
            qDebug() << "Plik 'LabiryntKulkowy_ru_RU.qm' nie zostal zaladowany";
        }
    }
}

/**
 * \brief Oblicza CRC-16 dla danych.
 *
 * Funkcja oblicza cykliczną sumę kontrolną CRC-16 (Cyclic Redundancy Check)
 * dla podanych danych.
 *
 * \param pData - tablica znaków, dla których obliczane jest CRC.
 * \param Length - długość danych (w bajtach).
 * \param Poly - wielomian CRC-16 (np. 0x8005).
 * \param InitVal - początkowa wartość CRC-16.
 * \return Obliczona suma kontrolna CRC-16.
 */
unsigned short int ComputeCRC16(char* pData, int Length, unsigned int Poly, unsigned short int InitVal)
{
    unsigned short int ResCRC = InitVal;

    while (--Length >= 0) {
        ResCRC ^= *pData++ << 8;
        for (short int i=0; i < 8; ++i)
            ResCRC = ResCRC & 0x8000 ? (ResCRC << 1) ^ Poly : ResCRC << 1;
    }
    return ResCRC & 0xFFFF;
}

void MainWindow::readFromPort()
{
    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        //qDebug() << line;

        QTextStream ss(&line);
        char ch;
        int x, y, z, sumdane;
        int xsize=0, ysize=0, zsize=0;
        ss >> ch >> x >> y >> z >> sumdane;

        if(x < 0){
            ++xsize;
        }

        for (int i=abs(x); i>0; i/=10){
            ++xsize;
        }

        if(y < 0){
            ++ysize;
        }

        for (int i=abs(y); i>0; i/=10){
            ++ysize;
        }

        if(z < 0){
            ++zsize;
        }

        for (int i=abs(z); i>0; i/=10){
            ++zsize;
        }
        int danesize = xsize+ysize+zsize+4;
        char dane[danesize];
        sprintf(dane, "D %d %d %d", x, y, z);
        int sumCRC16 = ComputeCRC16(dane, danesize, CRC16_POLYNOMIAL, CRC16_INIT);

        if(ch == 'D' && sumCRC16 == sumdane){
            ui->lineEdit_1->setText(QString::number(x));
            ui->lineEdit_1->setAlignment(Qt::AlignRight);
            ui->lineEdit_2->setText(QString::number(y));
            ui->lineEdit_2->setAlignment(Qt::AlignRight);
            ui->lineEdit_3->setText(QString::number(z));
            ui->lineEdit_3->setAlignment(Qt::AlignRight);
            for(int i=0; i<49; i++){
                daneX[i] = daneX[i+1];
                daneY[i] = daneY[i+1];
                daneZ[i] = daneZ[i+1];
            }
            LabKulk->set_XY(x, y);
            daneX[49] = x;
            daneY[49] = y;
            daneZ[49] = z;
            wyk->set_dane(0, daneX);
            wyk->set_dane(1, daneY);
            wyk->set_dane(2, daneZ);
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    this->addToLogs("Szukam urządzeń...");
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    for(int i = 0; i < devices.count(); i++) {
        this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + "\t" + devices.at(i).description());
        ui->comboBox->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
}

void MainWindow::addToLogs(const QString& message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEdit->append(currentDateTime + "\t" + message);
}


void MainWindow::on_pushButton_5_clicked()
{
    if(ui->comboBox->count() == 0) {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }

    QString portName = ui->comboBox->currentText().split("\t").first();
    this->device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if(!device->isOpen()) {
        if(device->open(QSerialPort::ReadWrite)) {
        this->device->setBaudRate(QSerialPort::Baud115200);
        this->device->setDataBits(QSerialPort::Data8);
        this->device->setParity(QSerialPort::NoParity);
        this->device->setStopBits(QSerialPort::OneStop);
        this->device->setFlowControl(QSerialPort::NoFlowControl);

        this->addToLogs("Otwarto port szeregowy.");
        connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
    } else {
        this->addToLogs("Otwarcie porty szeregowego się nie powiodło!");
    }
    } else {
        this->addToLogs("Port już jest otwarty!");
        return;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if(this->device->isOpen()) {
        this->device->close();
        ui->lineEdit_1->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        this->addToLogs("Zamknięto połączenie.");
    } else {
        this->addToLogs("Port nie jest otwarty!");
        return;
    }
}


void MainWindow::on_actionWykres_X_triggered()
{
    wyk->set_XYZWykres(0);
    wyk->show();
}


void MainWindow::on_actionWykres_Y_triggered()
{
    wyk->set_XYZWykres(1);
    wyk->show();
}


void MainWindow::on_actionWykres_Z_triggered()
{
    wyk->set_XYZWykres(2);
    wyk->show();
}


void MainWindow::on_actionWykres_XYZ_triggered()
{
    wyk->set_XYZWykres(3);
    wyk->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    on_pushButton_6_clicked();
    if (wyk->isVisible()){
        wyk->close();
    }
    if (LabKulk->isVisible()){
        LabKulk->close();
    }
    close();
}


void MainWindow::on_pushButton_clicked()
{
    LabKulk->zapolni();
    LabKulk->StartPosition();
    LabKulk->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    if(LabKulk->isVisible()){
        LabKulk->close();
        LabKulk->StartPosition();
        LabKulk->show();
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    wyk->show();
}


void MainWindow::on_actionLabirynt_triggered()
{
    on_pushButton_clicked();
}


void MainWindow::on_actionUproszczona_triggered()
{
    LabKulk->set_Zlozonosc(0);
}


void MainWindow::on_actionStandardowa_triggered()
{
    LabKulk->set_Zlozonosc(1);
}


void MainWindow::on_actionZaawansowana_triggered()
{
    LabKulk->set_Zlozonosc(2);
}


void MainWindow::on_actionPolski_triggered()
{
    changeLanguage("pl");
    wyk->changeLanguage("pl");
    LabKulk->changeLanguage("pl");
}


void MainWindow::on_actionEnglish_triggered()
{
    changeLanguage("en");
    wyk->changeLanguage("en");
    LabKulk->changeLanguage("en");
}


void MainWindow::on_action_triggered()
{
    changeLanguage("ru");
    wyk->changeLanguage("ru");
    LabKulk->changeLanguage("ru");
}

