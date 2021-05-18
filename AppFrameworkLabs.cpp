//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "AppFrameworkLabs.h"
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QDebug>

const QString kINTENT = "android/content/Intent";

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AppFrameworkLabs* AppFrameworkLabs::g_this = nullptr;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AppFrameworkLabs::AppFrameworkLabs(QObject *parent) : QObject(parent)
{
    g_this = this;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

AppFrameworkLabs::~AppFrameworkLabs()
{
    g_this = nullptr;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QString AppFrameworkLabs::qtVersion() const
{
    return qVersion();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void AppFrameworkLabs::send()
{
    const QAndroidJniObject kACTION_SEND = (QAndroidJniObject::getStaticObjectField(kINTENT.toUtf8().data(), "ACTION_SEND", "Ljava/lang/String;"));
    emit debug(QString("ACTION_SEND: ") + kACTION_SEND.toString());

    QAndroidJniObject intent(kINTENT.toUtf8().constData());
    intent.callObjectMethod("setAction", "(Ljava/langString;)Landroid/content/Intent;", kACTION_SEND.object<jstring>());

    QtAndroid::startActivity(intent.object<jobject>(), 101, fin);


}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

QObject* AppFrameworkLabs::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new AppFrameworkLabs();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void AppFrameworkLabs::fin(int a, int b, const QAndroidJniObject& obj)
{
    if (!g_this)
    {
        return;
    }

    g_this->_fin(a, b, obj);
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

void AppFrameworkLabs::_fin(int a, int b, const QAndroidJniObject& )
{
    emit debug(QString("fin: ") + QString::number(a) + " " + QString::number(b));
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
