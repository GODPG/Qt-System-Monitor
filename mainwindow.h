#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QTimer>
#include <QStorageInfo>
#include <QSysInfo>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTableWidget>
#include <QHeaderView>
#include <QVector>
#include <algorithm>
#include <winsock2.h>
#include <iphlpapi.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_END_NAMESPACE
QT_BEGIN_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateStats();
    void on_btn_saveReport_clicked();
    void on_btn_refreshProc_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;

    QChart *m_chart;
    QLineSeries *m_cpuSeries;
    QLineSeries *m_memSeries;
    QLineSeries *m_diskSeries;
    QLineSeries *m_netSeries;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qint64 m_timeCounter;


    FILETIME m_preIdleTime, m_preKernelTime, m_preUserTime;
    DWORD m_preNetIn, m_preNetOut;


    quint64 fileTime2UQ(const FILETIME &ft);
    double getCpuUsage();
    double getMemoryUsage();
    double getDiskUsage();
    double getNetworkUsage();
    void addLog(const QString &message, bool isWarning = false);


    void refreshProcessList();
};

#endif
