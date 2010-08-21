#pragma once


/**
 * @file Central place for compile-time settings
 * 
 * Compile-time settings and compiler environment settings
 */

#define PN_LOG_LEVEL eLV_COMMENTS

// Required definitions to set up the compiler environment
#ifdef _MSC_VER
  #pragma warning ( disable : 4996 4800 )
#endif