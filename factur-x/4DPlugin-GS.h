/* --------------------------------------------------------------------------------
 #
 #	4DPlugin-GS.h
 #	source generated by 4D Plugin Wizard
 #	Project : GS
 #	author : miyako
 #	2020/05/15
 #  
 # --------------------------------------------------------------------------------*/

#ifndef PLUGIN_GS_H
#define PLUGIN_GS_H

#include "ARRAY_TEXT.h"
#include "C_LONGINT.h"
#include "C_TEXT.h"

#include "4DPluginAPI.h"

#include "iapi.h"
#include "ierrors.h"

#include "4DPlugin-JSON.h"

#if VERSIONWIN
#include <time.h>
#endif

#pragma mark -

static void PDF_TO_PDFA(PA_PluginParameters params);
static void PDFA_GET_XML(PA_PluginParameters params);
static void PDFA_SET_XML(PA_PluginParameters params);

#endif /* PLUGIN_GS_H */
