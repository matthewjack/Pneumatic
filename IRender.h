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

// In principle would be nice to support streaming in the API...


// This enum is all about data formats - maybe it should actually be about transparency etc. Immature.

#include "Definitions.h"

enum ERenderType
{
	eRT_None = PN_TYPE_NONE,                                 // Assume I have no render data
  eRT_SVG,                                                 // Stopgap measure

};

struct IRender
{
	virtual ERenderType GetType() const = 0;

	// What about multiple parts?
	// Shared matrices (and properties?) but otherwise distinct...
	virtual GeometryId GetGeometryId() const = 0;
	virtual TextureId GetTextureId() const = 0;

	virtual void RenderCustom() = 0;                         // Here as a callback to allow direct rendering through an abstract interface
};