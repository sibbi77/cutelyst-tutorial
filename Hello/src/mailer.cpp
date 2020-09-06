#include "mailer.h"

#include <QtCore>

Q_LOGGING_CATEGORY(LOG_MAILER, "Mailer", QtDebugMsg)

Mailer* g_mailer = nullptr;

Mailer::Mailer(QObject *parent) : QObject(parent)
{
    qCInfo(LOG_MAILER) << "Created" << thread() << QThread::currentThread();
}

void Mailer::run()
{
    qCInfo(LOG_MAILER) << "Started" << thread() << QThread::currentThread();
    pthread_setname_np( pthread_self(), "Mailer" );
}

void Mailer::sendMail( QString subject, QString body, QVariantHash options )
{
    qCDebug(LOG_MAILER) << __PRETTY_FUNCTION__;

    if (QThread::currentThread() != thread()) {
        qCDebug(LOG_MAILER) << "wrong thread" << thread() << QThread::currentThread();
        bool ok = QMetaObject::invokeMethod( this, "sendMail", Qt::QueuedConnection, Q_ARG(QString,subject), Q_ARG(QString,body), Q_ARG(QVariantHash,options) );
        qCDebug(LOG_MAILER) << "invokeMethod" << ok;
        return;
    }

    qCDebug(LOG_MAILER) << __PRETTY_FUNCTION__ << "now running in correct thread";
}
