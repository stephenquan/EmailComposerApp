//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

#include "AppFrameworkLabs.h"
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include <QDebug>

const QString kIntentClass = "android/content/Intent";
const QString kUriClass = "android/net/Uri";

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

void AppFrameworkLabs::send(const QString& to, const QString& subject, const QString& text)
{
    QAndroidJniEnvironment env;

    const QAndroidJniObject kACTION_SEND = QAndroidJniObject::getStaticObjectField(
                kIntentClass.toUtf8().constData(),
                "ACTION_SEND",
                "Ljava/lang/String;");
    emit debug(QString("ACTION_SEND: ") + kACTION_SEND.toString());

    const QAndroidJniObject kEXTRA_SUBJECT = QAndroidJniObject::getStaticObjectField(
                kIntentClass.toUtf8().constData(),
                "EXTRA_SUBJECT",
                "Ljava/lang/String;");
    emit debug(QString("EXTRA_SUBJECT: ") + kEXTRA_SUBJECT.toString());

    const QAndroidJniObject kEXTRA_TEXT = QAndroidJniObject::getStaticObjectField(
                kIntentClass.toUtf8().constData(),
                "EXTRA_TEXT",
                "Ljava/lang/String;");
    emit debug(QString("EXTRA_TEXT: ") + kEXTRA_TEXT.toString());

    QString _to = QString("mailto:") + to;
    QAndroidJniObject toStr = QAndroidJniObject::fromString(_to);
    emit debug(QString("To: ") + toStr.toString());
    QAndroidJniObject toUrl = QAndroidJniObject::callStaticObjectMethod(
                kUriClass.toUtf8().constData(),
                "parse", "(Ljava/lang/String;)Landroid/net/Uri;",
                toStr.object<jstring>());
    emit debug(QString("ToUrl: ") + toUrl.toString());

    QAndroidJniObject intent(kIntentClass.toUtf8().constData());
    intent.callObjectMethod(
                "setAction",
                "(Ljava/lang/String;)Landroid/content/Intent;",
                kACTION_SEND.object<jstring>());

    intent.callObjectMethod(
                "setData",
                "(Landroid/net/Uri;)Landroid/content/Intent;",
                toUrl.object()
                );

    QAndroidJniObject subjectStr = QAndroidJniObject::fromString(subject);
    intent.callObjectMethod(
                "putExtra",
                "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                kEXTRA_SUBJECT.object<jstring>(),
                subjectStr.object<jstring>());

    QAndroidJniObject textStr = QAndroidJniObject::fromString(text);
    intent.callObjectMethod(
                "putExtra",
                "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                kEXTRA_TEXT.object<jstring>(),
                textStr.object<jstring>());

    QtAndroid::startActivity(intent.object<jobject>(), 101, fin);

    if (env->ExceptionCheck())
    {
        emit debug("Exception Occurred");
        env->ExceptionDescribe(); // writes to logcat
        //jthrowable jobj = env->ExceptionOccurred();
        env->ExceptionClear();
        return;
    }


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

int AppFrameworkLabs::androidSdkVersion() const
{
    return QtAndroid::androidSdkVersion();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

int AppFrameworkLabs::targetSdkVersion()
{
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod(
                "org/qtproject/qt5/android/QtNative",
                "activity",
                "()Landroid/app/Activity;");
    if (!activity.isValid())
    {
        return 0;
    }

    QAndroidJniObject packageManager = activity.callObjectMethod(
                "getPackageManager",
                "()Landroid/content/pm/PackageManager;");
    if (!packageManager.isValid())
    {
        return 0;
    }

    QAndroidJniObject packageName = activity.callObjectMethod(
                "getPackageName",
                "()Ljava/lang/String;");
    if (!packageName.isValid())
    {
        return 0;
    }

    QAndroidJniObject packageInfo = packageManager.callObjectMethod(
                "getPackageInfo",
                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;",
                packageName.object<jstring>(),
                0);
    if (!packageInfo.isValid())
    {
        return 0;
    }

    QAndroidJniObject applicationInfo = packageInfo.getObjectField(
                "applicationInfo",
                "Landroid/content/pm/ApplicationInfo;");
    if (!applicationInfo.isValid())
    {
        return 0;
    }

    return applicationInfo.getField<jint>("targetSdkVersion");
}
