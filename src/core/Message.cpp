#include "Message.hpp"

#include "Role.hpp"

#include <QJsonArray>

//#include <utility>

void Message::unmarshal(const QJsonObject &obj)
{
    // clazy:excludeall=qt4-qstring-from-array
    m_id        = obj["id"].toString().toULongLong();
    m_guildID   = obj["guild_id?"].toString().toULongLong();
    m_channelID = obj["channel_id"].toString().toULongLong();

    const auto &authorObj{ obj["author"].toObject() };
    m_author = authorObj["username"].toString();

    m_content   = obj["content"].toString();
    m_timestamp = QDateTime::fromString(obj["timestamp"].toString());
    m_edited_timestamp =
        QDateTime::fromString(obj["edited_timestamp"].toString());
    m_type       = static_cast<Type>(obj["type"].toInt());
    tts          = obj["tts"].toBool();
    mentions_all = obj["mentions_everyone"].toBool();
    pinned       = obj["pinned"].toBool();
    const auto &roles{ obj["mentioned_roles"].toArray() };
    // GULP!
    for (const auto &k : roles) {
        const auto &o{ k.toObject() };
        QJsonObject t;
        optional<Role::Tags> l;
        if (!o["tags"].isUndefined()) {
            t = o["tags"].toObject();
            optional<snowflake> id, intid;
            if (!o["id"].isUndefined() && !o["integration_id"].isUndefined()) {
                id.emplace(t["id"].toString().toULongLong());
                intid.emplace(t["integration_id"].toString().toULongLong());
            }
            l.emplace(id, intid);
        }
        const Role &r{
            o["id"].toString().toULongLong(), o["name"].toString(),
            o["color"].toString().toULong(), o["hoisted"].toBool(),
            o["position"].toString().toUInt(), o["permissions"].toString(),
            o["managed"].toBool(), o["mentionable"].toBool(), l };
        mentioned_roles.emplace_back(r);
    }
    const auto &attac{ obj["attachments"].toArray() };
    // GULP! Again!
    for (const auto &k : attac) {
        const auto &o{ k.toObject() };
        QJsonObject t;
        optional<Role::Tags> l;
        if (!o["tags"].isUndefined()) {
            t = o["tags"].toObject();
            optional<snowflake> id, intid;
            if (!o["id"].isUndefined() && !o["integration_id"].isUndefined()) {
                id.emplace(t["id"].toString().toULongLong());
                intid.emplace(t["integration_id"].toString().toULongLong());
            }
            l.emplace(id, intid);
        }
        const Role &r{
            o["id"].toString().toULongLong(), o["name"].toString(),
            o["color"].toString().toULong(), o["hoisted"].toBool(),
            o["position"].toString().toUInt(), o["permissions"].toString(),
            o["managed"].toBool(), o["mentionable"].toBool(), l };
        attachments.emplace_back(r);
    }
}

optional<snowflake> Message::guildID() const
{
    return m_guildID;
}

snowflake Message::channelID() const
{
    return m_channelID;
}

QDateTime Message::timestamp() const
{
    return m_timestamp;
}

QString Message::content() const
{
    return m_content;
}

QString Message::author() const
{
    return m_author;
}

snowflake Message::id() const
{
    return m_id;
}

const QDateTime &Message::edited_timestamp() const
{
    return m_edited_timestamp;
}

using Type = Message::Type;
Type Message::type() const
{
    return m_type;
}

bool Message::getTts() const
{
    return tts;
}

bool Message::getMentions_all() const
{
    return mentions_all;
}

const QList<Role> &Message::getMentioned_roles() const
{
    return mentioned_roles;
}

const QList<Attachment> &Message::getAttachments() const
{
    return attachments;
}

bool Message::getPinned() const
{
    return pinned;
}
