#ifndef __LicenceInfoObject__H__
#define __LicenceInfoObject__H__

#include <QObject>

QT_BEGIN_NAMESPACE
class QJsonObject;
QT_END_NAMESPACE
class LicenceInfoObject : public QObject
{
    Q_OBJECT

public:
    explicit LicenceInfoObject(QObject *parent=nullptr);

    void setLicence(const QJsonObject licenceObj);

    QString title;
    QString id;
    QString description;
    QString how;
    QString note;
    QString url;
    QStringList permissions;
    QStringList conditions;
    QStringList limitations;

    void setTitle(QString title);
    void setId(QString id);
    void setDescription(QString description);
    void setHow(QString how);
    void setNote(QString note);
    void setUrl(QString url);
    void setPermissions(QStringList permissions);
    void setConditions(QStringList conditions);
    void setLimitations(QStringList limitations);

    // QMap<QString, QString>;
};

#endif  //!__LicenceInfoObject__H__