#ifndef __AppFrameworkLabs__
#define __AppFrameworkLabs__

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QAndroidJniObject>
#include <QString>

class AppFrameworkLabs : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)
    Q_PROPERTY(int androidSdkVersion READ androidSdkVersion CONSTANT)
    Q_PROPERTY(int targetSdkVersion READ targetSdkVersion CONSTANT)

public:
    AppFrameworkLabs(QObject *parent = nullptr);

    virtual ~AppFrameworkLabs();

    Q_INVOKABLE void send(const QString& to = QString(), const QString& subject = QString(), const QString& text = QString());

    static QObject* singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

signals:
    void debug(const QString& message);

protected:
    QString qtVersion() const;
    int androidSdkVersion() const;
    int targetSdkVersion();

    void _fin(int a, int b, const QAndroidJniObject& );
    static void fin(int a, int b, const QAndroidJniObject& );
    static AppFrameworkLabs* g_this;

};

#endif
