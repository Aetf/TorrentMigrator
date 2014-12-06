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
    void acceptLeftConfig(IRecordsAccessor *accessor);
    void acceptRightConfig(IRecordsAccessor *accessor);

private:
    void clearStackedWidget(QStackedWidget *widget);
    void hideLeftConfig();
    void hideRightConfig();
    void showLeftConfig();
    void showRightConfig();

    void configHeaderViewFor(QTableView *view);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
