#pragma once

// Optional settings to configure compilation

#define PN_LOG_LEVEL eLV_COMMENTS

// Required definitions to set up the compiler environment
#ifdef _MSC_VER
  #pragma warning ( disable : 4996 4800 )
#endif