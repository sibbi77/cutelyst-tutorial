#include "hello.h"

#include <Cutelyst/Plugins/StaticSimple/staticsimple.h>
#include <Cutelyst/Plugins/View/Grantlee/grantleeview.h>
#include <Cutelyst/Engine>

#include <QtCore>

#include "root.h"
#include "site.h"

#include "mailer.h"

using namespace Cutelyst;

Hello::Hello(QObject *parent) : Application(parent)
{
}

Hello::~Hello()
{
}

bool Hello::init()
{
    new Root(this);
    new Site(this);

    new StaticSimple(this);

    new GrantleeView(this);

    if (engine()->isZeroWorker()) {
        // create mailer thread
        QThread* mailer_thread = new QThread( this );
        g_mailer = new Mailer();
        g_mailer->moveToThread( mailer_thread );
        connect( mailer_thread, &QThread::started, g_mailer, &Mailer::run );
        mailer_thread->start();
    }

    return true;
}

