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
#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif
#include <hx/CFFI.h>

#include <stdio.h>
#include <stdlib.h>
#include "api.h"
extern "C"
{

	#include "misc.h"
	#include "dialogs.h"
}

// init

static value systools_init()
{
	systools_misc_initialize();
	return val_null;
}
DEFINE_PRIM(systools_init,0);

// ---------------- Dialog methods -------------------------------------------


static value dialogs_message_box( value title, value msg, value error ) {
	val_check(title,string);
	val_check(msg,string);
	val_check(error,bool);
	systools_dialogs_message_box(val_string(title),val_string(msg),val_bool(error));
	return val_null;
}
DEFINE_PRIM(dialogs_message_box,3);


static value dialogs_dialog_box( value title, value msg, value error ) {
	int r;
	val_check(title,string);
	val_check(msg,string);
	val_check(error,bool);
	r = systools_dialogs_dialog_box(val_string(title),val_string(msg),val_bool(error));
	return alloc_bool(r);
}
DEFINE_PRIM(dialogs_dialog_box,3);

static value dialogs_save_file( value title, value msg, value initialdir, value mask) {
	char * v;
	struct ARG_FILEFILTERS filters = {0,0,0};

	value result = val_null;
	val_check(title, string);
	val_check(msg, string);
	val_check(initialdir, string);

	if (val_is_object(mask)) {
		value count = val_field(mask,val_id("count"));
		value descriptions = val_field(mask,val_id("descriptions"));
		value extensions = val_field(mask,val_id("extensions"));

		val_check(count,int);
		val_check(descriptions,array);
		val_check(extensions,array);

		filters.count = val_int(count);
		if (filters.count) {
			long i = filters.count;
			filters.descriptions = (const char**) malloc(i*sizeof(char*));
			filters.extensions = (const char**) malloc(i*sizeof(char*));
			while(i) {
				i--;
				filters.descriptions[i] = val_string(val_array_i(descriptions,i));
				filters.extensions[i] = val_string(val_array_i(extensions,i));
			}
		}
	}

	result = val_null;
	v = systools_dialogs_save_file(val_string(title),val_string(msg),val_string(initialdir),filters.count? &filters : NULL);
	if (v) {
		result = alloc_string(v);
		free((void*)v);
	}

	// clean up allocated mem. for filters:
	if (val_is_object(mask)) {
		free(filters.descriptions);
		free(filters.extensions);
	}

	return result;

}
DEFINE_PRIM(dialogs_save_file,4);

static value dialogs_open_file( value title, value msg, value mask,value multi) {
	value result = val_null;
	struct ARG_FILEFILTERS filters = {0,0,0};
	struct RES_STRINGLIST files;

	val_check(title,string);
	val_check(msg,string);
	val_check(multi,bool);
	
	if (val_is_object(mask)) {
		value count = val_field(mask,val_id("count"));
		value descriptions = val_field(mask,val_id("descriptions"));
		value extensions = val_field(mask,val_id("extensions"));

		val_check(count,int);
		val_check(descriptions,array);
		val_check(extensions,array);

		filters.count = val_int(count);
		if (filters.count) {
			long i = filters.count;
			filters.descriptions = (const char**) malloc(i*sizeof(char*));
			filters.extensions = (const char**) malloc(i*sizeof(char*));
			while(i) {
				i--;
				filters.descriptions[i] = val_string(val_array_i(descriptions,i));
				filters.extensions[i] = val_string(val_array_i(extensions,i));
			}
		}
	}
	
	systools_dialogs_open_file(val_string(title),val_string(msg),filters.count? &filters : NULL ,val_bool(multi) ,&files);
	if (files.count) {
		result = alloc_array(files.count);
		while(files.count) {
			files.count--;
			val_array_set_i(result, files.count, alloc_string(files.strings[files.count]));
			free(files.strings[files.count]);
		}
		free(files.strings);
	}

	// clean up allocated mem. for filters:
	if (val_is_object(mask)) {
		free(filters.descriptions);
		free(filters.extensions);
	}
	
	
	
	return result;
}
DEFINE_PRIM(dialogs_open_file,4);//note this

static value dialogs_folder( value title, value msg ) {
	char * v;
	value result = val_null;
	val_check(title, string);
	val_check(msg, string);
	result = val_null;
	v = systools_dialogs_folder(val_string(title),val_string(msg));
	if (v) {
		result = alloc_string(v);
		free(v);
	}
	return result;

}
DEFINE_PRIM(dialogs_folder,2);



// Neko specific code

extern "C" void systools_main()
{
    val_int(0); // fix neko init
}
DEFINE_ENTRY_POINT(systools_main);

extern "C" int systools_register_prims () { return 0; }
