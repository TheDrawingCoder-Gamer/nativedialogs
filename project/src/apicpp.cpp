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

#include <hxcpp.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"
extern "C"
{
	#include "misc.h"
	#include "dialogs.h"
}

// init

static void systools_init()
{
	systools_misc_initialize();
}

// ---------------- Dialog methods -------------------------------------------


static void dialogs_message_box( ::String title, ::String msg, bool error ) {
	systools_dialogs_message_box(title.c_str(),msg.c_str(),error);
}


static bool dialogs_dialog_box( ::String title, ::String msg, bool error ) {
	int r;
	r = systools_dialogs_dialog_box(title.c_str(),msg.c_str(),error);
	return (bool) r;
}

static ::String dialogs_save_file( ::String title, ::String msg, ::String initialdir, ARG_FILEFILTERS* mask) {
	char * v;
	const char* result = nullptr;
	result = nullptr;
	v = systools_dialogs_save_file(title.c_str(),msg.c_str(),initialdir.c_str(),mask);
	return v;

}

static ::Array<::String> dialogs_open_file( ::String title, ::String msg, ARG_FILEFILTERS* mask,bool multi) {
	struct RES_STRINGLIST files;
	
	
	systools_dialogs_open_file(title,msg, mask,multi ,&files);
	::Array<::String> arr = ::Array<::String>();
	for (int i =0; i < files.count; i++) {
		arr.Add(::String::create(files.strings[i], -1));
	}
	
	return arr;
}

static ::String dialogs_folder( ::String title, ::String msg ) {
	char * v;

	v = systools_dialogs_folder(title.c_str(),msg.c_str());

	return ::String::create(v);

}


static ARG_FILEFILTERS* new_filefilters(int count, ::Array<::String> descriptions, ::Array<::String> extensions) {
	ARG_FILEFILTERS* result = {0};
	result->count = count;
	result->descriptions = (const char**) malloc(sizeof(char*)*count);
	result->extensions = (const char**) malloc(sizeof(char*)*count);
	for (int i = 0; i < count; i++) {
		result->descriptions[i] = descriptions->__get(i);
		result->extensions[i] = extensions->__get(i);
	}
	return result;
}