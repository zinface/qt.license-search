
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QListWidget>
#include <LicenceInfoObject.h>
#include <LicenceInfoManage.h>
#include <NetworkRequest.h>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
  ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font = this->font();
    font.setPointSize(font.pointSize() - 2);

    QListWidget *licenceList = ui->licenceList;
    licenceList->setSortingEnabled(true);
    QLabel *licenceDescriptionLabel = ui->licenceDescriptionLabel;
    QLabel *licencePermissionsLabel = ui->licencePermissionsLabel;
    QLabel *licenceConditionsLabel = ui->licenceConditionsLabel;
    QLabel *licenceLimitationsLabel = ui->licenceLimitationsLabel;
    QLabel *licenceHowLabel = ui->licenceHowLabel;
    QLabel *licenceNoteLabel = ui->licenceNoteLabel;
    QTextEdit *licenceContentText = ui->licenceContentText;

    // 初始化时，清空 ui 设计图里的所有内容
    licenceDescriptionLabel->clear();
    licencePermissionsLabel->clear();
    licenceConditionsLabel->clear();
    licenceLimitationsLabel->clear();
    licenceHowLabel->clear();
    licenceNoteLabel->clear();
    licenceContentText->clear();

    resize(1200, 800);

    NetworkRequest *contentRequest = new NetworkRequest;
    connect(contentRequest,&NetworkRequest::replyRequest, [=](const QString &content){
        licenceContentText->setText(content);
    });

    manage = new LicenceInfoManage;
    connect(licenceList, &QListWidget::currentTextChanged, [=](const QString &currentText){
        for (auto lab : labels)
        {
            lab->setHidden(true);
        }
        for (auto &item : manage->licenseItems)
        {
            if (currentText.contains(item->id) && currentText.contains(item->title)) {
                licenceDescriptionLabel->setText(item->description);
                setLicenceLabelRuleData(licencePermissionsLabel, item->permissions, LicenceInfoManage::RuleType::Permissions);
                setLicenceLabelRuleData(licenceConditionsLabel, item->conditions, LicenceInfoManage::RuleType::Conditions);
                setLicenceLabelRuleData(licenceLimitationsLabel, item->limitations, LicenceInfoManage::RuleType::Limitations);
                if (item->how.length() > 0) {
                    licenceHowLabel->setText(item->how);
                    licenceHowLabel->parentWidget()->setHidden(false);
                } else {
                    licenceHowLabel->parentWidget()->setHidden(true);
                }

                if (item->note.length() > 0) {
                    licenceNoteLabel->setText(item->note);
                    licenceNoteLabel->parentWidget()->setHidden(false);
                } else {
                    licenceNoteLabel->parentWidget()->setHidden(true);
                }

                if (item->url.length() > 0) {
                    contentRequest->requestString(item->url);
                    licenceContentText->parentWidget()->setHidden(false);
                } else {
                    licenceContentText->parentWidget()->setHidden(true);
                }
            }
        }
    });
    connect(manage, &LicenceInfoManage::licenseLoaded, [=](QList<LicenceInfoObject *> licenseItems){
        QFont font = this->font();
        font.setPointSize(font.pointSize() - 2);
        licenceList->setFont(font);
        for (auto &item : licenseItems)
        {
            licenceList->addItem(QString("%1: %2").arg(item->id).arg(item->title));
        }
    });

    manage->reload();
}
MainWindow::~MainWindow()
{
	
}

void MainWindow::setLicenceLabelRuleData(QLabel *label, QStringList list, LicenceInfoManage::RuleType type) {
    QStringList _list;
    for (int i = 0; i < list.size(); i++) {
        QString str = list.at(i);
        switch (type) {
            case LicenceInfoManage::RuleType::Permissions:
                _list << (QString("%1.%2").arg(i+1).arg(manage->permissions_rules.value(str)));
                break;
            case LicenceInfoManage::RuleType::Conditions:
                _list << (QString("%1.%2").arg(i+1).arg(manage->conditions_rules.value(str)));
                break;
            case LicenceInfoManage::RuleType::Limitations:
                _list << (QString("%1.%2").arg(i+1).arg(manage->limitations_rules.value(str)));
                break;
        }
    }
    label->setText(_list.join("\n"));
    if (list.size() == 0) {
        label->parentWidget()->setHidden(true);
    } else {
        label->parentWidget()->setHidden(false);
        label->setWordWrap(true);
    }
}

