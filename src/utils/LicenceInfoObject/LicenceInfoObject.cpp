#include "LicenceInfoObject.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

LicenceInfoObject::LicenceInfoObject(QObject *parent) : QObject(parent) {
    
}

void LicenceInfoObject::setLicence(const QJsonObject licenceObj) {
    if(licenceObj.contains("title"))
        setTitle(licenceObj.value("title").toString());
    if(licenceObj.contains("spdx-id"))
        setId(licenceObj.value("spdx-id").toString());
    if(licenceObj.contains("description"))
        setDescription(licenceObj.value("description").toString());
    if(licenceObj.contains("how"))
        setHow(licenceObj.value("how").toString());
    if(licenceObj.contains("note"))
        setNote(licenceObj.value("note").toString());
    if(licenceObj.contains("url"))
        setUrl(licenceObj.value("url").toString());
    if(licenceObj.contains("permissions")) 
        setPermissions(licenceObj.value("permissions").toVariant().toStringList());
    if(licenceObj.contains("conditions")) 
        setConditions(licenceObj.value("conditions").toVariant().toStringList());
    if(licenceObj.contains("limitations")) 
        setLimitations(licenceObj.value("limitations").toVariant().toStringList());
}

void LicenceInfoObject::setTitle(QString title) {
    this->title = title;
}
void LicenceInfoObject::setId(QString id) {
    this->id = id;
}
void LicenceInfoObject::setDescription(QString description) {
    this->description = description;
}
void LicenceInfoObject::setHow(QString how) {
    this->how = how;
}
void LicenceInfoObject::setNote(QString note) {
    this->note = note;
}
void LicenceInfoObject::setUrl(QString url) {
    this->url = url;
}
void LicenceInfoObject::setPermissions(QStringList permissions) {
    this->permissions = permissions;
}
void LicenceInfoObject::setConditions(QStringList conditions) {
    this->conditions = conditions;
}
void LicenceInfoObject::setLimitations(QStringList limitations) {
    this->limitations = limitations;
}