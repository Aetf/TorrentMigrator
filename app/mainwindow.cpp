#include <QDebug>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qbittorrentconfpanel.h"
#include "utorrentconfpanel.h"
#include "basictorrentmodel.h"
#include "devicemaptransformer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->middleWidget->hide();
    backendConfs[0] = ui->backendConfLeft;
    backendConfs[1] = ui->backendConfRight;
    torrentViews[0] = ui->torrentViewLeft;
    torrentViews[1] = ui->torrentViewRight;

    for (int i = 0; i!= 2; i++) {
        hideConfig(i);
        clearStackedWidget(backendConfs[i]);
    }

//    auto transfermorModel = new QStandardItemModel(ui->transfermorList);
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
    prepareAndShowConfigPanel(backend, 0);
}

void MainWindow::prepareAndShowRightConfigPanel(const QString &backend)
{
    prepareAndShowConfigPanel(backend, 1);
}

void MainWindow::prepareAndShowConfigPanel(const QString &backend, int which)
{
    AbstractConfPanel *confPanel = nullptr;
    if (backend.compare("utorrent", Qt::CaseInsensitive) == 0) {
        confPanel = new uTorrentConfPanel(this);
    } else if (backend.compare("qbittorrent", Qt::CaseInsensitive) == 0) {
        confPanel = new qBittorrentConfPanel(this);
    } else {
        return;
    }
    confPanel->setId(which);
    connect(confPanel, SIGNAL(accept(int, IRecordsAccessor *)),
            SLOT(acceptConfig(int, IRecordsAccessor *)));

    clearStackedWidget(backendConfs[which]);
    backendConfs[which]->addWidget(confPanel);
    showConfig(which);
}

void MainWindow::acceptConfig(int id, IRecordsAccessor *accessor)
{
    hideConfig(id);
    auto old = torrentViews[id]->model();
    torrentViews[id]->setModel(new BasicTorrentModel(accessor, this));
    if (old) { delete old; }

    configureViewFor(torrentViews[id]);
}

void MainWindow::hideConfig(int which)
{
    backendConfs[which]->hide();
    //    backendConf[which]->setMaximumHeight(0);
}

void MainWindow::showConfig(int which)
{
    backendConfs[which]->show();
    //    QPropertyAnimation *anim = new ertyAnimation(ui->backendConfLeft, "maximumHeight");
    //    anim->setStartValue(0);
    //    anim->setDuration(10000);
    //    anim->setEndValue(QWIDGETSIZE_MAX);
    //    anim->start();
    //    backendConf[which]->setMaximumHeight(QWIDGETSIZE_MAX);
}

void MainWindow::configureViewFor(QTableView *view)
{
    view->horizontalHeader()->setSectionResizeMode(BasicTorrentModel::Col_No,
                                                   QHeaderView::ResizeToContents);
    view->horizontalHeader()->setSectionResizeMode(BasicTorrentModel::Col_State,
                                                   QHeaderView::ResizeToContents);
    view->horizontalHeader()->setSectionsMovable(true);
//    view->resizeColumnsToContents();
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void MainWindow::btnTransferToRight()
{
    auto targetModel = qobject_cast<BasicTorrentModel*>(torrentViews[1]->model());
    auto sourceModel = torrentViews[0]->model();
    if (!targetModel || !sourceModel) { return; }

    auto transformer = new DeviceMapTransformer();
    transformer->setup("I:/ => /media/AetfのHD\n"
                       "Y:/ => /media/AetfのHD.Ex\n"
                       "F:/ => /media/Documents\n"
                       "D:/ => /media/Softwares");

    for(auto idx : torrentViews[0]->selectionModel()->selectedRows()) {
        qDebug() << "Selected row:" << idx.row();
        auto record = sourceModel->data(idx, BasicTorrentModel::RecordDataRole).value<TorrentRecord>();
        qDebug() << "Processing record:" << record.name << "with save_path" << record.save_path;
        record = transformer->transform(record);
        qDebug() << "After transform:" << record.name << "with save_path" << record.save_path;
        targetModel->insertRecord(-1, record);
    }
}

void MainWindow::btnTransferToLeft()
{

}
