#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "QtNetwork/qnetworkaccessmanager.h"
#include "QtNetwork/QtNetwork"
#include <QMainWindow>
#include "scorewall.h"
#include "qtimer.h"
#define PATH (QString)"/home/fred/Dropbox/Taf/Cassiopee/cybergame/files/"


#define NETWORK_OK 0
#define NETWORK_FAIL 1
#define NETWORK_NOUSER 2


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<scoreWall *> scoreWalls;
    std::vector<int>scores1,scores2;
    std::vector<QString>names1,names2;
    int requestData1(int level);
    int requestData2(int level);
private:

    Ui::MainWindow *ui;
    int currentLevel;
    QTimer *t0;
    void initNetwork();

    int postData(QString id,int gameId,int score,int attempt);
    QNetworkAccessManager  *manager;

private slots:
    void updateScores();
};

#endif // MAINWINDOW_H
