#include <QDebug>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qbittorrentconfpanel.h"
#include "utorrentconfpanel.h"
#include "basictorrentmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hideLeftConfig();
    hideRightConfig();
    clearStackedWidget(ui->backendConfLeft);
    clearStackedWidget(ui->backendConfRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearStackedWidget(QStackedWidget *widget)
{
    while (widget->count()) {
        auto w = widget->widget(0);
        widget->removeWidget(w);
        delete w;
    }
}

void MainWindow::prepareAndShowLeftConfigPanel(const QString &backend)
{
    QWidget *confPanel = nullptr;
    if (backend.compare("utorrent", Qt::CaseInsensitive) == 0) {
        auto panel = new uTorrentConfPanel(this);
        connect(panel, SIGNAL(accept(IRecordsAccessor *)),
                SLOT(acceptLeftConfig(IRecordsAccessor *)));
        confPanel = panel;
    } else if (backend.compare("qbittorrent", Qt::CaseInsensitive) == 0) {
        auto panel = new qBittorrentConfPanel(this);
        connect(panel, SIGNAL(accept(IRecordsAccessor *)),
                SLOT(acceptLeftConfig(IRecordsAccessor *)));
        confPanel = panel;
    } else {
        return;
    }

    clearStackedWidget(ui->backendConfLeft);
    ui->backendConfLeft->addWidget(confPanel);
    showLeftConfig();
}

void MainWindow::prepareAndShowRightConfigPanel(const QString &backend)
{
    QWidget *confPanel = nullptr;
    if (backend.compare("utorrent", Qt::CaseInsensitive) == 0) {
        auto panel = new uTorrentConfPanel(this);
        connect(panel, SIGNAL(accept(IRecordsAccessor *)),
                SLOT(acceptRightConfig(IRecordsAccessor *)));
        confPanel = panel;
    } else if (backend.compare("qbittorrent", Qt::CaseInsensitive) == 0) {
        auto panel = new qBittorrentConfPanel(this);
        connect(panel, SIGNAL(accept(IRecordsAccessor *)),
                SLOT(acceptRightConfig(IRecordsAccessor *)));
        confPanel = panel;
    } else {
        return;
    }

    clearStackedWidget(ui->backendConfRight);
    ui->backendConfRight->addWidget(confPanel);
    showRightConfig();
}

void MainWindow::acceptLeftConfig(IRecordsAccessor *accessor)
{
    hideLeftConfig();
    auto old = ui->torrentViewLeft->model();
    ui->torrentViewLeft->setModel(new BasicTorrentModel(accessor, this));
    if (old) { delete old; }

    configHeaderViewFor(ui->torrentViewLeft);
}

void MainWindow::acceptRightConfig(IRecordsAccessor *accessor)
{
    hideRightConfig();
    auto old = ui->torrentViewRight->model();
    ui->torrentViewRight->setModel(new BasicTorrentModel(accessor, this));
    if (old) { delete old; }

    configHeaderViewFor(ui->torrentViewLeft);
}

void MainWindow::hideLeftConfig()
{
    ui->backendConfLeft->hide();
    //    ui->backendConfLeft->setMaximumHeight(0);
}

void MainWindow::hideRightConfig()
{
    ui->backendConfRight->hide();
    //    ui->backendConfRight->setMaximumHeight(0);
}

void MainWindow::showLeftConfig()
{
    ui->backendConfLeft->show();

    //    QPropertyAnimation *anim = new QPropertyAnimation(ui->backendConfLeft, "maximumHeight");
    //    anim->setStartValue(0);
    //    anim->setDuration(10000);
    //    anim->setEndValue(QWIDGETSIZE_MAX);
    //    anim->start();
    //    ui->backendConfLeft->setMaximumHeight(QWIDGETSIZE_MAX);
}

void MainWindow::showRightConfig()
{
    ui->backendConfRight->show();
    //    ui->backendConfRight->setMaximumHeight(0);
}

void MainWindow::configHeaderViewFor(QTableView *view)
{
    view->horizontalHeader()->setSectionResizeMode(BasicTorrentModel::Col_No,
                                                   QHeaderView::ResizeToContents);
    view->horizontalHeader()->setSectionResizeMode(BasicTorrentModel::Col_State,
                                                   QHeaderView::ResizeToContents);
    view->horizontalHeader()->setSectionsMovable(true);
}
