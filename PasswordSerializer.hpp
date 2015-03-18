
#ifndef PASSWORD_SERIALIZER_HPP
#define PASSWORD_SERIALIZER_HPP

#include "predefinedValues.hpp"
#include <QString>
#include <QList>


struct Rule
{
    bool monday = false;
    bool tuesday = false;
    bool wednesday = false;
    bool thursday = false;
    bool fryday = false;
    bool saturday = false;
    bool sunday = false;

    int minTime = 0;
    int maxTime = 24 * 60 * MINUTE_DURATION;

    int delay = 0;
};


class PasswordSerializer
{
    public :

    void reset();

    bool load(const QString& passwordStr, const QString& masterkey); // loads a crypted password string and sets all variables
    const QString& getPasswordStr() const;
    int waitingTime() const;

    void addRule(const Rule& r);
    void setPasswordStr(const QString& str);
    QString serialize(const QString& masterkey) const;  // returns a crypted password string


    private :

    QString cypher(const QString& str, QString masterkey) const;
    QString decypher(const QString& str, const QString& masterkey) const;

    bool addRule(const QString& rule);
    bool addToRule(const QString& ruleSubstr, Rule& r) const;

    QString m_passwordStr;
    QList<Rule> m_ruleList;
};


#endif // PASSWORD_SERIALIZER_HPP
