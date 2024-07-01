/*!
 * \file
 * \brief plik klasa Gra
 *
 * zawiera funkcje klasowe
 */
#include "../inc/gra.h"
#include "ui_gra.h"

#include <QMessageBox>
#include <QTranslator>

int checkX;
int checkY;

Gra::Gra(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gra)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gra::graj);

    translator = new QTranslator;

    //this->setWindowTitle("Game");
}

Gra::~Gra()
{
    delete ui;
}

void Gra::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
        return;
    }
    QMainWindow::changeEvent(event);
}


void Gra::changeLanguage(const QString& language)
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


void Gra::set_Zlozonosc(int zlozon)
{
    if (Zlozonosc != zlozon){
        Zlozonosc = zlozon;
        ui->comboBox->setCurrentIndex(zlozon);
        StartPosition();
        repaint();
    }
}

void Gra::zapolni()
{
    for (int i=0; i<641; i++){
        for (int j=0; j<801; j++){
            bitMap[i][j]=0;
            if(i == 0){
                bitMap[i][j]=1;
            }
            if(i == 80 && ((j>=0 && j<=160) || (j>=480 && j<=640))){
                bitMap[i][j]=1;
            }
            if(i == 160 && ((j>=0 && j<=80) || (j>=400 && j<=720))){
                bitMap[i][j]=1;
            }
            if(i == 240 && ((j>=240 && j<=400) || (j>=560 && j<=800))){
                bitMap[i][j]=1;
            }
            if(i == 320 && ((j>=80 && j<=160) || (j>=480 && j<=560) || (j>=640 && j<=720))){
                bitMap[i][j]=1;
            }
            if(i == 400 && ((j>=0 && j<=240) || (j>=320 && j<=400) || (j>=560 && j<=720))){
                bitMap[i][j]=1;
            }
            if(i == 480 && ((j>=160 && j<=240) || (j>=400 && j<=480))){
                bitMap[i][j]=1;
            }
            if(i == 560 && ((j>=80 && j<=160) || (j>=240 && j<=320) || (j>=400 && j<=480) || (j>=720 && j<=800))){
                bitMap[i][j]=1;
            }
            if(i == 640){
                bitMap[i][j]=1;
            }
            if(j == 0 && ((i>=0 && i<=80) || (i>=160 && i<=640))){
                bitMap[i][j]=1;
            }
            if(j == 80 && ((i>=160 && i<=320) || (i>=480 && i<=640))){
                bitMap[i][j]=1;
            }
            if(j == 160 && (i>=80 && i<=240)){
                bitMap[i][j]=1;
            }
            if(j == 240 && ((i>=80 && i<=240) || (i>=320 && i<=400) || (i>=480 && i<=560))){
                bitMap[i][j]=1;
            }
            if(j == 320 && ((i>=0 && i<=160) || (i>=240 && i<=560))){
                bitMap[i][j]=1;
            }
            if(j == 400 && ((i>=80 && i<=160) || (i>=320 && i<=480) || (i>=560 && i<=640))){
                bitMap[i][j]=1;
            }
            if(j == 480 && ((i>=0 && i<=80) || (i>=160 && i<=400))){
                bitMap[i][j]=1;
            }
            if(j == 560 && (i>=320 && i<=560)){
                bitMap[i][j]=1;
            }
            if(j == 640 && (i>=480 && i<=640)){
                bitMap[i][j]=1;
            }
            if(j == 720 && ((i>=80 && i<=160) || (i>=320 && i<=400) || (i>=480 && i<=560))){
                bitMap[i][j]=1;
            }
            if(j == 800 && (i>=0 && i<=560)){
                bitMap[i][j]=1;
            }
        }
    }
}

void Gra::paintEvent(QPaintEvent *event)
{
    int strzalkaX = 40;
    int strzalkaY = 170;

    QPainter paint(this);
    QPen piorko = paint.pen();

    paint.fillRect(rect(), QColor(53, 53, 53));

    piorko.setWidth(2);
    piorko.setColor(QColor(200, 0, 0));
    paint.setPen(piorko);
    paint.drawLine(strzalkaX, strzalkaY, strzalkaX+60, strzalkaY);
    paint.drawLine(strzalkaX+60, strzalkaY, strzalkaX+45, strzalkaY-15);
    paint.drawLine(strzalkaX+60, strzalkaY, strzalkaX+45, strzalkaY+15);

    strzalkaX = 800;
    strzalkaY = 650;
    piorko.setColor(QColor(0, 0, 230));
    paint.setPen(piorko);
    paint.drawLine(strzalkaX, strzalkaY, strzalkaX+60, strzalkaY);
    paint.drawLine(strzalkaX+60, strzalkaY, strzalkaX+45, strzalkaY-15);
    paint.drawLine(strzalkaX+60, strzalkaY, strzalkaX+45, strzalkaY+15);

    if (Zlozonosc == 2){
        paint.setBrush(QColor(150, 150, 150));
        paint.setPen(Qt::NoPen);
        paint.drawRect( 50,  50,  80,  80);
        paint.drawRect( 50, 210,  80,  80);
        paint.drawRect( 50, 610, 160,  80);
        paint.drawRect(290, 530,  80,  80);
        paint.drawRect(370, 370,  80, 160);
        paint.drawRect(450, 610,  80,  80);
        paint.drawRect(530,  50,  80,  80);
        paint.drawRect(530, 370,  80,  80);
        paint.drawRect(690, 370,  80,  80);
        paint.drawRect(770, 530,  80,  80);
    }

    for (int i=0; i<2; i++){
        if (i == 0){
            piorko.setWidth(8);
            piorko.setColor(QColor(0,0,0));
        } else {
            piorko.setWidth(1);
            piorko.setColor(QColor(0,200,0));
        }
        paint.setPen(piorko);
        paint.drawLine(50,  50,  850,  50);
        paint.drawLine(50,  690, 860, 690);
        paint.drawLine(850, 50,  850, 610);
        paint.drawLine(50,  50,   50, 130);
        paint.drawLine(50,  210,  50, 690);

        paint.drawLine(130, 210, 130, 370);
        paint.drawLine(130, 530, 130, 690);
        paint.drawLine(210, 130, 210, 290);
        paint.drawLine(290, 130, 290, 290);
        paint.drawLine(290, 370, 290, 450);
        paint.drawLine(290, 530, 290, 610);
        paint.drawLine(370, 50,  370, 210);
        paint.drawLine(370, 290, 370, 610);
        paint.drawLine(450, 130, 450, 210);
        paint.drawLine(450, 370, 450, 530);
        paint.drawLine(450, 610, 450, 690);
        paint.drawLine(530, 50,  530, 130);
        paint.drawLine(530, 210, 530, 450);
        paint.drawLine(610, 370, 610, 610);
        paint.drawLine(690, 530, 690, 690);
        paint.drawLine(770, 130, 770, 210);
        paint.drawLine(770, 370, 770, 450);
        paint.drawLine(770, 530, 770, 610);


        paint.drawLine(40,  130, 210, 130);
        paint.drawLine(530, 130, 690, 130);
        paint.drawLine(40,  210, 130, 210);
        paint.drawLine(450, 210, 770, 210);
        paint.drawLine(290, 290, 450, 290);
        paint.drawLine(610, 290, 850, 290);
        paint.drawLine(130, 370, 210, 370);
        paint.drawLine(530, 370, 610, 370);
        paint.drawLine(690, 370, 770, 370);
        paint.drawLine(50,  450, 290, 450);
        paint.drawLine(370, 450, 450, 450);
        paint.drawLine(610, 450, 770, 450);
        paint.drawLine(210, 530, 290, 530);
        paint.drawLine(450, 530, 530, 530);
        paint.drawLine(130, 610, 210, 610);
        paint.drawLine(290, 610, 370, 610);
        paint.drawLine(450, 610, 530, 610);
        paint.drawLine(770, 610, 860, 610);
    }

    paint.setBrush(QColor(0, 200, 0));
    paint.setRenderHint(QPainter::Antialiasing);
    paint.setPen(Qt::NoPen);
    paint.drawEllipse(QPoint(currentX, currentY), 10, 10);
}

void Gra::on_pushButton_clicked()
{
    timer->stop();
    close();
}

void Gra::victory()
{
    QMessageBox::about(this, QObject::tr("Victory"), QObject::tr("Udało się przejść labirynt"));
}

void Gra::lose()
{
    QMessageBox::warning(this, QObject::tr("Game lose"), QObject::tr("Wyjście za przedziały"));
}

void Gra::sprawdzStatus()
{
    switch (Status) {
        case 1:{
            timer->stop();
            victory();
            break;
        }
        case 2:{
            timer->stop();
            lose();
            break;
        }
    }
}

bool Gra::collision(QString strona)
{
    bool status = true;
    int start, stop;
    if (strona == "up"){
        start = 220;
        stop = 320;
    }
    if (strona == "down"){
        start = 40;
        stop = 140;
    }
    if (strona == "left"){
        start = 130;
        stop = 230;
    }
    if (strona == "right"){
        start = -50;
        stop = 50;
    }
    for (int r=15; r>0; r--){
        for (int angle = start; angle <= stop; ++angle) {
            double rad = angle * M_PI / 180.0;
            checkX = currentX-50 + r * std::cos(rad);
            checkY = currentY-50 + r * std::sin(rad);

            if (checkX>=0 && checkY>=0 && checkX<=800 && checkY<=640){
                if (bitMap[checkY][checkX]==1){
                    status = false;
                    break;
                }
            }
        }
        if(status == false){
            break;
        }
    }
    return status;
}

void Gra::versjaUproszczona()
{
    if (plytkaX>4000){
        if(collision("up")){
            currentY-=2;
        }
    }
    if (plytkaX<-4000){
        if(collision("down")){
            currentY+=2;
        }
    }
    if (plytkaY<-4000){
        if(collision("left")){
            currentX-=2;
        }
    }
    if (plytkaY>4000){
        if(collision("right")){
            currentX+=2;
        }
    }
}

void Gra::versjaStandartowa()
{
    if (plytkaX>2000){
        Vy-=2;
    }
    if (plytkaX<-2000){
        Vy+=2;
    }
    if (plytkaY<-2000){
        Vx-=2;
    }
    if (plytkaY>2000){
        Vx+=2;
    }

    if (Vy<0){
        if (Vy<-10){Vy=-9;}
        Vy++;
        if(collision("up")){
            currentY+=Vy;
        } else {
            Vy = -Vy;
        }
    }
    if (Vy>0){
        if (Vy>10){Vy=9;}
        Vy--;
        if(collision("down")){
            currentY+=Vy;
        } else {
            Vy = -Vy;
        }
    }
    if (Vx<0){
        if (Vx<-10){Vx=-9;}
        Vx++;
        if(collision("left")){
            currentX+=Vx;
            } else {
            Vx = -Vx;
        }
    }
    if (Vx>0){
        if (Vx>10){Vx=9;}
        Vx--;
        if(collision("right")){
            currentX+=Vx;
        } else {
            Vx = -Vx;
        }
    }
}

void Gra::versjaZaawansowana()
{

    versjaStandartowa();

    if (currentX>50 && currentX<130 && currentY>50 && currentY<130){
        Status = 2;
    }
    if (currentX>50 && currentX<130 && currentY>210 && currentY<290){
        Status = 2;
    }
    if (currentX>50 && currentX<210 && currentY>610 && currentY<690){
        Status = 2;
    }
    if (currentX>290 && currentX<370 && currentY>530 && currentY<610){
        Status = 2;
    }
    if (currentX>370 && currentX<450 && currentY>370 && currentY<530){
        Status = 2;
    }
    if (currentX>450 && currentX<530 && currentY>610 && currentY<690){
        Status = 2;
    }
    if (currentX>530 && currentX<610 && currentY>50 && currentY<130){
        Status = 2;
    }
    if (currentX>530 && currentX<610 && currentY>370 && currentY<450){
        Status = 2;
    }
    if (currentX>690 && currentX<770 && currentY>370 && currentY<450){
        Status = 2;
    }
    if (currentX>770 && currentX<850 && currentY>530 && currentY<610){
        Status = 2;
    }
}

void Gra::graj()
{
    switch (Zlozonosc) {
        case 0:{
            versjaUproszczona();
            break;
        }
        case 1:{
            versjaStandartowa();
            break;
        }
        case 2:{
            versjaZaawansowana();
            break;
        }
    }

    repaint();
    if (currentX<45){
        Status = 2;
    }
    if (currentX>860){
        Status = 1;
    }
    sprawdzStatus();
}

void Gra::on_pushButton_3_clicked()
{
    if (Status == 1 || Status == 2){
        StartPosition();
    }
    timer->start(15);
}


void Gra::on_pushButton_2_clicked()
{
    timer->stop();
}


void Gra::on_comboBox_activated(int index)
{
    if (Zlozonosc != index){
        Zlozonosc = index;
        StartPosition();
        repaint();
    }
}

