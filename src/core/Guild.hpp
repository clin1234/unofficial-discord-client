#pragma once

#include "Channel.hpp"
#include "Emoji.hpp"
#include "Role.hpp"

#include <QMap>

enum class NSFW_level : unsigned char {
    Default,
    Explicit,
    Safe,
    Age_Restricted
};
enum class Veri_level : unsigned char {
    None,
    Verified_Email,
    Five_Minutes,
    Ten_Minutes,
    Verified_PhoneNum
};
enum class Explicit_Filter_level : unsigned char {
    None,
    Without_Roles,
    Everyone
};

enum class Guild_Features : unsigned char {
    Animated_Guild_Icon, // guild has access to set an animated guild icon
    Banner,              // guild has access to set a guild banner image
    Commerce,  // guild has access to use commerce features (i.e. create
               // store channels)
    Community, // guild can enable welcome screen, Membership Screening, stage
               // channels and discovery, and receives community updates
    Discoverable,        // guild is able to be discovered in the directory
    Featurable,          // guild is able to be featured in the directory
    Invite_Splash,       // guild has access to set an invite splash background
    Member_Verification, // guild has enabled Membership
                         // Screening
    News_Channels,       // guild has access to create news channels
    Partnered,           //	guild is partnered
    Previewable,         // guild can be previewed before joining via Membership
                         // Screening or the directory
    Vanity_Url,          // guild has access to set a vanity URL
    Verified,            //	guild is verified
    VIP_Higher_Voice_Bitrate, // guild has access to set 384kbps bitrate in
                              // voice (previously VIP voice servers)
    Welcome_Screen,           // guild has enabled the welcome screen
    Ticketed_Events,          //	guild has enabled ticketed events
    Monetization,             // guild has enabled monetization
    More_Stickers,            // guild has increased custom sticker slots
};

using g = Guild_Features;
const QMap<const char *, Guild_Features> guild_features_map{
    { "ANIMATED_ICON", g::Animated_Guild_Icon },
    { "BANNER", g::Banner },
    { "COMMERCE", g::Commerce },
    { "COMMUNITY", g::Community },
    { "DISCOVERABLE", g::Discoverable },
    { "FEATURABLE", g::Featurable },
    { "INVITE_SPLASH", g::Invite_Splash },
    { "MEMBER_VERIFICATION_GATE_ENABLED", g::Member_Verification },
    { "NEWS", g::News_Channels },
    { "PARTNERED", g::Partnered },
    { "PREVIEW_ENABLED", g::Previewable },
    { "VANITY_URL", g::Vanity_Url },
    { "VERIFIED", g::Verified },
    { "VIP_REGIONS", g::VIP_Higher_Voice_Bitrate },
    { "WELCOME_SCREEN_ENABLED", g::Welcome_Screen },
    { "TICKETED_EVENTS_ENABLED", g::Ticketed_Events },
    { "MONETIZATION_ENABLED", g::Monetization },
    { "MORE_STICKERS", g::More_Stickers },
};

class Guild_Base
{
    // Common fields returned in both guild and guild preview objects
    snowflake m_id;
    QString m_name, m_iconHash, m_splash, m_discovery_splash, m_description;
    QList<Emoji> m_custom_emojis;
    QList<Guild_Features> m_features;

  public:
    virtual void unmarshal(const QJsonObject &o)
    {
        unmarshal(std::move(o));
    }
    void unmarshal(const QJsonObject &&);
    snowflake id() const;
    const QString &name() const;
    QString iconHash() const;
    const QString &splash() const;
    const QString &discovery_splash() const;
    const QString &description() const;
    const QList<Emoji> &custom_emojis() const;
    const QList<Guild_Features> &features() const;
};

class Guild : public Guild_Base
{
  public:
    void unmarshal(const QJsonObject &obj);
    const QByteArray &icondata() const noexcept;

    void addChannel(Channel &&c);

    void addMessageToChannel(Message &&m);

    void setIconBase64(QByteArray &&data);

    QList<Channel> channels;

    snowflake public_updates_channel_id() const;
    const QString &preferredlocale() const;
    NSFW_level nsfwlvl() const;

    snowflake ownerid() const;
    const QString &vanity_url() const;
    Veri_level verilvl() const;
    Explicit_Filter_level explilvl() const;
    bool is_only_mentioned() const;

    const QList<Role> &roles() const;
    bool mfa_required() const;

  private:
    // Guranteed members to be returned in guild object
    snowflake m_public_updates_channel_id, m_ownerid;

    QString m_preferredlocale;
    QString m_bannerhash;
    QString m_vanity_url;
    QByteArray m_icondata;
    unsigned m_afktimeout;
    NSFW_level m_nsfwlvl;
    Veri_level m_verilvl;
    Explicit_Filter_level m_explilvl;
    bool only_mentioned, m_mfa_required;
    QList<Role> m_roles;
};

class Guild_Preview : public Guild_Base
{
    unsigned m_member_count, m_online_count;

  public:
    void unmarshal(const QJsonObject &o)
    {
        unmarshal(std::move(o));
    }
    void unmarshal(const QJsonObject &&);
    const unsigned &member_count() const;
    const unsigned &online_count() const;
};
