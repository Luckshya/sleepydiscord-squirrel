// ------------------------------------------------------------------------------------------------
#include "DEmbed.h"

// ------------------------------------------------------------------------------------------------
namespace SqDiscord
{
// ------------------------------------------------------------------------------------------------
Embed::Embed()
{
	embed = new SleepyDiscord::Embed();
	embed->title = "";
	embed->description = "";
}

// ------------------------------------------------------------------------------------------------
void Embed::AddField(EmbedField field) {
	embed->fields.push_back(*(field.field));
}

// ------------------------------------------------------------------------------------------------
void Embed::SetTitle(CCStr title) {
	embed->title = title;
}

// ------------------------------------------------------------------------------------------------
void Embed::SetType(CCStr type) {
	embed->type = type;
}

// ------------------------------------------------------------------------------------------------
void Embed::SetDescription(CCStr description) {
	embed->description = description;
}

// ------------------------------------------------------------------------------------------------
void Embed::SetURL(CCStr URL) {
	embed->url = URL;
}

// ------------------------------------------------------------------------------------------------
void Embed::SetTimestamp(CCStr ts) {
	embed->timestamp = ts;
}

// ------------------------------------------------------------------------------------------------
void Embed::SetColor(int32_t color) {
	embed->color = color;
}

// ------------------------------------------------------------------------------------------------
void Embed::SetFooter(EmbedFooter footer) {
	embed->footer = *(footer.embedFooter);
}

// ------------------------------------------------------------------------------------------------
void Embed::SetImage(EmbedImage img) {
	embed->image = *(img.embedImage);
}

// ------------------------------------------------------------------------------------------------
void Embed::SetThumbnail(EmbedThumbnail tn) {
	embed->thumbnail = *(tn.embedThumbnail);
}

// ------------------------------------------------------------------------------------------------
void Embed::SetVideo(EmbedVideo vid) {
	embed->video = *(vid.embedVideo);
}

// ------------------------------------------------------------------------------------------------
void Embed::SetProvider(EmbedProvider provider) {
	embed->provider = *(provider.embedProvider);
}

// ------------------------------------------------------------------------------------------------
void Embed::SetAuthor(EmbedAuthor author) {
	embed->author = *(author.embedAuthor);
}

// ------------------------------------------------------------------------------------------------
Embed::~Embed() {
	delete embed;
}

// ------------------------------------------------------------------------------------------------
void Register_Embeds(Sqrat::Table embeds) {
	using namespace Sqrat;

	HSQUIRRELVM vm = embeds.GetVM();

	embeds.Bind("Embed",
		Class< Embed, NoCopy< Embed > >(vm, "Embed")

		.Func("AddField", &Embed::AddField)
		.Func("SetTitle", &Embed::SetTitle)
		.Func("SetType", &Embed::SetType)
		.Func("SetDescription", &Embed::SetDescription)
		.Func("SetURL", &Embed::SetURL)
		.Func("SetTimestamp", &Embed::SetTimestamp)
		.Func("SetColor", &Embed::SetColor)
		.Func("SetFooter", &Embed::SetFooter)
		.Func("SetImage", &Embed::SetImage)
		.Func("SetThumbnail", &Embed::SetThumbnail)
		.Func("SetVideo", &Embed::SetVideo)
		.Func("SetProvider", &Embed::SetProvider)
		.Func("SetAuthor", &Embed::SetAuthor)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedField",
		Class< EmbedField, NoCopy<EmbedField> >(vm, "EmbedField")

		.Func("SetName", &EmbedField::SetName)
		.Func("SetValue", &EmbedField::SetValue)
		.Func("SetInline", &EmbedField::SetInline)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedThumbnail",
		Class< EmbedThumbnail, NoCopy<EmbedThumbnail> >(vm, "EmbedThumbnail")

		.Func("SetURL", &EmbedThumbnail::SetURL)
		.Func("SetProxyURL", &EmbedThumbnail::SetProxyURL)
		.Func("SetHeight", &EmbedThumbnail::SetHeight)
		.Func("SetWidth", &EmbedThumbnail::SetWidth)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedField",
		Class< EmbedField, NoCopy<EmbedField> >(vm, "EmbedField")

		.Func("SetName", &EmbedField::SetName)
		.Func("SetValue", &EmbedField::SetValue)
		.Func("SetInline", &EmbedField::SetInline)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedFooter",
		Class< EmbedFooter, NoCopy<EmbedFooter> >(vm, "EmbedFooter")

		.Func("SetText", &EmbedFooter::SetText)
		.Func("SetIconURL", &EmbedFooter::SetIconURL)
		.Func("SetProxyIconURL", &EmbedFooter::SetProxyIconURL)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedImage",
		Class< EmbedImage, NoCopy<EmbedImage> >(vm, "EmbedImage")

		.Func("SetURL", &EmbedImage::SetURL)
		.Func("SetProxyURL", &EmbedImage::SetProxyURL)
		.Func("SetHeight", &EmbedImage::SetHeight)
		.Func("SetWidth", &EmbedImage::SetWidth)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedVideo",
		Class< EmbedVideo, NoCopy<EmbedVideo> >(vm, "EmbedVideo")

		.Func("SetURL", &EmbedVideo::SetURL)
		.Func("SetHeight", &EmbedVideo::SetHeight)
		.Func("SetWidth", &EmbedVideo::SetWidth)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedProvider",
		Class< EmbedProvider, NoCopy<EmbedProvider> >(vm, "EmbedProvider")

		.Func("SetName", &EmbedProvider::SetName)
		.Func("SetURL", &EmbedProvider::SetURL)
	);

	// ------------------------------------------------------------------------------------------------
	embeds.Bind("EmbedAuthor",
		Class< EmbedAuthor, NoCopy<EmbedAuthor> >(vm, "EmbedAuthor")

		.Func("SetName", &EmbedAuthor::SetName)
		.Func("SetURL", &EmbedAuthor::SetURL)
		.Func("SetIconURL", &EmbedAuthor::SetIconURL)
		.Func("SetProxyIconURL", &EmbedAuthor::SetProxyIconURL)
	);
}

// ------------------------------------------------------------------------------------------------
EmbedField::EmbedField()
{
	field = new SleepyDiscord::EmbedField();
	field->name = "";
	field->value = "";
}

// ------------------------------------------------------------------------------------------------
void EmbedField::SetName(CCStr name)
{
	field->name = name;
}

// ------------------------------------------------------------------------------------------------
void EmbedField::SetValue(CCStr value)
{
	field->value = value;
}

// ------------------------------------------------------------------------------------------------
void EmbedField::SetInline(bool isInline)
{
	field->isInline = isInline;
}

// ------------------------------------------------------------------------------------------------
EmbedField::~EmbedField() {
	delete field;
}

// ------------------------------------------------------------------------------------------------
EmbedThumbnail::EmbedThumbnail() {
	embedThumbnail = new SleepyDiscord::EmbedThumbnail();
}

// ------------------------------------------------------------------------------------------------
void EmbedThumbnail::SetURL(CCStr url) {
	embedThumbnail->url = url;
}

// ------------------------------------------------------------------------------------------------
void EmbedThumbnail::SetProxyURL(CCStr pUrl) {
	embedThumbnail->proxyUrl = pUrl;
}

// ------------------------------------------------------------------------------------------------
void EmbedThumbnail::SetHeight(int64_t ht) {
	embedThumbnail->height = ht;
}

// ------------------------------------------------------------------------------------------------
void EmbedThumbnail::SetWidth(int64_t wd) {
	embedThumbnail->width = wd;
}

// ------------------------------------------------------------------------------------------------
EmbedThumbnail::~EmbedThumbnail() {
	delete embedThumbnail;
}

// ------------------------------------------------------------------------------------------------
EmbedFooter::EmbedFooter() {
	embedFooter = new SleepyDiscord::EmbedFooter();
}

// ------------------------------------------------------------------------------------------------
void EmbedFooter::SetText(CCStr text) {
	embedFooter->text = text;
}

// ------------------------------------------------------------------------------------------------
void EmbedFooter::SetIconURL(CCStr url) {
	embedFooter->iconUrl = url;
}

// ------------------------------------------------------------------------------------------------
void EmbedFooter::SetProxyIconURL(CCStr pURL) {
	embedFooter->proxyIconUrl = pURL;
}

// ------------------------------------------------------------------------------------------------
EmbedFooter::~EmbedFooter() {
	delete embedFooter;
}

// ------------------------------------------------------------------------------------------------
EmbedImage::EmbedImage() {
	embedImage = new SleepyDiscord::EmbedImage();
}

// ------------------------------------------------------------------------------------------------
void EmbedImage::SetURL(CCStr url) {
	embedImage->url = url;
}

// ------------------------------------------------------------------------------------------------
void EmbedImage::SetProxyURL(CCStr pUrl) {
	embedImage->proxyUrl = pUrl;
}

// ------------------------------------------------------------------------------------------------
void EmbedImage::SetHeight(int64_t ht) {
	embedImage->height = ht;
}

// ------------------------------------------------------------------------------------------------
void EmbedImage::SetWidth(int64_t wd) {
	embedImage->width = wd;
}

// ------------------------------------------------------------------------------------------------
EmbedImage::~EmbedImage() {
	delete embedImage;
}

// ------------------------------------------------------------------------------------------------
EmbedVideo::EmbedVideo() {
	embedVideo = new SleepyDiscord::EmbedVideo();
}

// ------------------------------------------------------------------------------------------------
void EmbedVideo::SetURL(CCStr url) {
	embedVideo->url = url;
}

// ------------------------------------------------------------------------------------------------
void EmbedVideo::SetHeight(int64_t ht) {
	embedVideo->height = ht;
}

// ------------------------------------------------------------------------------------------------
void EmbedVideo::SetWidth(int64_t wd) {
	embedVideo->width = wd;
}

// ------------------------------------------------------------------------------------------------
EmbedVideo::~EmbedVideo() {
	delete embedVideo;
}

// ------------------------------------------------------------------------------------------------
EmbedProvider::EmbedProvider() {
	embedProvider = new SleepyDiscord::EmbedProvider();
}

// ------------------------------------------------------------------------------------------------
void EmbedProvider::SetName(CCStr name) {
	embedProvider->name = name;
}

// ------------------------------------------------------------------------------------------------
void EmbedProvider::SetURL(CCStr url) {
	embedProvider->url = url;
}

// ------------------------------------------------------------------------------------------------
EmbedProvider::~EmbedProvider() {
	delete embedProvider;
}

// ------------------------------------------------------------------------------------------------
EmbedAuthor::EmbedAuthor() {
	embedAuthor = new SleepyDiscord::EmbedAuthor();
}

// ------------------------------------------------------------------------------------------------
void EmbedAuthor::SetName(CCStr author) {
	embedAuthor->name = author;
}

// ------------------------------------------------------------------------------------------------
void EmbedAuthor::SetURL(CCStr url) {
	embedAuthor->url = url;
}

// ------------------------------------------------------------------------------------------------
void EmbedAuthor::SetIconURL(CCStr iconURL) {
	embedAuthor->iconUrl = iconURL;
}

// ------------------------------------------------------------------------------------------------
void EmbedAuthor::SetProxyIconURL(CCStr pIconUrl) {
	embedAuthor->proxyIconUrl = pIconUrl;
}

// ------------------------------------------------------------------------------------------------
EmbedAuthor::~EmbedAuthor() {
	embedAuthor = new SleepyDiscord::EmbedAuthor();
}
}

