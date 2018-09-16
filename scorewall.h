#ifndef scoreWall_H
#define scoreWall_H


#include "qobject.h"
#include "qpainter.h"
#include "qlabel.h"
#include "qthread.h"
#include "qevent.h"
#include <QMouseEvent>
#include "qstringlist.h"
#include "QPropertyAnimation"




class scoreWall:public QLabel
{
    Q_OBJECT

public:
    scoreWall(QWidget *parent = 0,QString filename="",QString fontname="");
    ~scoreWall();
    void paintScores();
    void goAway();
protected:
    void mousePressEvent( QMouseEvent* ev );

private:
    QString filename;
    QString fontname;
    QPixmap* background;
    QFont font;
    QPropertyAnimation *appearance,*disappearance;


};








#endif // SPLASH_H
