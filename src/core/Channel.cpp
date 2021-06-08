#include "Channel.hpp"

void Channel::unmarshal(const QJsonObject &obj)
{
    // clazy:excludeall=qt4-qstring-from-array
    m_id                = obj["id"].toString().toULongLong();
    m_name              = obj["name"].toString();
    m_nfsw              = obj["nfwm"].toBool();
    m_parentId          = obj["parent_id"].toString().toULongLong();
    m_guildId           = obj["guild_id"].toString().toULongLong();
    m_position          = obj["position"].toInt();
    m_topic             = obj["topic"].toString();
    m_last_message_id   = obj["last_message_id"].toString().toULongLong();
    rate_limit_per_user = obj["rate_limit_per_user"].toString().toUShort();
    m_type              = static_cast<Type>(obj["type"].toInt());
    message_count       = obj["message_count"].toString().toUShort();
    member_count        = obj["member_count"].toString().toUShort();
}

/*
bool key_exists(const QJsonObject &k, QString &l)
{
<<<<<<< HEAD
    return !k[l).isNull();
=======
    return !k.value(l).isNull();
<<<<<<< HEAD
>>>>>>> 4ec4a79 (WIP)
=======
>>>>>>> 2d0b1ee5ce0a55777d3de9e1449fa0f809496b37
>>>>>>> 17a0b43a7993c64631a46f28011ba408220b3e08
}*/

snowflake Channel::id() const
{
    return m_id;
}

optional<QString> Channel::name() const
{
    return m_name;
}

optional<snowflake> Channel::guildId() const
{
    return m_guildId;
}

optional<int> Channel::position() const
{
    return m_position;
}

Channel::Type Channel::type() const
{
    return m_type;
}
