#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
 
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
 
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startRequest(const QUrl &requestedUrl);
 
private:
    Ui::MainWindow *ui;
 
private:
    // [3] 添加对象
    QUrl url;
    QNetworkRequest req;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
 
private slots:
//    void startRequest(const QUrl &requestedUrl);
    void replyFinished();
 
};
#endif // MAINWINDOW_H



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
 
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //调用函数发送请求，参数是请求的服务器地址
    startRequest( QUrl("http://127.0.0.1:8000/test"));
 
}
 
MainWindow::~MainWindow()
{
    delete ui;
}
 
void MainWindow::startRequest(const QUrl &requestedUrl){
    url = requestedUrl;
    manager = new QNetworkAccessManager(this);
    req.setUrl(url);
    //由于请求发生重定向，所以一定要加上这行代码，设置自动跳转，否则会返回 302
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
//    req.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
//    req.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
    //get方式发送请求
    reply = manager->get(req);
    //将服务器的返回信号与replyFinished槽连接起来，当服务器返回消息时，会在槽里做相应操作
    connect(reply,&QNetworkReply::finished,this,&MainWindow::replyFinished);
 
}
 
void MainWindow::replyFinished(){
 
    // <1>判断有没有错误
    if (reply->error()){
        qDebug()<<reply->errorString();
        reply->deleteLater();
        return;
    }
 
    // <2>检测网页返回状态码，常见是200，404等，200为成功
    int statusCode  = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "statusCode:" << statusCode;
 
    // <3>判断是否需要重定向
    if (statusCode >= 200 && statusCode <300){
        // ok
 
        // 准备读数据
        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QString all = codec->toUnicode(reply->readAll());
        qDebug() << "接收到的数据" <<all;
 
        //显示在mainwindow 测试，将服务器返回值打印至label上，服务器用的是mongoose模拟
        QLabel *label = new QLabel(this);
        label->setText(all);
        label->move(200,200);
        label->setVisible(true);
 
        // 数据读取完成之后，清除reply
        reply->deleteLater();
        reply = nullptr;
 
    } else if (statusCode >=300 && statusCode <400){
        // redirect
 
        // 获取重定向信息
        const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        // 检测是否需要重定向，如果不需要则读数据
        if (!redirectionTarget.isNull()) {
            const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
 
            reply->deleteLater();
            reply = nullptr;
 
            startRequest(redirectedUrl);
            qDebug()<< "http redirect to " << redirectedUrl.toString();
            return;
        }
    }
}