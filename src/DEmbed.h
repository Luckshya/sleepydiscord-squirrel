#pragma once

// ------------------------------------------------------------------------------------------------
#include "sqrat.h"
#include "sleepy_discord/websocketpp_websocket.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
typedef const char * CCStr;

// ------------------------------------------------------------------------------------------------
class EmbedField
{
public:
    std::shared_ptr< SleepyDiscord::EmbedField > field;

	EmbedField();

    EmbedField(const EmbedField & o) = default;
    EmbedField(EmbedField && o) = default;
    EmbedField & operator = (const EmbedField & o) = default;
    EmbedField & operator = (EmbedField && o) = default;

	void SetName(CCStr);
	void SetValue(CCStr);
	void SetInline(bool);
};

// ------------------------------------------------------------------------------------------------
class EmbedFooter
{
public :
    std::shared_ptr< SleepyDiscord::EmbedFooter > embedFooter;

	EmbedFooter();

    EmbedFooter(const EmbedFooter & o) = default;
    EmbedFooter(EmbedFooter && o) = default;
    EmbedFooter & operator = (const EmbedFooter & o) = default;
    EmbedFooter & operator = (EmbedFooter && o) = default;

	void SetText(CCStr);
	void SetIconURL(CCStr);
	void SetProxyIconURL(CCStr);
};

// ------------------------------------------------------------------------------------------------
class EmbedImage
{
public :
    std::shared_ptr< SleepyDiscord::EmbedImage > embedImage;

	EmbedImage();

    EmbedImage(const EmbedImage & o) = default;
    EmbedImage(EmbedImage && o) = default;
    EmbedImage & operator = (const EmbedImage & o) = default;
    EmbedImage & operator = (EmbedImage && o) = default;

    void SetURL(CCStr);
	void SetProxyURL(CCStr);
	void SetHeight(int64_t);
	void SetWidth(int64_t);
};

// ------------------------------------------------------------------------------------------------
class EmbedThumbnail
{
public :
    std::shared_ptr< SleepyDiscord::EmbedThumbnail > embedThumbnail;

	EmbedThumbnail();

    EmbedThumbnail(const EmbedThumbnail & o) = default;
    EmbedThumbnail(EmbedThumbnail && o) = default;
    EmbedThumbnail & operator = (const EmbedThumbnail & o) = default;
    EmbedThumbnail & operator = (EmbedThumbnail && o) = default;

	void SetURL(CCStr);
	void SetProxyURL(CCStr);
	void SetHeight(int64_t);
	void SetWidth(int64_t);
};

// ------------------------------------------------------------------------------------------------
class EmbedVideo
{
public :
    std::shared_ptr< SleepyDiscord::EmbedVideo > embedVideo;

	EmbedVideo();

    EmbedVideo(const EmbedVideo & o) = default;
    EmbedVideo(EmbedVideo && o) = default;
    EmbedVideo & operator = (const EmbedVideo & o) = default;
    EmbedVideo & operator = (EmbedVideo && o) = default;

	void SetURL(CCStr);
	void SetHeight(int64_t);
	void SetWidth(int64_t);
};

// ------------------------------------------------------------------------------------------------
class EmbedProvider
{
public:
    std::shared_ptr< SleepyDiscord::EmbedProvider > embedProvider;

	EmbedProvider();

    EmbedProvider(const EmbedProvider & o) = default;
    EmbedProvider(EmbedProvider && o) = default;
    EmbedProvider & operator = (const EmbedProvider & o) = default;
    EmbedProvider & operator = (EmbedProvider && o) = default;

	void SetName(CCStr);
	void SetURL(CCStr);
};

// ------------------------------------------------------------------------------------------------
class EmbedAuthor
{
public :
    std::shared_ptr< SleepyDiscord::EmbedAuthor > embedAuthor;

	EmbedAuthor();

    EmbedAuthor(const EmbedAuthor & o) = default;
    EmbedAuthor(EmbedAuthor && o) = default;
    EmbedAuthor & operator = (const EmbedAuthor & o) = default;
    EmbedAuthor & operator = (EmbedAuthor && o) = default;

	void SetName(CCStr);
	void SetURL(CCStr);
	void SetIconURL(CCStr);
	void SetProxyIconURL(CCStr);
};

// ------------------------------------------------------------------------------------------------
class Embed
{
public:
    std::shared_ptr< SleepyDiscord::Embed > embed;

	Embed();

    Embed(const Embed & o) = default;
    Embed(Embed && o) = default;
    Embed & operator = (const Embed & o) = default;
    Embed & operator = (Embed && o) = default;

	void AddField(const EmbedField &);
	void SetTitle(CCStr);
	void SetType(CCStr);
	void SetDescription(CCStr);
	void SetURL(CCStr);
	void SetTimestamp(CCStr);
	void SetColor(int32_t);

	void SetFooter(const EmbedFooter &);
	void SetImage(const EmbedImage &);
	void SetThumbnail(const EmbedThumbnail &);
	void SetVideo(const EmbedVideo &);
	void SetProvider(const EmbedProvider &);
	void SetAuthor(const EmbedAuthor &);
};

// ------------------------------------------------------------------------------------------------
void Register_Embeds(Sqrat::Table discordcn);
}