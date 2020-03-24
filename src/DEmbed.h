#pragma once

// ------------------------------------------------------------------------------------------------
#include "sqrat.h"
#include "sleepy_discord/websocketpp_websocket.h"

// ------------------------------------------------------------------------------------------------
#define FAILURE 0
#define SUCCESS 1

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
typedef const char * CCStr;

// ------------------------------------------------------------------------------------------------
class EmbedField
{
public:
	SleepyDiscord::EmbedField * field;

	EmbedField();
	~EmbedField();

	void SetName(CCStr);
	void SetValue(CCStr);
	void SetInline(bool);
};

// ------------------------------------------------------------------------------------------------
class EmbedFooter
{
public :
	SleepyDiscord::EmbedFooter * embedFooter;

	EmbedFooter();
	~EmbedFooter();

	void SetText(CCStr);
	void SetIconURL(CCStr);
	void SetProxyIconURL(CCStr);
};

// ------------------------------------------------------------------------------------------------
class EmbedImage
{
public :
	SleepyDiscord::EmbedImage * embedImage;

	EmbedImage();
	~EmbedImage();

	void SetURL(CCStr);
	void SetProxyURL(CCStr);
	void SetHeight(int64_t);
	void SetWidth(int64_t);
};

// ------------------------------------------------------------------------------------------------
class EmbedThumbnail
{
public :
	SleepyDiscord::EmbedThumbnail * embedThumbnail;

	EmbedThumbnail();
	~EmbedThumbnail();

	void SetURL(CCStr);
	void SetProxyURL(CCStr);
	void SetHeight(int64_t);
	void SetWidth(int64_t);
};

// ------------------------------------------------------------------------------------------------
class EmbedVideo
{
public :
	SleepyDiscord::EmbedVideo * embedVideo;

	EmbedVideo();
	~EmbedVideo();

	void SetURL(CCStr);
	void SetHeight(int64_t);
	void SetWidth(int64_t);
};

// ------------------------------------------------------------------------------------------------
class EmbedProvider
{
public:
	SleepyDiscord::EmbedProvider * embedProvider;

	EmbedProvider();
	~EmbedProvider();

	void SetName(CCStr);
	void SetURL(CCStr);
};

// ------------------------------------------------------------------------------------------------
class EmbedAuthor
{
public :
	SleepyDiscord::EmbedAuthor * embedAuthor;

	EmbedAuthor();
	~EmbedAuthor();

	void SetName(CCStr);
	void SetURL(CCStr);
	void SetIconURL(CCStr);
	void SetProxyIconURL(CCStr);
};

// ------------------------------------------------------------------------------------------------
class Embed
{
public:
	SleepyDiscord::Embed * embed;

	Embed();
	~Embed();

	void AddField(EmbedField);
	void SetTitle(CCStr);
	void SetType(CCStr);
	void SetDescription(CCStr);
	void SetURL(CCStr);
	void SetTimestamp(CCStr);
	void SetColor(int32_t);

	void SetFooter(EmbedFooter);
	void SetImage(EmbedImage);
	void SetThumbnail(EmbedThumbnail);
	void SetVideo(EmbedVideo);
	void SetProvider(EmbedProvider);
	void SetAuthor(EmbedAuthor);
};

// ------------------------------------------------------------------------------------------------
void Register_Embeds(Sqrat::Table discordcn);
}