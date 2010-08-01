#include <stdio.h>
#include <stdlib.h>

#include "../girara.h"

int setting_cb(girara_session_t* session, girara_setting_t* setting);

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  girara_session_t* session = girara_session_create();
  girara_session_init(session);

  int test_val_int = -1337;
  girara_setting_add(session, "test-val-int", &test_val_int, INT, FALSE, NULL, setting_cb);
  test_val_int = 42;
  girara_setting_set(session, "test-val-int", &test_val_int);

  girara_statusbar_item_t* item = girara_statusbar_item_add(session, TRUE, TRUE, TRUE, NULL);
  girara_statusbar_item_set_text(session, item, "girara-left");

  gtk_main();

  girara_session_destroy(session);
  
  return 0;
}

int setting_cb(girara_session_t* session, girara_setting_t* setting)
{
  printf("Changed setting '%s'!\n", setting->name);
  return 0;
}
