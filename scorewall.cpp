#include "scorewall.h"
#include "qdebug.h"
#include "qtimer.h"
#include "mainwindow.h"
#include "QFont"
#include "qfontdatabase.h"

#include "qtoolbutton.h"

#define NAMEMAXSIZE 18

#define zeroScorex 198-20
#define zeroScore1y 829
#define deltaScorey 60

#define zeroScore2y 1353

scoreWall::scoreWall(QWidget *parent, QString filename,QString fontname):QLabel(parent),filename(filename),fontname(fontname)
{



    int id = QFontDatabase::addApplicationFont(fontname);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family,30);

    background = new QPixmap();




    this->resize(1080,1920);

    appearance = new QPropertyAnimation(this, "geometry");
    appearance->setDuration(600);
    appearance->setStartValue(QRect(0, -height(), width(),height()));
    appearance->setEndValue(QRect(0, 0, width(),height()));
    appearance->setEasingCurve(QEasingCurve::InCurve);


    disappearance = new QPropertyAnimation(this, "geometry");
    disappearance->setDuration(600);
    disappearance->setStartValue(QRect(0, 0, width(),height()));
    disappearance->setEndValue(QRect(0, height(), width(),height()));
    disappearance->setEasingCurve(QEasingCurve::InCurve);
    connect(disappearance,SIGNAL(finished()),this,SLOT(hide()));

}



void scoreWall::paintScores()
{

    background->load(filename);

    QPainter p1(background);

    p1.setPen(QPen(Qt::white));
    p1.setFont(font);



    QString score,name;
    for (int i = 0;i<((MainWindow*)parent())->names1.size();i++)
    {

        name = ((MainWindow*)parent())->names1[i];
        int t = ((MainWindow*)parent())->scores1[i];

        QString cs =  QString("%1").arg(t%100, 2, 10, QChar('0'));
        QString s =  QString("%1").arg((t/100)%60, 2, 10, QChar('0'));
        QString min =QString("%1").arg(t/6000, 2, 10, QChar('0'));
        score = min+":"+s+":"+cs;




        p1.drawText(QRect(zeroScorex,zeroScore1y+deltaScorey*i,1000,100), Qt::AlignLeft, QString::number(i+1)+". ");
        p1.drawText(QRect(zeroScorex+40,zeroScore1y+deltaScorey*i,560,100), Qt::AlignLeft, name);
        p1.drawText(QRect(zeroScorex+600,zeroScore1y+deltaScorey*i,200,100), Qt::AlignRight, score);
    }


    for (int i = 0;i<((MainWindow*)parent())->names2.size();i++)
    {
        name = ((MainWindow*)parent())->names2[i];




        score = QString::number(((MainWindow*)parent())->scores2[i]);
        p1.drawText(QRect(zeroScorex,zeroScore2y+deltaScorey*i,1000,100), Qt::AlignLeft, QString::number(i+1)+". ");
        p1.drawText(QRect(zeroScorex+40,zeroScore2y+deltaScorey*i,560,100), Qt::AlignLeft,name);
        p1.drawText(QRect(zeroScorex+600,zeroScore2y+deltaScorey*i,200,100), Qt::AlignRight, score);
    }


    this->setPixmap(*background);

    appearance->start();



    show();
}

void scoreWall::goAway()
{

    disappearance->start();

}





void scoreWall::mousePressEvent( QMouseEvent* ev )
{

    qDebug()<<ev->pos();
}



scoreWall::~scoreWall()
{


}


