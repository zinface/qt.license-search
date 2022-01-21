
#ifndef __LicenceInfoManage__H__
#define __LicenceInfoManage__H__

#include <QObject>
#include <QMap>

QT_BEGIN_NAMESPACE
class LicenceInfoObject;
class NetworkRequest;
QT_END_NAMESPACE
class LicenceInfoManage : public QObject
{
    Q_OBJECT
public:
    explicit LicenceInfoManage(QObject *parent=nullptr);

    enum RuleType {
        Permissions,
        Conditions,
        Limitations,
    };

    void reload();
    // QMap<QString, QString> rules;
    QMap<QString, QString> permissions_rules;
    QMap<QString, QString> conditions_rules;
    QMap<QString, QString> limitations_rules;
    QList<LicenceInfoObject*> licenseItems;

signals:
    void licenseLoaded(QList<LicenceInfoObject*> licenseItems);

private:
    NetworkRequest *request;
};

#endif  //!__LicenceInfoManage__H__