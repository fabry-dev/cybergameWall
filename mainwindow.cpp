#include "mainwindow.h"
#include "ui_mainwindow.h"





QStringList scores1 = QStringList() << "1''10''23"<<"1''40''12" << "1''42''09" <<"1''44''23"<<"2''47''18";
QStringList names1 = QStringList() << "login 1"<<"login 2"<<"login 3"<<"login 4"<<"login 5";

QStringList scores2 = QStringList() << "2''10''23"<<"2''40''12" << "2''42''09" <<"2''44''23"<<"3''47''18";
QStringList names2 = QStringList() << "login 6"<<"very long login for some reason"<<"login 8"<<"login 9"<<"login 10";


#define ROTATION 10


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initNetwork();
    setWindowState(Qt::WindowFullScreen);

    for (int i = 0;i<3;i++)
    {
        scoreWalls.push_back(new scoreWall(this,PATH+"leaderBoard"+QString::number(i+1)+".png",PATH+"Gotham-Book.otf"));

    }


    currentLevel = 1;

    requestData1(currentLevel);
    requestData2(currentLevel);





    updateScores();


    t0 = new QTimer(this);
    connect(t0,SIGNAL(timeout()),this,SLOT(updateScores()));
    t0->start(1000*ROTATION);

}


void MainWindow::updateScores()
{




    int previousLevel = currentLevel-1;


    if (previousLevel<1)
        previousLevel = 3;



    scoreWalls[currentLevel-1]->paintScores();
    scoreWalls[previousLevel-1]->goAway();



    currentLevel++;
    if(currentLevel>3)
        currentLevel = 1;
    requestData1(currentLevel);
    requestData2(currentLevel);


}

void MainWindow::initNetwork()
{
    manager = new QNetworkAccessManager();
}

int MainWindow::requestData1(int level)
{

    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);
    request.setUrl(QUrl("https://cyberquestevent2018.ae/game/top/scorer/1/"+QString::number(level)+"/"));

    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    connect(manager,SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();

    scores1.clear();
    names1.clear();


    if (reply->error()) {
        qDebug() << reply->errorString();

        return NETWORK_FAIL;
    }


    QString answer = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    int receptionOK=jsonObject["status_code"].toInt();

    if(not receptionOK)
    {
        qDebug()<<"get failure";
        return NETWORK_NOUSER;
    }
    QJsonArray results = jsonObject["result"].toArray();



    QJsonObject r1;
    QString name;
    int score;




    for(QJsonValue r:results)
    {

        r1 = r.toObject();

        name = r1["name"].toString();
        score = (r1["score_1"].toInt());
        names1.push_back(name);
        scores1.push_back(score);
    }

   // for (auto s:scores1)


    return NETWORK_OK;

}

int MainWindow::requestData2(int level)
{

    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);
    request.setUrl(QUrl("https://cyberquestevent2018.ae/game/top/scorer/2/"+QString::number(level)+"/"));

    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    connect(manager,SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();


    if (reply->error()) {
        qDebug() << reply->errorString();
        return NETWORK_FAIL;
    }


    QString answer = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    int receptionOK=jsonObject["status_code"].toInt();

    if(not receptionOK)
    {
        qDebug()<<"get failure";
        return NETWORK_NOUSER;
    }
    QJsonArray results = jsonObject["result"].toArray();
    QJsonObject r1;
    QString name;
    int score;
    scores2.clear();
    names2.clear();

    for(QJsonValue r:results)
    {
        r1 = r.toObject();
        name = r1["name"].toString();
        score = (r1["score_2"].toInt());
        names2.push_back(name);
        scores2.push_back(score);
    }


    return NETWORK_OK;

}


MainWindow::~MainWindow()
{
    delete ui;
}
