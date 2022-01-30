/* ************************************************************************ */
/*																			*/
/*  Systool - a Neko VM library												*/
/*  Copyright (c)2006														*/
/*  Asger Ottar Alstrup, Nicolas Cannasse, Edwin van Rijkom, Ian Thomas		*/
/*																			*/
/* This library is free software; you can redistribute it and/or			*/
/* modify it under the terms of the GNU Lesser General Public				*/
/* License as published by the Free Software Foundation; either				*/
/* version 2.1 of the License, or (at your option) any later version.		*/
/*																			*/
/* This library is distributed in the hope that it will be useful,			*/
/* but WITHOUT ANY WARRANTY; without even the implied warranty of			*/
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU		*/
/* Lesser General Public License or the LICENSE file for more details.		*/
/*																			*/
/* ************************************************************************ */

#ifndef STATIC_LINK
	#define IMPLEMENT_API
#endif

#include <stdio.h>
#include <stdlib.h>

extern "C"
{
	#include "api.h"
	#include "misc.h"
	#include "dialogs.h"
}

// init

static void systools_init()
{
	systools_misc_initialize();
}

// ---------------- Dialog methods -------------------------------------------


static void dialogs_message_box( const char* title, const char* msg, bool error ) {
	systools_dialogs_message_box(title,msg,error);
}


static bool dialogs_dialog_box( const char* title, const char* msg, bool error ) {
	int r;
	r = systools_dialogs_dialog_box(title,msg,error);
	return (bool) r;
}

static const char *dialogs_save_file( const char *title, const char* msg, const char* initialdir, ARG_FILEFILTERS* mask) {
	char * v;
	const char* result = nullptr;
	result = nullptr;
	v = systools_dialogs_save_file(title,msg,initialdir,mask ? mask : nullptr);
	return v;

}

static const char** dialogs_open_file( const char* title, const char* msg, ARG_FILEFILTERS* mask,bool multi) {
	struct RES_STRINGLIST files;
	
	
	systools_dialogs_open_file(title,msg, mask,multi ,&files);
	
	
	
	return files.strings;
}

static const char* dialogs_folder( const char* title, const char* msg ) {
	char * v;

	v = systools_dialogs_folder(title,msg);

	return v;

}


