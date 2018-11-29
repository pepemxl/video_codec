#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRect>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
//#include <QSqlDatabase>
//#include <QSqlQuery>
//#include <QSqlRecord>
//#include <QSqlField>
//#include <QSqlError>
#include <QEventLoop>
#include <QThread>
#include <QMutex>
//#include <QHostAddress>
//#include <QHostInfo>
//#include <QNetworkInterface>
#include <QMutableStringListIterator>
//#include <QVideoEncoderSettingsControl>
//#include <QMediaMetaData>
//#include <QMediaPlayer>
//#include <QtXlsx>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <ratio>
#include <iomanip>
#include <fstream>
#include <stack>
#include <string>
#include <thread>
#include <vector>
#include <exception>
#include <sys/time.h>
#include <mutex>

extern "C" {
#include <errno.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/pixdesc.h>
#include <libavutil/rational.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

#include <omp.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int numberOfVideos;
    int numberOfVideosIncorrect;
    FILE *fout;
    QMessageBox QMB_aviso;
    QMessageBox QMB_pregunta;
    std::string currentInputPath;
    std::string currentOutputPath;
    std::mutex mtx;
    QDir directoryIn;
    QStringList qslValidExtensions;
    QVector<QString> vectorShortFileNames;
    QVector<QString> vectorLongFileNames;
    QVector<QString> vectorExtension;
    QVector<QString> vectorCodec;
    QVector<QString> vectorCodecTag;
    QVector<QString> vectorCodecTag2;
    QVector<QString> vectorCodecName;
    QVector<QString> vectorCodecProfile;
    QVector<QString> vectorCodecDescription;
    QVector<bool> vectorStatusCorrect;
    std::vector<std::string> vectorParametros;
//    QMediaPlayer *mPlayer;
    char lista_parametros[10][200];
    bool flagProcessed;

    std::string getCurrentInputPath() const;
    void setCurrentInputPath(const std::string &value);

    std::string getCurrentOutputPath() const;
    void setCurrentOutputPath(const std::string &value);

    QDir getDirectoryIn() const;
    void setDirectoryIn(const QDir &value);

    void setValidExtensions();
    void clearVectors();
    void setPropertiesOnQTableWidget();
    void setLabelCurrentPathIn();
    //void GetMetaData(QMediaPlayer *player);
    QString getCodec(QString filename, QString *codec_tag, QString *codec_tag2, QString *codec_name, QString *codec_profile, QString *codec_description);
    QString getCodec(QString filename, char lista_parametros[10][200]);
    bool getFlagProcessed() const;
    void setFlagProcessed(bool value);

    int getNumberOfVideos() const;
    void setNumberOfVideos(int value);

    int getNumberOfVideosIncorrect() const;
    void setNumberOfVideosIncorrect(int value);

public slots:
    //void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
private slots:
    void on_pushButton_clicked();

    void on_pushButtonProcesar_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
