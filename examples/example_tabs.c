/* See LICENSE file for license and copyright information */

#include <stdio.h>
#include <stdlib.h>

#include "../girara.h"

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  girara_session_t* session = girara_session_create();

	if (session == NULL) {
		return -1;
	}

  if (girara_session_init(session) == false) {
		girara_session_destroy(session);
		return -1;
	}

	/* enable tabs */
	girara_tabs_enable(session);

	GtkWidget* tab_1_widget = gtk_text_view_new();
	GtkTextBuffer* buffer_1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab_1_widget));
	gtk_text_buffer_set_text (buffer_1, "Tab 1", -1);
	girara_tab_new(session, NULL, tab_1_widget, false, NULL);

	GtkWidget* tab_2_widget = gtk_text_view_new();
	GtkTextBuffer* buffer_2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab_2_widget));
	gtk_text_buffer_set_text (buffer_2, "Tab 2", -1);
	girara_tab_new(session, "Tab 2", tab_2_widget, false, NULL);

  gtk_main();

  girara_session_destroy(session);

  return 0;
}
