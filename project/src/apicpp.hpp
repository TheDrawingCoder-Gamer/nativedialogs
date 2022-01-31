#ifndef _SYSTOOLS_APICPP_HPP
#define _SYSTOOLS_APICPP_HPP

#include <hxcpp.h>
#include "api.h"

static void systools_init();

static void dialogs_message_box(::String title, ::String msg, bool error);
static bool dialogs_dialog_box(::String title, ::String msg, bool error);
static ::String dialogs_save_file(::String title, ::String msg, ::String initialdir, ARG_FILEFILTERS* mask);
static ::Array<::String> dialogs_open_file(::String title, ::String msg, ARG_FILEFILTERS* mask, bool multi);
static ::String dialogs_folder(::String title, ::String msg);
static ARG_FILEFILTERS* new_filefilters(int count, ::Array<::String> descriptions, ::Array<::String> extensions);
#endif // _SYSTOOLS_APICPP_HPP