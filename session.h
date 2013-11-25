/* See LICENSE file for license and copyright information */

#ifndef GIRARA_SESSION_H
#define GIRARA_SESSION_H

#include "types.h"
#include "macros.h"
#include "callbacks.h"

#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <gdk/gdkkeysyms.h>

struct girara_session_s
{
  struct
  {
    GtkWidget       *window; /**< The main window of the application */
    GtkBox          *box; /**< A box that contains all widgets */
    GtkWidget       *view; /**< The view area of the applications widgets */
    GtkWidget       *viewport; /**< The viewport of view */
    GtkWidget       *statusbar; /**< The statusbar */
    GtkBox          *statusbar_entries; /**< Statusbar entry box */
    GtkWidget       *notification_area; /**< The notification area */
    GtkWidget       *notification_text; /**< The notification entry */
    GtkWidget       *tabbar; /**< The tabbar */
    GtkBox          *inputbar_box; /**< Inputbar box */
    GtkWidget       *inputbar; /**< Inputbar event box */
    GtkLabel        *inputbar_dialog; /**< Inputbar dialog */
    GtkEntry        *inputbar_entry; /**< Inputbar entry */
    GtkNotebook     *tabs; /**< The tabs notebook */
    GtkBox          *results; /**< Completion results */
    Window          embed; /**< Embedded window */
  } gtk;

  struct
  {
    GdkRGBA default_foreground; /**< The default foreground color */
    GdkRGBA default_background; /**< The default background color */
    GdkRGBA inputbar_foreground; /**< The foreground color of the inputbar */
    GdkRGBA inputbar_background; /**< The background color of the inputbar */
    GdkRGBA statusbar_foreground; /**< The foreground color of the statusbar */
    GdkRGBA statusbar_background; /**< The background color of the statusbar */
    GdkRGBA completion_foreground; /**< The foreground color of a completion item */
    GdkRGBA completion_background; /**< The background color of a completion item */
    GdkRGBA completion_group_foreground; /**< The foreground color of a completion group entry */
    GdkRGBA completion_group_background; /**< The background color of a completion group entry */
    GdkRGBA completion_highlight_foreground; /**< The foreground color of a highlighted completion item */
    GdkRGBA completion_highlight_background; /**< The background color of a highlighted completion item */
    GdkRGBA notification_error_foreground; /**< The foreground color of an error notification */
    GdkRGBA notification_error_background; /**< The background color of an error notification */
    GdkRGBA notification_warning_foreground; /**< The foreground color of a warning notification */
    GdkRGBA notification_warning_background; /**< The background color of a warning notification */
    GdkRGBA notification_default_foreground; /**< The foreground color of a default notification */
    GdkRGBA notification_default_background; /**< The background color of a default notification */
    GdkRGBA tabbar_foreground; /**< The foreground color for a tab */
    GdkRGBA tabbar_background; /**< The background color for a tab */
    GdkRGBA tabbar_focus_foreground; /**< The foreground color for a focused tab */
    GdkRGBA tabbar_focus_background; /**< The background color for a focused tab */
    PangoFontDescription *font; /**< The used font */
  } style;

  struct
  {
    girara_list_t* mouse_events; /**< List of mouse events */
    girara_list_t* commands; /**< List of commands */
    girara_list_t* shortcuts; /**< List of shortcuts */
    girara_list_t* special_commands; /**< List of special commands */
    girara_list_t* inputbar_shortcuts; /**< List of inputbar shortcuts */
  } bindings;

  struct
  {
    girara_list_t* statusbar_items; /**< List of statusbar items */
  } elements;

  /**
   * List of settings (deprecated)
   */
  girara_list_t* GIRARA_DEPRECATED(settings);

  struct
  {
    int inputbar_activate; /**< Inputbar activation */
    int inputbar_key_pressed; /**< Pressed key in inputbar */
    int inputbar_changed; /**< Inputbar text changed */
    int view_key_pressed; /**< Pressed key in view */
    int view_button_press_event; /**< Pressed button */
    int view_button_release_event; /**< Released button */
    int view_motion_notify_event; /**< Cursor movement event */
    int view_scroll_event; /**< Scroll event */
    girara_callback_inputbar_activate_t inputbar_custom_activate; /**< Custom handler */
    girara_callback_inputbar_key_press_event_t inputbar_custom_key_press_event; /**< Custom handler */
    void* inputbar_custom_data; /**< Data for custom handler */
  } signals;

  struct
  {
    void (*buffer_changed)(girara_session_t* session); /**< Buffer changed */
    bool (*unknown_command)(girara_session_t* session, const char* input); /**< Unknown command */
  } events;

  struct
  {
    GString *buffer; /**< Buffer */
    void* data; /**< User data */
    girara_list_t* GIRARA_DEPRECATED(command_history); /**< Command history (deprecated) */
    bool autohide_inputbar; /**< Auto-hide inputbar */
    bool hide_statusbar; /**< Hide statusbar */
  } global;

  struct
  {
    girara_mode_t current_mode; /**< Current mode */
    girara_list_t *identifiers; /**< List of modes with its string identifiers */
    girara_mode_t normal; /**< The normal mode */
    girara_mode_t inputbar; /**< The inputbar mode */
  } modes;

  struct
  {
    int n; /**< Numeric buffer */
    GString *command; /**< Command in buffer */
  } buffer;

  struct
  {
    girara_list_t* handles;
    girara_list_t* shortcut_mappings;
    girara_list_t* argument_mappings;
  } config;

  GiraraInputHistory* command_history; /**< Command history */
  girara_session_private_t* private_data; /**< Private data of a girara session */
};

/**
 * Creates a girara session
 *
 * @return A valid session object
 * @return NULL when an error occured
 */
girara_session_t* girara_session_create();

/**
 * Initializes an girara session
 *
 * @param session The used girara session
 * @param appname Name of the session (can be NULL)
 * @return TRUE No error occured
 * @return FALSE An error occured
 */
bool girara_session_init(girara_session_t* session, const char* appname);

/**
 * Destroys an girara session
 *
 * @param session The used girara session
 * @return TRUE No error occured
 * @return FALSE An error occured
 */
bool girara_session_destroy(girara_session_t* session);

/**
 * Sets the view widget of girara
 *
 * @param session The used girara session
 * @param widget The widget that should be displayed
 * @return TRUE No error occured
 * @return FALSE An error occured
 */
bool girara_set_view(girara_session_t* session, GtkWidget* widget);

/**
 * Returns a copy of the buffer
 *
 * @param session The used girara session
 * @return Copy of the current buffer
 */
char* girara_buffer_get(girara_session_t* session);

/**
 * Displays a notification for the user. It is possible to pass GIRARA_INFO,
 * GIRARA_WARNING or GIRARA_ERROR as a notification level.
 *
 * @param session The girara session
 * @param level The level
 * @param format String format
 * @param ...
 */
void girara_notify(girara_session_t* session, int level,
    const char* format, ...) GIRARA_PRINTF(3, 4);

/**
 * Creates a girara dialog
 *
 * @param session The girara session
 * @param dialog The dialog message
 * @param invisible Sets the input visibility
 * @param key_press_event Callback function to a custom key press event handler
 * @param activate_event Callback function to a custom activate event handler
 * @param data Custom data that is passed to the callback functions
 */
void girara_dialog(girara_session_t* session, const char* dialog, bool
    invisible, girara_callback_inputbar_key_press_event_t key_press_event,
    girara_callback_inputbar_activate_t activate_event, void* data);

/**
 * Adds a new mode by its string identifier
 *
 * @param session The used girara session
 * @param name The string identifier used in configs/inputbar etc to refer by
 * @return A newly defined girara_mode_t associated with name
 */
girara_mode_t girara_mode_add(girara_session_t* session, const char* name);

/**
 * Sets the current mode
 *
 * @param session The used girara session
 * @param mode The new mode
 */
void girara_mode_set(girara_session_t* session, girara_mode_t mode);

/**
 * Returns the current mode
 *
 * @param session The used girara session
 * @return The current mode
 */
girara_mode_t girara_mode_get(girara_session_t* session);

/**
 * Set name of the window title
 *
 * @param session The used girara session
 * @param name The new name of the session
 * @return true if no error occured
 * @return false if an error occured
 */
bool girara_set_window_title(girara_session_t* session, const char* name);

/**
 * Returns the command history
 *
 * @param session The used girara session
 * @return The command history (list of strings) or NULL
 */
girara_list_t* girara_get_command_history(girara_session_t* session);

#endif
