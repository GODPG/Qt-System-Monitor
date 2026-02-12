#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <algorithm>


class NumericSortItem : public QTableWidgetItem
{
public:
    NumericSortItem(const QString& text) : QTableWidgetItem(text) {}
    NumericSortItem() : QTableWidgetItem() {}

    bool operator<(const QTableWidgetItem &other) const override {
        return this->data(Qt::UserRole).toDouble() < other.data(Qt::UserRole).toDouble();
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timeCounter(0)
    , m_preNetIn(0)
    , m_preNetOut(0)
{
    ui->setupUi(this);
    this->setWindowTitle("System Performance Monitoring Tool");


    QString qss = R"(
        /* Global Window */
        QMainWindow, QWidget {
            background-color: #2b2b2b;
            color: #e0e0e0;
            font-family: "Segoe UI", "Arial";
            font-size: 14px;
        }

        /* Tab Widget Styling */
        QTabWidget::pane { border: 1px solid #444; top: -1px; }
        QTabBar::tab {
            background: #1e1e1e; color: #aaa; padding: 8px 25px; border: 1px solid #444; border-bottom: none;
            border-top-left-radius: 4px; border-top-right-radius: 4px; margin-right: 2px;
        }
        QTabBar::tab:selected { background: #3498db; color: white; font-weight: bold; border-bottom: 2px solid #3498db; }
        QTabBar::tab:hover { background: #333; }

        /* Table Widget */
        QTableWidget {
            background-color: #1a1a1a; gridline-color: #333; color: #00ff00; /* Hacker Green */
            border: 1px solid #555; font-family: Consolas; selection-background-color: #3498db;
        }

        /* 【修改】恢复了简洁的表头样式，去掉了对 arrow 的自定义和 padding-right */
        QHeaderView::section {
            background-color: #333;
            color: white;
            padding: 4px;
            border: 1px solid #444;
            font-weight: bold;
            /* 确保文字居中，且不乱动 */
            padding-left: 4px;
            padding-right: 4px;
        }

        /* 【新增】将排序箭头的大小强制设为 0 */
        /* 这样 Qt 就不会预留空间，文字也就不会因为排序而左右跳动了 */
        QHeaderView::up-arrow, QHeaderView::down-arrow {
            width: 0px;
            height: 0px;
            border: none;
            background: none;
        }

        /* 注意：删除了 QHeaderView::up-arrow 和 down-arrow 的部分，
           这样 Qt 会使用系统或主题默认的排序指示器（如果有的话），
           或者仅仅通过高亮显示排序。 */

        QTableCornerButton::section { background-color: #333; border: 1px solid #444; }

        /* Standard Controls */
        QLabel { color: #ffffff; font-weight: bold; }
        QGroupBox { border: 1px solid #555; border-radius: 5px; margin-top: 10px; padding-top: 15px; }
        QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 5px; color: #00d2ff; }

        /* Progress Bars */
        QProgressBar { border: 1px solid #444; border-radius: 8px; background-color: #1e1e1e; text-align: center; color: white; font-weight: bold; }
        QProgressBar#progressBar::chunk { background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff4b1f, stop:1 #ff9068); border-radius: 8px; }
        QProgressBar#progressBar_2::chunk { background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2193b0, stop:1 #6dd5ed); border-radius: 8px; }
        QProgressBar#progressBar_disk::chunk { background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #11998e, stop:1 #38ef7d); border-radius: 8px; }
        QProgressBar#progressBar_net::chunk { background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f12711, stop:1 #f5af19); border-radius: 8px; }

        /* Buttons */
        QPushButton { background-color: #3498db; color: white; border-radius: 5px; padding: 8px; font-weight: bold; border: none; }
        QPushButton:hover { background-color: #5dade2; }
        QPushButton:pressed { background-color: #2980b9; }

        /* Log */
        QTextEdit { background-color: #000000; border: 1px solid #555; border-radius: 4px; color: #00ff00; font-family: Consolas; }
    )";
    this->setStyleSheet(qss);

    QString osType = QSysInfo::productType();
    QString osVersion = QSysInfo::productVersion();
    QString machineHostName = QSysInfo::machineHostName();
    QString cpuArch = QSysInfo::currentCpuArchitecture();
    if(osType == "windows") osType = "Windows";
    QString infoText = QString("OS: %1 %2  |  Host: %3  |  Arch: %4")
                           .arg(osType, osVersion, machineHostName, cpuArch);
    if(ui->label_os_info) ui->label_os_info->setText(infoText);

    ui->verticalLayout_main->setStretch(0, 0);
    ui->verticalLayout_main->setStretch(1, 0);
    ui->verticalLayout_main->setStretch(2, 0);
    ui->verticalLayout_main->setStretch(3, 0);
    ui->verticalLayout_main->setStretch(4, 0);
    ui->verticalLayout_main->setStretch(5, 10);
    ui->verticalLayout_main->setStretch(8, 2);

    m_chart = new QChart();
    m_chart->setTitle("Real-time System Performance Trend");
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->setAnimationOptions(QChart::SeriesAnimations);

    m_cpuSeries = new QLineSeries();
    m_cpuSeries->setName("CPU");
    m_cpuSeries->setPen(QPen(QColor("#ff4b1f"), 2));

    m_memSeries = new QLineSeries();
    m_memSeries->setName("Memory");
    m_memSeries->setPen(QPen(QColor("#2193b0"), 2));

    m_diskSeries = new QLineSeries();
    m_diskSeries->setName("Disk");
    m_diskSeries->setPen(QPen(QColor("#38ef7d"), 2));

    m_netSeries = new QLineSeries();
    m_netSeries->setName("Network");
    m_netSeries->setPen(QPen(QColor("#f5af19"), 2));

    m_chart->addSeries(m_cpuSeries); m_chart->addSeries(m_memSeries);
    m_chart->addSeries(m_diskSeries); m_chart->addSeries(m_netSeries);

    m_axisX = new QValueAxis(); m_axisX->setRange(0, 60); m_axisX->setTitleText("Time (s)"); m_axisX->setLabelFormat("%d");
    m_axisY = new QValueAxis(); m_axisY->setRange(0, 100); m_axisY->setTitleText("Usage %");

    m_chart->addAxis(m_axisX, Qt::AlignBottom); m_chart->addAxis(m_axisY, Qt::AlignLeft);
    for(auto s : m_chart->series()) { s->attachAxis(m_axisX); s->attachAxis(m_axisY); }

    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    if(ui->verticalLayout_chart) ui->verticalLayout_chart->addWidget(chartView);

    ui->tableWidget_proc->setColumnCount(4);
    ui->tableWidget_proc->setHorizontalHeaderLabels(QStringList() << "PID" << "Process Name" << "Threads" << "Memory (RAM)");
    ui->tableWidget_proc->setColumnWidth(0, 80);
    ui->tableWidget_proc->setColumnWidth(1, 250);
    ui->tableWidget_proc->setColumnWidth(2, 80);
    ui->tableWidget_proc->setColumnWidth(3, 120);
    ui->tableWidget_proc->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_proc->setSortingEnabled(true);

    GetSystemTimes(&m_preIdleTime, &m_preKernelTime, &m_preUserTime);
    getNetworkUsage();

    refreshProcessList();

    ui->tableWidget_proc->horizontalHeader()->setSortIndicator(3, Qt::DescendingOrder);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateStats);
    m_timer->start(1000);

    addLog("System Monitor initialized.", false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::refreshProcessList()
{
    int savedColumn = ui->tableWidget_proc->horizontalHeader()->sortIndicatorSection();
    Qt::SortOrder savedOrder = ui->tableWidget_proc->horizontalHeader()->sortIndicatorOrder();

    ui->tableWidget_proc->setSortingEnabled(false);
    ui->tableWidget_proc->setRowCount(0);

    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE) {
        addLog("Failed to snapshot processes!", true);
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    int row = 0;
    do {
        QString memoryStr = "Access Denied";
        QString procName = QString::fromWCharArray(pe32.szExeFile);
        double memoryMB = -1.0;

        if (pe32.th32ProcessID == 0) {
            procName = "[System Idle Process]";
            memoryStr = "System Kernel";
        }
        else if (pe32.th32ProcessID == 4) {
            procName = "System";
            memoryStr = "System Memory";
        }
        else {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe32.th32ProcessID);
            if (hProcess) {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    SIZE_T memBytes = pmc.WorkingSetSize;
                    memoryMB = memBytes / 1024.0 / 1024.0;

                    if (memoryMB < 1.0) memoryStr = QString::asprintf("%.0f KB", memBytes / 1024.0);
                    else memoryStr = QString::asprintf("%.2f MB", memoryMB);
                }
                CloseHandle(hProcess);
            }
        }


        ui->tableWidget_proc->insertRow(row);

        QTableWidgetItem *pidItem = new QTableWidgetItem();
        pidItem->setData(Qt::DisplayRole, (int)pe32.th32ProcessID);
        pidItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_proc->setItem(row, 0, pidItem);

        ui->tableWidget_proc->setItem(row, 1, new QTableWidgetItem(procName));

        QTableWidgetItem *threadItem = new QTableWidgetItem();
        threadItem->setData(Qt::DisplayRole, (int)pe32.cntThreads);
        threadItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_proc->setItem(row, 2, threadItem);

        NumericSortItem *memItem = new NumericSortItem(memoryStr);
        memItem->setData(Qt::UserRole, memoryMB);
        memItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        if (memoryMB < 0) {
            memItem->setForeground(QBrush(Qt::gray));
        }
        ui->tableWidget_proc->setItem(row, 3, memItem);

        row++;
        if (row >= 2000) break;

    } while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    ui->label_proc_title->setText(QString("Running Processes (Count: %1)").arg(row));

    ui->tableWidget_proc->setSortingEnabled(true);

    if (savedColumn >= 0) {
        ui->tableWidget_proc->horizontalHeader()->setSortIndicator(savedColumn, savedOrder);
    }
}

void MainWindow::on_btn_refreshProc_clicked() {
    refreshProcessList();
    addLog("Process list refreshed.", false);
}

void MainWindow::addLog(const QString &message, bool isWarning) {
    QString timeStr = QDateTime::currentDateTime().toString("HH:mm:ss");
    QString fullMsg = QString("[%1] %2").arg(timeStr, message);
    if (isWarning) ui->textEdit_log->append(QString("<font color='#ff4b1f'><b>%1</b></font>").arg(fullMsg));
    else ui->textEdit_log->append(fullMsg);
}

quint64 MainWindow::fileTime2UQ(const FILETIME &ft) {
    ULARGE_INTEGER li; li.LowPart = ft.dwLowDateTime; li.HighPart = ft.dwHighDateTime; return li.QuadPart;
}

double MainWindow::getMemoryUsage() {
    MEMORYSTATUSEX memInfo; memInfo.dwLength = sizeof(MEMORYSTATUSEX); GlobalMemoryStatusEx(&memInfo);
    return (double)(memInfo.ullTotalPhys - memInfo.ullAvailPhys) / memInfo.ullTotalPhys * 100.0;
}

double MainWindow::getCpuUsage() {
    FILETIME i, k, u; if (!GetSystemTimes(&i, &k, &u)) return 0.0;
    quint64 idle = fileTime2UQ(i) - fileTime2UQ(m_preIdleTime);
    quint64 kernel = fileTime2UQ(k) - fileTime2UQ(m_preKernelTime);
    quint64 user = fileTime2UQ(u) - fileTime2UQ(m_preUserTime);
    m_preIdleTime = i; m_preKernelTime = k; m_preUserTime = u;
    quint64 total = kernel + user; return total > 0 ? (double)(total - idle) / total * 100.0 : 0.0;
}

double MainWindow::getDiskUsage() {
    QStorageInfo storage("C:"); storage.refresh();
    if (storage.isValid() && storage.isReady() && storage.bytesTotal() > 0)
        return (double)(storage.bytesTotal() - storage.bytesAvailable()) / storage.bytesTotal() * 100.0;
    return 0.0;
}

double MainWindow::getNetworkUsage() {
    MIB_IFTABLE *t = nullptr; ULONG s = 0;
    if (GetIfTable(nullptr, &s, FALSE) == ERROR_INSUFFICIENT_BUFFER) t = (MIB_IFTABLE *)malloc(s);
    if (!t || GetIfTable(t, &s, FALSE) != NO_ERROR) { free(t); return 0.0; }
    DWORD in = 0, out = 0;
    for (DWORD i = 0; i < t->dwNumEntries; i++) if (t->table[i].dwType != MIB_IF_TYPE_LOOPBACK) { in += t->table[i].dwInOctets; out += t->table[i].dwOutOctets; }
    double speed = (m_preNetIn > 0) ? (double)(in - m_preNetIn + out - m_preNetOut) / 1024.0 : 0.0;
    m_preNetIn = in; m_preNetOut = out; free(t); return speed;
}

void MainWindow::updateStats()
{
    double cpu = getCpuUsage();
    double mem = getMemoryUsage();
    double disk = getDiskUsage();
    double netSpeedKB = getNetworkUsage();

    if (cpu > 80.0) addLog(QString("WARNING: High CPU Load! Current: %1%").arg(QString::asprintf("%.1f", cpu)), true);
    if (mem > 90.0) addLog(QString("WARNING: Low Memory! Current: %1%").arg(QString::asprintf("%.1f", mem)), true);

    // 网络告警
    if (netSpeedKB > 10240.0) {
        double netSpeedMB = netSpeedKB / 1024.0;
        addLog(QString("WARNING: High Network Traffic! Current: %1 MB/s").arg(QString::asprintf("%.1f", netSpeedMB)), true);
    }

    // 磁盘告警
    if (disk > 80.0) {
        if (m_timeCounter % 60 == 0) {
            addLog(QString("WARNING: Low Disk Space! Current: %1%").arg(QString::asprintf("%.1f", disk)), true);
        }
    }

    const double MAX_NET = 20480.0;
    double netPercent = (netSpeedKB / MAX_NET) * 100.0; if (netPercent > 100) netPercent = 100;

    m_cpuSeries->append(m_timeCounter, cpu);
    m_memSeries->append(m_timeCounter, mem);
    m_diskSeries->append(m_timeCounter, disk);
    m_netSeries->append(m_timeCounter, netPercent);

    if (ui->progressBar) ui->progressBar->setValue((int)cpu);
    if (ui->progressBar_2) ui->progressBar_2->setValue((int)mem);
    if (ui->progressBar_disk) ui->progressBar_disk->setValue((int)disk);
    if (ui->progressBar_net) {
        ui->progressBar_net->setValue((int)netPercent);
        ui->progressBar_net->setFormat(netSpeedKB > 1024 ? QString::asprintf("%.1f MB/s", netSpeedKB/1024) : QString::asprintf("%.0f KB/s", netSpeedKB));
    }

    if (m_timeCounter > 60) m_chart->scroll(m_chart->plotArea().width() / 60.0, 0);
    m_timeCounter++;
}

struct ProcessInfo {
    QString name;
    double memoryMB;
};

void MainWindow::on_btn_saveReport_clicked()
{
    QString fileName = "G:\\Linux_course_design\\design2\\result\\SystemReport.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QMessageBox::warning(this, "Error", "Cannot save report file!"); return;
    }

    refreshProcessList();

    QVector<ProcessInfo> allProcs;
    int rowCount = ui->tableWidget_proc->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QString name = ui->tableWidget_proc->item(i, 1)->text();
        double mem = ui->tableWidget_proc->item(i, 3)->data(Qt::UserRole).toDouble();
        allProcs.append({name, mem});
    }

    std::sort(allProcs.begin(), allProcs.end(), [](const ProcessInfo &a, const ProcessInfo &b) {
        return a.memoryMB > b.memoryMB;
    });

    QTextStream out(&file);
    out << "==================================================\n";
    out << "            SYSTEM PERFORMANCE REPORT             \n";
    out << "==================================================\n";
    out << "Time: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n";

    if(ui->label_os_info) {
        out << "System Info: " << ui->label_os_info->text() << "\n";
    }
    out << "\n[Current Resources]\n";
    out << "CPU Usage : " << ui->progressBar->value() << "%\n";
    out << "RAM Usage : " << ui->progressBar_2->value() << "%\n";
    out << "Disk Usage: " << ui->progressBar_disk->value() << "%\n";
    out << "Network   : " << ui->progressBar_net->format() << "\n";

    out << "\n[Top 3 Memory Consumers]\n";
    if (allProcs.isEmpty()) {
        out << "No process data available.\n";
    } else {
        for (int i = 0; i < 3 && i < allProcs.size(); ++i) {
            out << QString("#%1 %2").arg(i + 1).arg(allProcs[i].name)
                << "  -  " << QString::number(allProcs[i].memoryMB, 'f', 2) << " MB\n";
        }
    }

    out << "\n[System Alarm Log History]\n";
    QString logs = ui->textEdit_log->toPlainText();
    if (logs.isEmpty()) {
        out << "(No alarms recorded)\n";
    } else {
        out << logs << "\n";
    }

    out << "--------------------------------------------------\n\n";

    file.close();
    addLog("Full report with Top-Processes saved.", false);
    QMessageBox::information(this, "Success", "Report generated at:\n" + fileName);
}
