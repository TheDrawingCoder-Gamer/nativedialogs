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

#define HL_NAME(n) systools_##n

#include <stdbool.h>
#include <hl.h>
// CFFI is neko afaik

#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "clipboard.h"
#include "misc.h"
#include "registry.h"
#include "dialogs.h"
#include "fileutils.h"
#ifndef HX_LINUX
#include "browser.h"
#include "display.h"
#endif

typedef struct _filefilters systools_filefilters;
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
DEFINE_PRIM(_VOID, hl_init, _NO_ARG);

// ---------------- Dialog methods -------------------------------------------


HL_PRIM void HL_NAME(hl_dialogs_message_box)( vstring* title, vstring* msg, bool error ) {
	systools_dialogs_message_box(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes), error);
}
DEFINE_PRIM(_VOID, hl_dialogs_message_box, _STRING _STRING _BOOL);


HL_PRIM bool HL_NAME(hl_dialogs_dialog_box)( vstring* title, vstring* msg, bool error ) {
	return systools_dialogs_dialog_box(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes),error) != 0;
}
DEFINE_PRIM(_BOOL, hl_dialogs_dialog_box, _STRING _STRING _BOOL);

HL_PRIM vbyte* HL_NAME(hl_dialogs_save_file)( vstring* title, vstring* msg, vstring* initialdir, vdynamic* mask) {
	char * v;
	struct ARG_FILEFILTERS filters = {0,0,0};
	if (mask) {
		int count = hl_dyn_geti(mask,hl_hash_utf8("count"), &hlt_i32);
		varray* descriptions = hl_dyn_getp(mask,hl_hash_utf8("descriptions"), &hlt_array);
		varray* extensions = hl_dyn_getp(mask,hl_hash_utf8("extensions"), &hlt_array);


		filters.count = count;
		if (filters.count) {
			long i = filters.count;
			filters.descriptions = (const char**) malloc(i*sizeof(char*));
			filters.extensions = (const char**) malloc(i*sizeof(char*));
			while(i) {
				i--;
				filters.descriptions[i] = hl_to_utf8(hl_aptr(descriptions,vstring*)[i]->bytes);
				filters.extensions[i] = hl_to_utf8(hl_aptr(extensions,vstring*)[i]->bytes);
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
DEFINE_PRIM(_BYTES, hl_dialogs_save_file, _STRING _STRING _STRING _DYN);

HL_PRIM varray* HL_NAME(hl_dialogs_open_file)( vstring* title, vstring* msg, vdynamic* mask,bool multi) {
	varray* result = NULL;
	struct ARG_FILEFILTERS filters = {0,0,0};
	struct RES_STRINGLIST files;

	
	if (mask) {
		int count = hl_dyn_geti(mask,hl_hash_utf8("count"), &hlt_i32);
		varray* descriptions = hl_dyn_getp(mask,hl_hash_utf8("descriptions"), &hlt_array);
		varray* extensions = hl_dyn_getp(mask,hl_hash_utf8("extensions"), &hlt_array);


		filters.count = count;
		if (filters.count) {
			long i = filters.count;
			filters.descriptions = (const char**) malloc(i*sizeof(char*));
			filters.extensions = (const char**) malloc(i*sizeof(char*));
			while(i) {
				i--;
				filters.descriptions[i] = hl_to_utf8(hl_aptr(descriptions,vstring*)[i]->bytes);
				filters.extensions[i] = hl_to_utf8(hl_aptr(extensions,vstring*)[i]->bytes);
			}
		}
	}
	
	systools_dialogs_open_file(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes),filters.count? &filters : NULL ,multi ,&files);
	if (files.count) {
		result = hl_alloc_array(&hlt_bytes, files.count);
		while(files.count) {
			files.count--;
			hl_aptr(result, vbyte*)[files.count] = (vbyte*) files.strings[files.count];
			free(files.strings[files.count]);
		}
		free(files.strings);
	}

	// clean up allocated mem. for filters:
	if (mask) {
		free(filters.descriptions);
		free(filters.extensions);
	}
	
	
	
	return result;
}
DEFINE_PRIM(_ARR, hl_dialogs_open_file, _STRING _STRING _DYN _BOOL);//note this

HL_PRIM vbyte* HL_NAME(hl_dialogs_folder)( vstring* title, vstring* msg ) {
	char * v;
	vbyte* result = NULL;
	result = NULL;
	v = systools_dialogs_folder(hl_to_utf8(title->bytes),hl_to_utf8(msg->bytes));
	return (vbyte*) v;

}
DEFINE_PRIM(_BYTES, hl_dialogs_folder, _STRING _STRING);


// ---------------- Clipboard methods ----------------------------------------


HL_PRIM int HL_NAME(hl_clipboard_set_text)( vstring* text ) {
	return systools_clipboard_set_text(hl_to_utf8(text->bytes));
}
DEFINE_PRIM(_I32, hl_clipboard_set_text, _STRING);


HL_PRIM vbyte* HL_NAME(hl_clipboard_get_text)() {
	char* v = systools_clipboard_get_text();
	return (vbyte*) v;
}
DEFINE_PRIM(_BYTES, hl_clipboard_get_text, _NO_ARG);


HL_PRIM void HL_NAME(hl_clipboard_clear)( ) {
	systools_clipboard_clear();
}
DEFINE_PRIM(_VOID, hl_clipboard_clear,_NO_ARG);


// ---------------- Miscellanious tools --------------------------------------


HL_PRIM int HL_NAME(hl_misc_get_key_state)( int key ) {
	int r;
	r = systools_misc_get_key_state(key);
	return r;
}
DEFINE_PRIM(_I32, misc_get_key_state, _I32);

// ---------------- Browser tools ---------------------------------------
HL_PRIM bool HL_NAME(hl_browser_launch)( vstring* url )
{
#ifndef HL_LINUX
	return systools_browser_launch(hl_to_utf8(url->bytes));
#else
	hl_error("this function is not available for this platform");
	return NULL;
#endif
}
DEFINE_PRIM(_BOOL, hl_browser_launch, _STRING);

// ---------------- File Utils ---------------------------------------
HL_PRIM vbyte* HL_NAME(hl_fileutils_get_temp_folder)()
{
	char * v;
	v = systools_fileutils_get_temp_folder();
	return (vbyte*) v;
}
DEFINE_PRIM(_BYTES, hl_fileutils_get_temp_folder, _NO_ARG);

// ---------------- Display tools --------------------

// Display specific code
HL_PRIM vdynamic* HL_NAME(hl_display_get_screen_size)()
{
#ifndef HL_LINUX
    dimensions dim;

	systools_display_get_screen_size(&dim);
	vdynamic* o = hl_make_dyn(&dim, &hlt_dyn);
	return o;
#else
	hl_error("function not available for this platform");
	return NULL;
#endif
}
DEFINE_PRIM(_DYN, hl_display_get_screen_size, _NO_ARG);

// ---------------- Registry tools --------------------------------------


HL_PRIM void HL_NAME(hl_registry_set_value)( int key, vstring* subkey, vstring* valuename, vstring* v) {
	systools_registry_set_value(key, hl_to_utf8(subkey->bytes), hl_to_utf8(valuename->bytes), hl_to_utf8(v->bytes));
}
DEFINE_PRIM(_VOID, hl_registry_set_value, _I32 _STRING _STRING _STRING);

HL_PRIM vbyte* HL_NAME(hl_registry_get_value)( int key, vstring* subkey, vstring* valuename) {
	char * v;
	v = systools_registry_get_value(key, hl_to_utf8(subkey->bytes), hl_to_utf8(valuename->bytes));
	return (vbyte*) v;
}
DEFINE_PRIM(_BYTES, hl_registry_get_value, _I32 _STRING _STRING);

HL_PRIM void HL_NAME(hl_registry_delete_key)( int key, vstring* subkey) {
	systools_registry_delete_key(key, hl_to_utf8(subkey->bytes));
}
DEFINE_PRIM(_VOID, hl_registry_delete_key, _I32 _STRING);


// -- Windows specific


#ifdef HL_WINDOWS

#include "win/win.h"
#include "win/menus.h"
#include "win/display.h"

HL_PRIM bool HL_NAME(hl_win_replace_exe_icon)( vstring* exe, vstring* icon, int iconResourceID) {
	int r = 0;
	r = systools_win_replaceExeIcon(hl_to_utf8(exe->bytes),hl_to_utf8(icon->bytes),iconResourceID);
	return r==1? true : false;
}
DEFINE_PRIM(_BOOL, hl_win_replace_exe_icon, _STRING _STRING _I32);

HL_PRIM int HL_NAME(hl_win_create_process)( vstring* app, vstring* args, vstring* wd, bool hide, bool wait) {
	int r;
	const char *_args = 0;
	const char *_wd = 0;
	if (args != NULL) {
		_args = hl_to_utf8(args->bytes);
	}
	if (wd != NULL) {
		_wd = hl_to_utf8(wd->bytes);
	}
	r = systools_win_create_process
		( hl_to_utf8(app->bytes)
		, _args
		, _wd
		, hide
		, wait
		);
	return r;
}
DEFINE_PRIM(_I32, hl_win_create_process, _STRING _STRING _STRING _BOOL _BOOL);


// Tray Icon specific code


static value systray_create_icon( value w, value iconpath, value tooltip )
{
	val_check(tooltip,string);
	if ( !(val_is_string(iconpath) || val_is_null(iconpath)) )
		val_throw(alloc_string(tray_icon_error));
	else {
		tray_icon *tray = systools_win_create_tray_icon(val_hwnd(w),val_string(iconpath),val_string(tooltip));
		if (!tray)
			val_throw(alloc_string(tray_icon_error));

		return alloc_abstract(k_tray_icon,tray);
	}
	return val_null;
}
DEFINE_PRIM(systray_create_icon,3);

static value systray_destroy_icon( value tray )
{
	val_check_kind(tray,k_tray_icon);
	systools_win_destroy_tray_icon(val_tray_icon(tray));
	return val_null;
}
DEFINE_PRIM(systray_destroy_icon,1);

static value systray_menu_callback()
{
	return alloc_abstract(k_window_msg_cb,&tray_menu_cb);
}
DEFINE_PRIM(systray_menu_callback,0);

// Menu specific code
static value win_menu_create()
{
	return alloc_abstract(k_menu,systools_menu_create());
}
DEFINE_PRIM(win_menu_create,0);

static value win_popup_menu_create()
{
	return alloc_abstract(k_menu,systools_popup_menu_create());
}
DEFINE_PRIM(win_popup_menu_create,0);

static void win_destroy_menu( value menu )
{
	val_check_kind(menu,k_menu);
	systools_menu_destroy(val_menu(menu));
}
DEFINE_PRIM(win_destroy_menu,1);

static value win_destroy_tray_icon( value ico )
{
	val_check_kind(ico,k_icondata);
	systools_win_destroy_tray_icon(val_tray_icon(ico));
	return val_null;
}
DEFINE_PRIM(win_destroy_tray_icon,1);

static value win_add_menu_item( value menu, value caption, value callbackid )
{
	val_check_kind(menu,k_menu);
	val_check(caption,string);
	val_check(callbackid,int);
	systools_menu_add_item(val_menu(menu), val_string(caption), val_int(callbackid));
	return val_null;
}
DEFINE_PRIM(win_add_menu_item,3);

static value win_add_menu_submenu( value menu, value submenu, value caption, value callbackid )
{
	val_check_kind(menu,k_menu);
	val_check_kind(submenu,k_menu);
	val_check(caption,string);
	val_check(callbackid,int);
	systools_menu_add_submenu(val_menu(menu), val_menu(submenu), val_string(caption), val_int(callbackid));
	return val_null;
}
DEFINE_PRIM(win_add_menu_submenu,4);

static value win_add_menu_divider( value menu, value callbackid )
{
	val_check_kind(menu,k_menu);
	val_check(callbackid,int);
	systools_menu_add_item(val_menu(menu), (char*)"--", val_int(callbackid));
	return val_null;
}
DEFINE_PRIM(win_add_menu_divider,2);

static value win_show_menu( value w, value m )
{
	val_check_kind(m,k_menu);
	return alloc_int(systools_menu_show( val_hwnd(w), val_menu(m) ));
}
DEFINE_PRIM(win_show_menu,2);

static value win_show_popup_menu( value w, value m )
{
	val_check_kind(m,k_menu);
	return alloc_int(systools_popup_menu_show( val_hwnd(w), val_menu(m) ));
}
DEFINE_PRIM(win_show_popup_menu,2);

static value display_set_mode( value width, value height, value depth )
{
	int r;
	val_check(width,int);
	val_check(height,int);
	val_check(depth,int);
	r=systools_win_display_set_mode(val_int(width),val_int(height),val_int(depth));
	return alloc_bool(r);
}
DEFINE_PRIM(display_set_mode,3);

static value display_set_default_mode()
{
	systools_win_display_set_default_mode();
	return val_null;
}
DEFINE_PRIM(display_set_default_mode,0);

static value display_is_mode_supported( value width, value height, value depth )
{
	int r;
	val_check(width,int);
	val_check(height,int);
	val_check(depth,int);
	r=systools_win_display_is_mode_supported(val_int(width),val_int(height),val_int(depth));
	return alloc_bool(r);
}
DEFINE_PRIM(display_is_mode_supported,3);

#endif
