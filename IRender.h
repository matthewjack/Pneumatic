#pragma once

// Something like... 
// Can ask for content id, and ask if is static or dynamic
// dynamic has no content id?
// Render system can grab data and render it in some efficent manner
// No, wait, I've got all this the wrong way round.
// The renderer will want to convert this into its own format.
// When the object is loadewd, something must create than internal format
// Some other format might be exchangable with the instances for dynamic/animated content
// However, usually a render type shoudl be about the style of rendering (transparency maybe?)
// and the only thing fetched shoudl eb the handle to the renderable data, regardless of the original format.

// ?
// Maybe a graphics guy can enlighten me.


struct IRender
{
	virtual ERenderType GetType() = 0;

	virtual Render
};