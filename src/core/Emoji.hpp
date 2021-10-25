#pragma once

#include "Types.hpp"

#include <QJsonObject>
#include <optional>

using std::optional;

class Emoji
{
    snowflake m_id;
    QString m_name;
    optional<bool> m_require_colons, m_managed, m_animated, m_available;

  public:
    void unmarshal(const QJsonObject &o);
    snowflake id() const;
    const QString &name() const;
    // optional<User> &user();
    optional<bool> require_colons() const;
    optional<bool> managed() const;
    optional<bool> animated() const;
    optional<bool> available() const;
};