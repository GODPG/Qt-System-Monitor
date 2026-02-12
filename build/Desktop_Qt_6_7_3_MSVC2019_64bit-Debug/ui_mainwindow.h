/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_root;
    QGroupBox *groupBox_info;
    QHBoxLayout *horizontalLayout_info;
    QLabel *label_os_info;
    QTabWidget *tabWidget;
    QWidget *tab_dashboard;
    QVBoxLayout *verticalLayout_main;
    QHBoxLayout *horizontalLayout_cpu;
    QLabel *label;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_mem;
    QLabel *label_2;
    QProgressBar *progressBar_2;
    QHBoxLayout *horizontalLayout_disk;
    QLabel *label_disk;
    QProgressBar *progressBar_disk;
    QHBoxLayout *horizontalLayout_net;
    QLabel *label_net;
    QProgressBar *progressBar_net;
    QFrame *line;
    QVBoxLayout *verticalLayout_chart;
    QFrame *line_2;
    QLabel *label_log;
    QTextEdit *textEdit_log;
    QWidget *tab_processes;
    QVBoxLayout *verticalLayout_proc;
    QLabel *label_proc_title;
    QTableWidget *tableWidget_proc;
    QPushButton *btn_refreshProc;
    QPushButton *btn_saveReport;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1050, 850);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_root = new QVBoxLayout(centralwidget);
        verticalLayout_root->setObjectName("verticalLayout_root");
        groupBox_info = new QGroupBox(centralwidget);
        groupBox_info->setObjectName("groupBox_info");
        horizontalLayout_info = new QHBoxLayout(groupBox_info);
        horizontalLayout_info->setObjectName("horizontalLayout_info");
        label_os_info = new QLabel(groupBox_info);
        label_os_info->setObjectName("label_os_info");
        label_os_info->setAlignment(Qt::AlignCenter);

        horizontalLayout_info->addWidget(label_os_info);


        verticalLayout_root->addWidget(groupBox_info);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab_dashboard = new QWidget();
        tab_dashboard->setObjectName("tab_dashboard");
        verticalLayout_main = new QVBoxLayout(tab_dashboard);
        verticalLayout_main->setObjectName("verticalLayout_main");
        horizontalLayout_cpu = new QHBoxLayout();
        horizontalLayout_cpu->setObjectName("horizontalLayout_cpu");
        label = new QLabel(tab_dashboard);
        label->setObjectName("label");
        label->setMinimumSize(QSize(110, 0));

        horizontalLayout_cpu->addWidget(label);

        progressBar = new QProgressBar(tab_dashboard);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        horizontalLayout_cpu->addWidget(progressBar);


        verticalLayout_main->addLayout(horizontalLayout_cpu);

        horizontalLayout_mem = new QHBoxLayout();
        horizontalLayout_mem->setObjectName("horizontalLayout_mem");
        label_2 = new QLabel(tab_dashboard);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(110, 0));

        horizontalLayout_mem->addWidget(label_2);

        progressBar_2 = new QProgressBar(tab_dashboard);
        progressBar_2->setObjectName("progressBar_2");
        progressBar_2->setValue(0);

        horizontalLayout_mem->addWidget(progressBar_2);


        verticalLayout_main->addLayout(horizontalLayout_mem);

        horizontalLayout_disk = new QHBoxLayout();
        horizontalLayout_disk->setObjectName("horizontalLayout_disk");
        label_disk = new QLabel(tab_dashboard);
        label_disk->setObjectName("label_disk");
        label_disk->setMinimumSize(QSize(110, 0));

        horizontalLayout_disk->addWidget(label_disk);

        progressBar_disk = new QProgressBar(tab_dashboard);
        progressBar_disk->setObjectName("progressBar_disk");
        progressBar_disk->setValue(0);

        horizontalLayout_disk->addWidget(progressBar_disk);


        verticalLayout_main->addLayout(horizontalLayout_disk);

        horizontalLayout_net = new QHBoxLayout();
        horizontalLayout_net->setObjectName("horizontalLayout_net");
        label_net = new QLabel(tab_dashboard);
        label_net->setObjectName("label_net");
        label_net->setMinimumSize(QSize(110, 0));

        horizontalLayout_net->addWidget(label_net);

        progressBar_net = new QProgressBar(tab_dashboard);
        progressBar_net->setObjectName("progressBar_net");
        progressBar_net->setValue(0);

        horizontalLayout_net->addWidget(progressBar_net);


        verticalLayout_main->addLayout(horizontalLayout_net);

        line = new QFrame(tab_dashboard);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_main->addWidget(line);

        verticalLayout_chart = new QVBoxLayout();
        verticalLayout_chart->setObjectName("verticalLayout_chart");

        verticalLayout_main->addLayout(verticalLayout_chart);

        line_2 = new QFrame(tab_dashboard);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_main->addWidget(line_2);

        label_log = new QLabel(tab_dashboard);
        label_log->setObjectName("label_log");

        verticalLayout_main->addWidget(label_log);

        textEdit_log = new QTextEdit(tab_dashboard);
        textEdit_log->setObjectName("textEdit_log");
        textEdit_log->setMaximumSize(QSize(16777215, 100));
        textEdit_log->setReadOnly(true);

        verticalLayout_main->addWidget(textEdit_log);

        tabWidget->addTab(tab_dashboard, QString());
        tab_processes = new QWidget();
        tab_processes->setObjectName("tab_processes");
        verticalLayout_proc = new QVBoxLayout(tab_processes);
        verticalLayout_proc->setObjectName("verticalLayout_proc");
        label_proc_title = new QLabel(tab_processes);
        label_proc_title->setObjectName("label_proc_title");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_proc_title->setFont(font);

        verticalLayout_proc->addWidget(label_proc_title);

        tableWidget_proc = new QTableWidget(tab_processes);
        if (tableWidget_proc->columnCount() < 4)
            tableWidget_proc->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_proc->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_proc->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_proc->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_proc->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_proc->setObjectName("tableWidget_proc");
        tableWidget_proc->setColumnCount(4);

        verticalLayout_proc->addWidget(tableWidget_proc);

        btn_refreshProc = new QPushButton(tab_processes);
        btn_refreshProc->setObjectName("btn_refreshProc");
        btn_refreshProc->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_proc->addWidget(btn_refreshProc);

        tabWidget->addTab(tab_processes, QString());

        verticalLayout_root->addWidget(tabWidget);

        btn_saveReport = new QPushButton(centralwidget);
        btn_saveReport->setObjectName("btn_saveReport");
        btn_saveReport->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout_root->addWidget(btn_saveReport);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1050, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "System Monitor (Task Manager Ultimate)", nullptr));
        groupBox_info->setTitle(QCoreApplication::translate("MainWindow", "System Information", nullptr));
        label_os_info->setText(QCoreApplication::translate("MainWindow", "Initializing system info...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "CPU Usage:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Memory Usage:", nullptr));
        label_disk->setText(QCoreApplication::translate("MainWindow", "Disk Usage:", nullptr));
        progressBar_disk->setFormat(QCoreApplication::translate("MainWindow", "%p% (System Drive)", nullptr));
        label_net->setText(QCoreApplication::translate("MainWindow", "Network I/O:", nullptr));
        progressBar_net->setFormat(QCoreApplication::translate("MainWindow", "%v", nullptr));
        label_log->setText(QCoreApplication::translate("MainWindow", "System Alarm Log:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_dashboard), QCoreApplication::translate("MainWindow", "Performance Dashboard", nullptr));
        label_proc_title->setText(QCoreApplication::translate("MainWindow", "Running Processes (Loading...)", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_proc->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "PID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_proc->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Process Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_proc->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Threads", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_proc->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Memory", nullptr));
        btn_refreshProc->setText(QCoreApplication::translate("MainWindow", "Refresh Process List", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_processes), QCoreApplication::translate("MainWindow", "Process Manager", nullptr));
        btn_saveReport->setText(QCoreApplication::translate("MainWindow", "Generate Full Report", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
