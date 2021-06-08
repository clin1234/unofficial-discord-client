#ifndef ROLE_HPP
#define ROLE_HPP

#include "Types.hpp"

#include <QJsonObject>
#include <QString>
#include <optional>
<<<<<<< HEAD
=======

>>>>>>> 74ff62e (Add preliminary support for attachments and roles.)
using std::optional;
class Role
{
  public:
    void unmarshal(const QJsonObject &obj);
    snowflake id() const;
    const QString &name() const;
    const QString &permissions() const;
    bool hoisted() const;
    bool managed() const;
    bool mentionable() const;
    // XXX: cludge
    class Tags
    {
        optional<snowflake> id, integration_id;
<<<<<<< HEAD

      public:
=======
>>>>>>> 74ff62e (Add preliminary support for attachments and roles.)
        Tags(snowflake id, snowflake inte) : id(id), integration_id(inte) {}
    };
    optional<Tags> getTags() const;

  private:
    snowflake m_id;
    QString m_name, m_permissions;
    unsigned m_color{ 0 }, m_position;
    bool m_hoisted, m_managed, m_mentionable;
<<<<<<< HEAD
=======

>>>>>>> 74ff62e (Add preliminary support for attachments and roles.)
    optional<Tags> m_tags;
};

#endif // ROLE_HPP
