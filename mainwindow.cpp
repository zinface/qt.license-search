
#include "mainwindow.h"

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
{
    QFont font = this->font();
    font.setPointSize(font.pointSize() - 2);
// 1
    QGroupBox *licenceSearchGroupBox = new QGroupBox("许可证列表");
	QVBoxLayout *licenceSearchGroupBoxLayout = new QVBoxLayout(licenceSearchGroupBox);
// 1.1
    QListWidget *licenceList = new QListWidget;
    licenceList->setSortingEnabled(true);

// 1.2
    QGroupBox *licenceDescriptionGroupBox = new QGroupBox("说明");
    licenceDescriptionGroupBox->setFont(font);
	QVBoxLayout *licenceDescriptionGroupBoxLayout = new QVBoxLayout(licenceDescriptionGroupBox);
    QLabel *licenceDescriptionLabel = new QLabel;
    licenceDescriptionLabel->setMargin(0);
    licenceDescriptionLabel->setWordWrap(true);
    licenceDescriptionGroupBoxLayout->addWidget(licenceDescriptionLabel, 0, Qt::AlignTop);

    licenceSearchGroupBoxLayout->addWidget(licenceList, 6);
    licenceSearchGroupBoxLayout->addWidget(licenceDescriptionGroupBox, 4);
//! 1

// 2
    QGroupBox *licenceInfomationGroupBox = new QGroupBox("许可证信息");
	QVBoxLayout *licenceInfomationGroupBoxLayout = new QVBoxLayout(licenceInfomationGroupBox);
// 2.1
    // QGroupBox *licencePermissionsBox = new QGroupBox("Permissions(允许用途)");
    QGroupBox *licencePermissionsBox = new QGroupBox("允许用途");
    licencePermissionsBox->setFont(font);
    QVBoxLayout *licencePermissionsBoxLayout = new QVBoxLayout(licencePermissionsBox);
    QLabel *licencePermissionsLabel = new QLabel;
    licencePermissionsBoxLayout->addWidget(licencePermissionsLabel, 0, Qt::AlignTop);

// 2.2
    // QGroupBox *licenceConditionsBox = new QGroupBox("Conditions(要求条件)");
    QGroupBox *licenceConditionsBox = new QGroupBox("要求条件");
    licenceConditionsBox->setFont(font);
    QVBoxLayout *licenceConditionsBoxLayout = new QVBoxLayout(licenceConditionsBox);
    QLabel *licenceConditionsLabel = new QLabel;
    licenceConditionsBoxLayout->addWidget(licenceConditionsLabel, 0, Qt::AlignTop);

// 2.3
    // QGroupBox *licenceLimitationsBox = new QGroupBox("Limitations(限制用途)");
    QGroupBox *licenceLimitationsBox = new QGroupBox("限制用途");
    licenceLimitationsBox->setFont(font);
    QVBoxLayout *licenceLimitationsBoxLayout = new QVBoxLayout(licenceLimitationsBox);
    QLabel *licenceLimitationsLabel = new QLabel;
    licenceLimitationsBoxLayout->addWidget(licenceLimitationsLabel, 0, Qt::AlignTop);
    
// 2.4
    QGroupBox *licenceHowBox = new QGroupBox("许可证实施规范");
    licenceHowBox->setFont(font);
    QVBoxLayout *licenceHowBoxLayout = new QVBoxLayout(licenceHowBox);
    QLabel *licenceHowLabel = new QLabel;
    licenceHowLabel->setWordWrap(true);
    licenceHowBoxLayout->addWidget(licenceHowLabel, 0, Qt::AlignTop);

// 2.5
    QGroupBox *licenceNoteBox = new QGroupBox("许可证注意事项");
    licenceNoteBox->setFont(font);
    QVBoxLayout *licenceNoteBoxLayout = new QVBoxLayout(licenceNoteBox);
    QLabel *licenceNoteLabel = new QLabel;
    licenceNoteLabel->setWordWrap(true);
    licenceNoteBoxLayout->addWidget(licenceNoteLabel);

// 2.6
    QGroupBox *licenceContentBox = new QGroupBox("许可证内容");
    licenceContentBox->setFont(font);
    
    QVBoxLayout *licenceContentBoxLayout = new QVBoxLayout(licenceContentBox);
    QTextEdit *licenceContentText = new QTextEdit;
    licenceContentBoxLayout->addWidget(licenceContentText);

// 2.7
    licenceInfomationGroupBoxLayout->addWidget(licencePermissionsBox);
    licenceInfomationGroupBoxLayout->addWidget(licenceConditionsBox);
    licenceInfomationGroupBoxLayout->addWidget(licenceLimitationsBox);
    licenceInfomationGroupBoxLayout->addWidget(licenceHowBox);
    licenceInfomationGroupBoxLayout->addWidget(licenceNoteBox);
    licenceInfomationGroupBoxLayout->addWidget(licenceContentBox, 1);
    // licenceInfomationGroupBoxLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(licenceSearchGroupBox, 4);
    mainLayout->addWidget(licenceInfomationGroupBox, 6);

    setLayout(mainLayout);

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

