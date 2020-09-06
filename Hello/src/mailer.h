#ifndef MAILER_H
#define MAILER_H

#include <QObject>
#include <QVariantHash>

class Mailer : public QObject
{
    Q_OBJECT
public:
    explicit Mailer(QObject *parent = nullptr);

public slots:
    void run();
    void sendMail( QString subject, QString body, QVariantHash options = QVariantHash() );

signals:

};

extern Mailer* g_mailer;

#endif // MAILER_H
