
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QVBoxLayout;
class LicenceInfoManage;
class QLabel;
class QListWidget;
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    LicenceInfoManage *manage;

private:
    void setLicenceLabelRuleData(QLabel *label, QStringList list);


    QList<QWidget*> labels;

};

#endif // MAINWINDOW_H

