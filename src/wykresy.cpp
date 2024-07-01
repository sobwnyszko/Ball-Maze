/*!
 * \file
 * \brief plik klasa Wykresy
 *
 * zawiera funkcje klasowe
 */
#include "../inc/wykresy.h"
#include "ui_wykresy.h"
#include <QTranslator>

Wykresy::Wykresy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Wykresy)
{
    ui->setupUi(this);

    lineSeriesX = new QLineSeries();
    lineSeriesY = new QLineSeries();
    lineSeriesZ = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(this);

    chart->legend()->hide();
    chart->addSeries(lineSeriesX);
    lineSeriesX->setColor(QColor(140, 0, 0));
    chart->addSeries(lineSeriesY);
    lineSeriesY->setColor(QColor(0, 140, 0));
    chart->addSeries(lineSeriesZ);
    lineSeriesZ->setColor(QColor(0, 0, 140));
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-32000, 32000);
    ui->comboBox_2->setCurrentIndex(1);
    chart->axes(Qt::Horizontal).first()->setRange(0, 50);
    chart->setBackgroundBrush(QColor(222, 184, 135));
    //chart->setTitleBrush(QBrush(Qt::white));
    chart->setVisible(true);

    chartView->setChart(chart);
    chartView->setFixedSize(800, 500);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setVisible(true);

    translator = new QTranslator;

    //this->setWindowTitle("Chart");
}


Wykresy::~Wykresy()
{
    delete ui;
}


void Wykresy::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
        return;
    }
    QMainWindow::changeEvent(event);
}


void Wykresy::changeLanguage(const QString& language)
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


void Wykresy::set_XYZWykres(int CoZaWykres)
{
    XYZWykres = CoZaWykres;
    if (CoZaWykres == 0){
        ui->comboBox->setCurrentIndex(0);
    }
    if (CoZaWykres == 1){
        ui->comboBox->setCurrentIndex(1);
    }
    if (CoZaWykres == 2){
        ui->comboBox->setCurrentIndex(2);
    }
    if (CoZaWykres == 3){
        ui->comboBox->setCurrentIndex(3);
    }
}

void Wykresy::set_dane(int CoZaWykres, int *dane)
{
    if (CoZaWykres == 0){
        for (int i=0; i<50; i++){
            daneX[i] = dane[i];
        }
    }
    if (CoZaWykres == 1){
        for (int i=0; i<50; i++){
            daneY[i] = dane[i];
        }
    }
    if (CoZaWykres == 2){
        for (int i=0; i<50; i++){
            daneZ[i] = dane[i];
        }
    }
    rysuj();
}

void Wykresy::rysuj()
{
    lineSeriesX->clear();
    lineSeriesY->clear();
    lineSeriesZ->clear();

    if (XYZWykres == 0 || XYZWykres == 3){
        for (int i=0; i<50; i++){
            lineSeriesX->append(i, daneX[i]);
        }
    }
    if (XYZWykres == 1 || XYZWykres == 3){
        for (int i=0; i<50; i++){
            lineSeriesY->append(i, daneY[i]);
        }
    }
    if (XYZWykres == 2 || XYZWykres == 3){
        for (int i=0; i<50; i++){
            lineSeriesZ->append(i, daneZ[i]);
        }
    }
}


void Wykresy::resizeEvent(QResizeEvent *event)
{
    QSize windowSize = size();
    chartView->setFixedSize(windowSize.width(), windowSize.height()-50);
}


void Wykresy::on_pushButton_clicked()
{
    close();
}


void Wykresy::on_comboBox_2_activated(int index)
{
    if (index == 0){
        chart->axes(Qt::Vertical).first()->setRange(-16000, 16000);
    } else if (index == 1){
        chart->axes(Qt::Vertical).first()->setRange(-32000, 32000);
    }
}


void Wykresy::on_comboBox_currentIndexChanged(int index)
{
    XYZWykres = index;
}

