#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QStackedWidget;
class QTableView;
class IRecordsAccessor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void prepareAndShowLeftConfigPanel(const QString &backend);
    void prepareAndShowRightConfigPanel(const QString &backend);
    void prepareAndShowConfigPanel(const QString &backend, int which);
    void acceptConfig(int id, IRecordsAccessor *accessor);
    void btnTransferToRight();
    void btnTransferToLeft();

private:
    void clearStackedWidget(QStackedWidget *widget);
    void hideConfig(int which);
    void showConfig(int which);

    void configureViewFor(QTableView *view);

private:
    Ui::MainWindow *ui;
    QStackedWidget *backendConfs[2];
    QTableView *torrentViews[2];
};

#endif // MAINWINDOW_H
