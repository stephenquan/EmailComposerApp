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

public:
    AppFrameworkLabs(QObject *parent = nullptr);

    virtual ~AppFrameworkLabs();

    Q_INVOKABLE void send();

    static QObject* singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

signals:
    void debug(const QString& message);

protected:
    QString qtVersion() const;

    void _fin(int a, int b, const QAndroidJniObject& );
    static void fin(int a, int b, const QAndroidJniObject& );
    static AppFrameworkLabs* g_this;

};

#endif
