#include "LicenceInfoManage.h"
#include <LicenceInfoObject.h>
#include "NetworkRequest.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

LicenceInfoManage::LicenceInfoManage(QObject *parent) : QObject(parent)
, request(new NetworkRequest)
{
    NetworkRequest *requestRule = new NetworkRequest;

    connect(requestRule, &NetworkRequest::replyRequest, [=](const QString &content){
        QJsonDocument rule = QJsonDocument::fromJson(content.toLocal8Bit());
        QMap<QString, QVariant> permissionsRules = rule.object().value("permissions").toObject().toVariantMap();
        QMap<QString, QVariant> conditionsRules = rule.object().value("conditions").toObject().toVariantMap();
        QMap<QString, QVariant> limitationsRules = rule.object().value("limitations").toObject().toVariantMap();
        QStringList permissionsKeys = permissionsRules.keys();
        QStringList conditionsKeys = conditionsRules.keys();
        QStringList limitationsKeys = limitationsRules.keys();

        for (auto &key : permissionsKeys) permissions_rules.insert(key, permissionsRules.value(key, QString()).toString());
        for (auto &key : conditionsKeys) conditions_rules.insert(key, conditionsRules.value(key, QString()).toString());
        for (auto &key : limitationsKeys) limitations_rules.insert(key, limitationsRules.value(key, QString()).toString());
    });

    connect(request, &NetworkRequest::replyRequest, [=](const QString &content){
        QJsonDocument document = QJsonDocument::fromJson(content.toLocal8Bit());
        QJsonArray array = document.array();
        for (auto val : array)
        {
            LicenceInfoObject *itemInfo = new LicenceInfoObject;
            itemInfo->setLicence(val.toObject());
            licenseItems.append(itemInfo); 
        }
        emit licenseLoaded(licenseItems); 
    });

    requestRule->requestString("https://gitee.com/zinface/youwant.license/raw/master/SPDX/rules.json");
}

void LicenceInfoManage::reload() {
    request->requestString("https://gitee.com/zinface/youwant.license/raw/master/SPDX/licenses.json");
}