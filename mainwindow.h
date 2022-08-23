
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <LicenceInfoManage.h>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QListWidget;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LicenceInfoManage *manage;

private:
    void setLicenceLabelRuleData(QLabel *label, QStringList list, LicenceInfoManage::RuleType type);


    QList<QWidget*> labels;

};

#endif // MAINWINDOW_H

