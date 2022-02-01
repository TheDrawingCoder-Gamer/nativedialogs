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

#define HL_NAME(n) nativedialogs_##n

#include <stdbool.h>
#include <hl.h>
// CFFI is neko afaik

#include <stdio.h>
#include <stdlib.h>

#include "misc.h"
#include "dialogs.h"

typedef struct _filefilters nativedialogs_filefilters;
struct _filefilters {
	int count;
	varray* descriptions;
	varray* extensions;
} ;
// init

HL_PRIM void HL_NAME(hl_init)()
{
	systools_misc_initialize();
}
DEFINE_PRIM(_VOID, hl_init, _NO_ARG)

// ---------------- Dialog methods -------------------------------------------


HL_PRIM void HL_NAME(hl_dialogs_message_box)( vstring* title, vstring* msg, bool error ) {
	systools_dialogs_message_box(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes), error);
}
DEFINE_PRIM(_VOID, hl_dialogs_message_box, _STRING _STRING _BOOL)


HL_PRIM bool HL_NAME(hl_dialogs_dialog_box)( vstring* title, vstring* msg, bool error ) {
	return systools_dialogs_dialog_box(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes),error) != 0;
}
DEFINE_PRIM(_BOOL, hl_dialogs_dialog_box, _STRING _STRING _BOOL)

HL_PRIM vbyte* HL_NAME(hl_dialogs_save_file)( vstring* title, vstring* msg, vstring* initialdir, vdynamic* mask) {
	char * v;
	struct ARG_FILEFILTERS filters = {0,0,0};
	if (mask) {
		int count = hl_dyn_geti(mask,hl_hash_utf8("count"), &hlt_i32);
		varray* descriptions = hl_dyn_getp(mask,hl_hash_utf8("descriptions"), &hlt_array);
		varray* extensions = hl_dyn_getp(mask,hl_hash_utf8("extensions"), &hlt_array);


		filters.count = count;
		if (filters.count) {
			int i;
			filters.descriptions = (const char**) malloc(count*sizeof(char*));
			filters.extensions = (const char**) malloc(count*sizeof(char*));
			for (i=0;i<filters.count;i++) {
				filters.descriptions[i] = hl_to_utf8((uchar*) hl_aptr(descriptions, vbyte*)[i]);
				filters.extensions[i] = hl_to_utf8((uchar*) hl_aptr(extensions, vbyte*)[i]);
			}
		}
	}

	v = systools_dialogs_save_file(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes),hl_to_utf8(initialdir->bytes),filters.count? &filters : NULL);

	// clean up allocated mem. for filters:
	if (mask) {
		free(filters.descriptions);
		free(filters.extensions);
	}

	return (vbyte*) v;

}
DEFINE_PRIM(_BYTES, hl_dialogs_save_file, _STRING _STRING _STRING _DYN)

HL_PRIM varray* HL_NAME(hl_dialogs_open_file)( vstring* title, vstring* msg, vdynamic* mask,bool multi) {
	varray* result = NULL;
	struct ARG_FILEFILTERS filters = {0,0,0};
	struct RES_STRINGLIST files;

	if (mask) {
		int count = (int)hl_dyn_geti(mask,hl_hash_utf8("count"), &hlt_i32);
		varray* descriptions = (varray*)hl_dyn_getp(mask,hl_hash_utf8("descriptions"), &hlt_array);
		varray* extensions = (varray*)hl_dyn_getp(mask,hl_hash_utf8("extensions"), &hlt_array);


		filters.count = count;
		if (filters.count) {
			int i;
			filters.descriptions = (const char**) malloc(count*sizeof(char*));
			filters.extensions = (const char**) malloc(count*sizeof(char*));
			for (i=0;i<filters.count;i++) {
				filters.descriptions[i] = hl_to_utf8((uchar*) hl_aptr(descriptions, vbyte*)[i]);
				filters.extensions[i] = hl_to_utf8((uchar*) hl_aptr(extensions, vbyte*)[i]);
			}
		}
	}
	systools_dialogs_open_file(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes),filters.count? &filters : NULL ,multi ,&files);
	if (files.count) {
		result = hl_alloc_array(&hlt_bytes, files.count);
		memcpy(hl_aptr(result, vbyte*), files.strings, files.count*hl_type_size(&hlt_bytes));
		free(files.strings);
	}

	// clean up allocated mem. for filters:
	if (mask) {
		free(filters.descriptions);
		free(filters.extensions);
	}
	
	
	return result;
}
DEFINE_PRIM(_ARR, hl_dialogs_open_file, _STRING _STRING _DYN _BOOL)//note this

HL_PRIM vbyte* HL_NAME(hl_dialogs_folder)( vstring* title, vstring* msg ) {
	char * v;
	v = systools_dialogs_folder(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes));
	return (vbyte*) v;

}
DEFINE_PRIM(_BYTES, hl_dialogs_folder, _STRING _STRING)

