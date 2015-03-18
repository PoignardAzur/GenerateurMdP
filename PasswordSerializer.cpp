
#include "PasswordSerializer.hpp"
#include <QDate>
#include <QTime>
#include <QStringList>

#include "SimpleCrypt/SimpleCrypt.hpp"
#include <QCryptographicHash>

const QString DEFAULT_MASTERKEY = "aaa";
const QString PASSWORD_CHECK = "password";


void PasswordSerializer::reset()
{
    m_passwordStr.clear();
    m_ruleList.clear();
}

bool PasswordSerializer::load(const QString& passwordStr, const QString& masterkey)
{
    QStringList ruleStrList = decypher(passwordStr, masterkey).split(";", QString::SkipEmptyParts);

    if (ruleStrList.isEmpty())
    {
        return false;
    }

    // else

    reset();

    m_passwordStr = ruleStrList[0];
    ruleStrList.removeFirst();

    for (const QString& ruleStr : ruleStrList)
    {
        addRule(ruleStr);
    }

    return true;
}

bool PasswordSerializer::addRule(const QString& ruleStr)
{
    Rule r;

    QStringList splitRuleStr = ruleStr.split(":");

    if (splitRuleStr.size() != 2)
    {
        return false;
    }

    // else

    r.delay = splitRuleStr[1].toInt();
    QStringList ruleSubstrList = splitRuleStr[0].split(",");

    for (const QString& ruleSubstr : ruleSubstrList)
    {
        addToRule(ruleSubstr, r);
    }

    addRule(r);
    return true;
}

bool PasswordSerializer::addToRule(const QString& ruleSubstr, Rule& r) const
{
    if (ruleSubstr == "Mon")
    r.monday = true;

    else if (ruleSubstr == "Tue")
    r.tuesday = true;

    else if (ruleSubstr == "Wed")
    r.wednesday = true;

    else if (ruleSubstr == "Thu")
    r.thursday = true;

    else if (ruleSubstr == "Fry")
    r.fryday = true;

    else if (ruleSubstr == "Sat")
    r.saturday = true;

    else if (ruleSubstr == "Sun")
    r.sunday = true;

    else
    {
        QStringList hours = ruleSubstr.split("-", QString::SkipEmptyParts);

        if (hours.size() < 2)
        {
            return false;
        }

        int minHour = hours[0].toInt();
        int maxHour = hours[1].toInt();

        r.minTime = minHour;
        r.maxTime = maxHour;

        if (maxHour < minHour)
        {
            return false;
        }
    }

    return true;
}


int PasswordSerializer::waitingTime() const
{
    int day = QDate::currentDate().dayOfWeek();
    int delay = 0;

    for (const Rule& r : m_ruleList)
    {
        bool apply = (day == 1 && r.monday)
                  || (day == 2 && r.tuesday)
                  || (day == 3 && r.wednesday)
                  || (day == 4 && r.thursday)
                  || (day == 5 && r.fryday)
                  || (day == 6 && r.saturday)
                  || (day == 7 && r.sunday);

        int time = QTime::currentTime().msec();
        apply = apply && (time > r.minTime) && (time < r.maxTime);

        if (apply)
        {
            if (r.delay > delay)
            {
                delay = r.delay;
            }
        }
    }

    return delay;
}

const QString& PasswordSerializer::getPasswordStr() const
{
    return m_passwordStr;
}


void PasswordSerializer::addRule(const Rule& r)
{
    m_ruleList.append(r);
}

void PasswordSerializer::setPasswordStr(const QString& str)
{
    m_passwordStr = str;
}


QString PasswordSerializer::serialize(const QString& masterkey) const
{
    QString str = getPasswordStr();

    for (const Rule& r : m_ruleList)
    {
        str += ";";

        if (r.monday)
        {
            str += "Mon,";
        }

        if (r.tuesday)
        {
            str += "Tue,";
        }

        if (r.wednesday)
        {
            str += "Wed,";
        }

        if (r.thursday)
        {
            str += "Thu,";
        }

        if (r.fryday)
        {
            str += "Fry,";
        }

        if (r.saturday)
        {
            str += "Sat,";
        }

        if (r.sunday)
        {
            str += "Sun,";
        }

        str += QString::number(r.minTime) + "-" + QString::number(r.maxTime) + ":" + QString::number(r.delay);
    }

    return cypher(str, masterkey);
}


QString PasswordSerializer::cypher(const QString& str, QString masterkey) const
{
    if (masterkey == "")
    {
        masterkey = DEFAULT_MASTERKEY;
    }

    QString hash = QCryptographicHash::hash(masterkey.toLatin1(), QCryptographicHash::Md4);
    int checksum = qChecksum(hash.toLatin1().data(), hash.size());

    SimpleCrypt crypt(checksum);
    return crypt.encryptToString(PASSWORD_CHECK + str);
}

QString PasswordSerializer::decypher(const QString& str, const QString& masterkey) const
{
    if (masterkey != DEFAULT_MASTERKEY)
    {
        QString decryptedStr = decypher(str, DEFAULT_MASTERKEY);

        if (decryptedStr != "")
        {
            return decryptedStr;
        }
    }

    // else

    QString hash = QCryptographicHash::hash(masterkey.toLatin1(), QCryptographicHash::Md4);
    int checksum = qChecksum(hash.toLatin1().data(), hash.size());

    SimpleCrypt crypt(checksum);
    QString decryptedStr = crypt.decryptToString(str);

    if (decryptedStr.indexOf(PASSWORD_CHECK) == 0)  // if the decrypted string starts with "password"
    {
        return decryptedStr.mid(PASSWORD_CHECK.size());
    }

    else
    {
        return "";
    }
}

