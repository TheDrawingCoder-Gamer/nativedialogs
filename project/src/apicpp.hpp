#ifndef APICPP_HPP
#define APICPP_HPP

#include "api.h"
static void systools_init();

static void dialogs_message_box(const char* title, const char* msg, bool error);
static bool dialogs_dialog_box(const char* title, const char* msg, bool error);
static const char* dialogs_save_file(const char* title, const char* msg, const char* initialdir, ARG_FILEFILTERS* mask);
static const char** dialogs_open_file(const char* title, const char* msg, ARG_FILEFILTERS* mask, bool multi);
static const char *dialogs_folder(const char* title, const char* msg);

#endif // APICPP_HPP