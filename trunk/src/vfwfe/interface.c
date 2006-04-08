#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component, widget, name) \
	g_object_set_data_full(G_OBJECT(component), name, \
			       gtk_widget_ref(widget), (GDestroyNotify)gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component, widget, name) \
	g_object_set_data(G_OBJECT(component), name, widget)

GtkWidget*
create_vfwfe_main (void)
{
  GtkWidget *vfwfe_main;
  GtkWidget *vfwfe_tab;
  GtkWidget *vbox1;
  GtkWidget *hbox1;
  GtkWidget *vfwfe_label_monitor;
  GtkWidget *vfwfe_led_monitor;
  GtkWidget *vfwfe_switch_monitor;
  GtkWidget *alignment2;
  GtkWidget *hbox11;
  GtkWidget *image5;
  GtkWidget *label14;
  GtkWidget *hbox2;
  GtkWidget *vfwfe_label_notifier;
  GtkWidget *vfwfe_led_notifier;
  GtkWidget *vfwfe_switch_notifier;
  GtkWidget *alignment3;
  GtkWidget *hbox12;
  GtkWidget *image6;
  GtkWidget *label15;
  GtkWidget *hbox3;
  GtkWidget *vfwfe_label_logger;
  GtkWidget *vfwfe_led_logger;
  GtkWidget *vfwfe_switch_logger;
  GtkWidget *alignment4;
  GtkWidget *hbox13;
  GtkWidget *image7;
  GtkWidget *label16;
  GtkWidget *hbox4;
  GtkWidget *vfwfe_label_direction;
  GtkWidget *vfwfe_check_in;
  GtkWidget *vfwfe_check_out;
  GtkWidget *vfwfe_apply_direction;
  GtkWidget *alignment1;
  GtkWidget *hbox10;
  GtkWidget *image4;
  GtkWidget *label13;
  GtkWidget *vfwfe_status;
  GtkWidget *empty_notebook_page;
  GtkWidget *vfwfe_rules;
  GtkWidget *vfwfe_info;
  GtkWidget *vfwfe_about;

  vfwfe_main = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (vfwfe_main), 5);
  gtk_window_set_title (GTK_WINDOW (vfwfe_main), "Visual Firewall");
  gtk_window_set_position (GTK_WINDOW (vfwfe_main), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable (GTK_WINDOW (vfwfe_main), FALSE);
  gtk_window_set_icon_name (GTK_WINDOW (vfwfe_main), "gtk-dialog-authentication");

  vfwfe_tab = gtk_notebook_new ();
  gtk_widget_show (vfwfe_tab);
  gtk_container_add (GTK_CONTAINER (vfwfe_main), vfwfe_tab);

  vbox1 = gtk_vbox_new (TRUE, 5);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (vfwfe_tab), vbox1);
  gtk_container_set_border_width (GTK_CONTAINER (vbox1), 5);

  hbox1 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

  vfwfe_label_monitor = gtk_label_new ("Monitor:");
  gtk_widget_show (vfwfe_label_monitor);
  gtk_box_pack_start (GTK_BOX (hbox1), vfwfe_label_monitor, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_monitor, 70, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_monitor), TRUE);

  vfwfe_led_monitor = gtk_image_new_from_stock ("gtk-no", GTK_ICON_SIZE_LARGE_TOOLBAR);
  gtk_widget_show (vfwfe_led_monitor);
  gtk_box_pack_start (GTK_BOX (hbox1), vfwfe_led_monitor, TRUE, TRUE, 0);

  vfwfe_switch_monitor = gtk_toggle_button_new ();
  gtk_widget_show (vfwfe_switch_monitor);
  gtk_box_pack_start (GTK_BOX (hbox1), vfwfe_switch_monitor, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_switch_monitor, 100, -1);

  alignment2 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment2);
  gtk_container_add (GTK_CONTAINER (vfwfe_switch_monitor), alignment2);

  hbox11 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox11);
  gtk_container_add (GTK_CONTAINER (alignment2), hbox11);

  image5 = gtk_image_new_from_stock ("gtk-execute", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image5);
  gtk_box_pack_start (GTK_BOX (hbox11), image5, FALSE, FALSE, 0);

  label14 = gtk_label_new_with_mnemonic ("Switch");
  gtk_widget_show (label14);
  gtk_box_pack_start (GTK_BOX (hbox11), label14, FALSE, FALSE, 0);

  hbox2 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox2, TRUE, TRUE, 0);

  vfwfe_label_notifier = gtk_label_new ("Notifier:");
  gtk_widget_show (vfwfe_label_notifier);
  gtk_box_pack_start (GTK_BOX (hbox2), vfwfe_label_notifier, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_notifier, 70, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_notifier), TRUE);

  vfwfe_led_notifier = gtk_image_new_from_stock ("gtk-no", GTK_ICON_SIZE_LARGE_TOOLBAR);
  gtk_widget_show (vfwfe_led_notifier);
  gtk_box_pack_start (GTK_BOX (hbox2), vfwfe_led_notifier, TRUE, TRUE, 0);

  vfwfe_switch_notifier = gtk_toggle_button_new ();
  gtk_widget_show (vfwfe_switch_notifier);
  gtk_box_pack_start (GTK_BOX (hbox2), vfwfe_switch_notifier, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_switch_notifier, 100, -1);

  alignment3 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment3);
  gtk_container_add (GTK_CONTAINER (vfwfe_switch_notifier), alignment3);

  hbox12 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox12);
  gtk_container_add (GTK_CONTAINER (alignment3), hbox12);

  image6 = gtk_image_new_from_stock ("gtk-execute", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image6);
  gtk_box_pack_start (GTK_BOX (hbox12), image6, FALSE, FALSE, 0);

  label15 = gtk_label_new_with_mnemonic ("Switch");
  gtk_widget_show (label15);
  gtk_box_pack_start (GTK_BOX (hbox12), label15, FALSE, FALSE, 0);

  hbox3 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox3);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox3, TRUE, TRUE, 0);

  vfwfe_label_logger = gtk_label_new ("Logger:");
  gtk_widget_show (vfwfe_label_logger);
  gtk_box_pack_start (GTK_BOX (hbox3), vfwfe_label_logger, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_logger, 70, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_logger), TRUE);

  vfwfe_led_logger = gtk_image_new_from_stock ("gtk-no", GTK_ICON_SIZE_LARGE_TOOLBAR);
  gtk_widget_show (vfwfe_led_logger);
  gtk_box_pack_start (GTK_BOX (hbox3), vfwfe_led_logger, TRUE, TRUE, 0);

  vfwfe_switch_logger = gtk_toggle_button_new ();
  gtk_widget_show (vfwfe_switch_logger);
  gtk_box_pack_start (GTK_BOX (hbox3), vfwfe_switch_logger, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_switch_logger, 100, -1);

  alignment4 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment4);
  gtk_container_add (GTK_CONTAINER (vfwfe_switch_logger), alignment4);

  hbox13 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox13);
  gtk_container_add (GTK_CONTAINER (alignment4), hbox13);

  image7 = gtk_image_new_from_stock ("gtk-execute", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image7);
  gtk_box_pack_start (GTK_BOX (hbox13), image7, FALSE, FALSE, 0);

  label16 = gtk_label_new_with_mnemonic ("Switch");
  gtk_widget_show (label16);
  gtk_box_pack_start (GTK_BOX (hbox13), label16, FALSE, FALSE, 0);

  hbox4 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox4);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox4, TRUE, TRUE, 0);

  vfwfe_label_direction = gtk_label_new ("Direction(s):");
  gtk_widget_show (vfwfe_label_direction);
  gtk_box_pack_start (GTK_BOX (hbox4), vfwfe_label_direction, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_direction, 70, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_direction), TRUE);

  vfwfe_check_in = gtk_check_button_new_with_mnemonic ("Input");
  gtk_widget_show (vfwfe_check_in);
  gtk_box_pack_start (GTK_BOX (hbox4), vfwfe_check_in, TRUE, TRUE, 0);

  vfwfe_check_out = gtk_check_button_new_with_mnemonic ("Output");
  gtk_widget_show (vfwfe_check_out);
  gtk_box_pack_start (GTK_BOX (hbox4), vfwfe_check_out, TRUE, TRUE, 0);

  vfwfe_apply_direction = gtk_button_new ();
  gtk_widget_show (vfwfe_apply_direction);
  gtk_box_pack_start (GTK_BOX (hbox4), vfwfe_apply_direction, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_apply_direction, 100, -1);

  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (vfwfe_apply_direction), alignment1);

  hbox10 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox10);
  gtk_container_add (GTK_CONTAINER (alignment1), hbox10);

  image4 = gtk_image_new_from_stock ("gtk-apply", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image4);
  gtk_box_pack_start (GTK_BOX (hbox10), image4, FALSE, FALSE, 0);

  label13 = gtk_label_new_with_mnemonic ("Apply");
  gtk_widget_show (label13);
  gtk_box_pack_start (GTK_BOX (hbox10), label13, FALSE, FALSE, 0);

  vfwfe_status = gtk_label_new ("Status");
  gtk_widget_show (vfwfe_status);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (vfwfe_tab), gtk_notebook_get_nth_page (GTK_NOTEBOOK (vfwfe_tab), 0), vfwfe_status);
  gtk_label_set_justify (GTK_LABEL (vfwfe_status), GTK_JUSTIFY_CENTER);

  empty_notebook_page = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (empty_notebook_page);
  gtk_container_add (GTK_CONTAINER (vfwfe_tab), empty_notebook_page);

  vfwfe_rules = gtk_label_new ("Rules");
  gtk_widget_show (vfwfe_rules);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (vfwfe_tab), gtk_notebook_get_nth_page (GTK_NOTEBOOK (vfwfe_tab), 1), vfwfe_rules);
  gtk_label_set_justify (GTK_LABEL (vfwfe_rules), GTK_JUSTIFY_CENTER);

  vfwfe_info = gtk_label_new ("Visual Firewall FE\nCopyright (C) 2006 Nguyen Minh Nhat\nHomepage: http://vfw.berlios.de\nLicense: GPL");
  gtk_widget_show (vfwfe_info);
  gtk_container_add (GTK_CONTAINER (vfwfe_tab), vfwfe_info);
  gtk_label_set_justify (GTK_LABEL (vfwfe_info), GTK_JUSTIFY_CENTER);

  vfwfe_about = gtk_label_new ("About");
  gtk_widget_show (vfwfe_about);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (vfwfe_tab), gtk_notebook_get_nth_page (GTK_NOTEBOOK (vfwfe_tab), 2), vfwfe_about);
  gtk_label_set_justify (GTK_LABEL (vfwfe_about), GTK_JUSTIFY_CENTER);

  g_signal_connect ((gpointer) vfwfe_main, "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_switch_monitor, "toggled",
                    G_CALLBACK (on_vfwfe_switch_monitor_toggled),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_switch_notifier, "toggled",
                    G_CALLBACK (on_vfwfe_switch_notifier_toggled),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_switch_logger, "toggled",
                    G_CALLBACK (on_vfwfe_switch_logger_toggled),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_apply_direction, "clicked",
                    G_CALLBACK (on_vfwfe_apply_direction_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (vfwfe_main, vfwfe_main, "vfwfe_main");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_tab, "vfwfe_tab");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_label_monitor, "vfwfe_label_monitor");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_led_monitor, "vfwfe_led_monitor");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_switch_monitor, "vfwfe_switch_monitor");
  GLADE_HOOKUP_OBJECT (vfwfe_main, alignment2, "alignment2");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox11, "hbox11");
  GLADE_HOOKUP_OBJECT (vfwfe_main, image5, "image5");
  GLADE_HOOKUP_OBJECT (vfwfe_main, label14, "label14");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_label_notifier, "vfwfe_label_notifier");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_led_notifier, "vfwfe_led_notifier");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_switch_notifier, "vfwfe_switch_notifier");
  GLADE_HOOKUP_OBJECT (vfwfe_main, alignment3, "alignment3");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox12, "hbox12");
  GLADE_HOOKUP_OBJECT (vfwfe_main, image6, "image6");
  GLADE_HOOKUP_OBJECT (vfwfe_main, label15, "label15");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_label_logger, "vfwfe_label_logger");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_led_logger, "vfwfe_led_logger");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_switch_logger, "vfwfe_switch_logger");
  GLADE_HOOKUP_OBJECT (vfwfe_main, alignment4, "alignment4");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox13, "hbox13");
  GLADE_HOOKUP_OBJECT (vfwfe_main, image7, "image7");
  GLADE_HOOKUP_OBJECT (vfwfe_main, label16, "label16");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_label_direction, "vfwfe_label_direction");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_check_in, "vfwfe_check_in");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_check_out, "vfwfe_check_out");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_apply_direction, "vfwfe_apply_direction");
  GLADE_HOOKUP_OBJECT (vfwfe_main, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT (vfwfe_main, hbox10, "hbox10");
  GLADE_HOOKUP_OBJECT (vfwfe_main, image4, "image4");
  GLADE_HOOKUP_OBJECT (vfwfe_main, label13, "label13");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_status, "vfwfe_status");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_rules, "vfwfe_rules");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_info, "vfwfe_info");
  GLADE_HOOKUP_OBJECT (vfwfe_main, vfwfe_about, "vfwfe_about");

  return vfwfe_main;
}

GtkWidget*
create_vfwfe_alert_out (void)
{
  GtkWidget *vfwfe_alert_out;
  GtkWidget *dialog_vbox1;
  GtkWidget *vbox2;
  GtkWidget *hbox5;
  GtkWidget *vfwfe_label_pid;
  GtkWidget *vfwfe_entry_pid;
  GtkWidget *hbox6;
  GtkWidget *vfwfe_label_path;
  GtkWidget *vfwfe_entry_path;
  GtkWidget *hbox7;
  GtkWidget *vfwfe_label_checksum;
  GtkWidget *vfwfe_entry_checksum;
  GtkWidget *hbox8;
  GtkWidget *vfwfe_label_dest_ip;
  GtkWidget *vfwfe_entry_dest_ip;
  GtkWidget *hbox9;
  GtkWidget *vfwfe_label_dest_port;
  GtkWidget *vfwfe_entry_dest_port;
  GtkWidget *vfwfe_check_save;
  GtkWidget *alignment5;
  GtkWidget *hbox15;
  GtkWidget *image8;
  GtkWidget *label18;
  GtkWidget *vfwfe_label_ask;
  GtkWidget *dialog_action_area1;
  GtkWidget *vfwfe_rule_accept;
  GtkWidget *alignment6;
  GtkWidget *hbox16;
  GtkWidget *image9;
  GtkWidget *label19;
  GtkWidget *vfwfe_rule_cancel;
  GtkWidget *vfwfe_rule_drop;
  GtkWidget *alignment7;
  GtkWidget *hbox17;
  GtkWidget *image10;
  GtkWidget *label20;

  vfwfe_alert_out = gtk_dialog_new ();
  gtk_widget_set_size_request (vfwfe_alert_out, 500, -1);
  gtk_container_set_border_width (GTK_CONTAINER (vfwfe_alert_out), 5);
  gtk_window_set_title (GTK_WINDOW (vfwfe_alert_out), "New connection");
  gtk_window_set_resizable (GTK_WINDOW (vfwfe_alert_out), FALSE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (vfwfe_alert_out), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (vfwfe_alert_out), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox1 = GTK_DIALOG (vfwfe_alert_out)->vbox;
  gtk_widget_show (dialog_vbox1);

  vbox2 = gtk_vbox_new (TRUE, 5);
  gtk_widget_show (vbox2);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), vbox2, TRUE, TRUE, 0);

  hbox5 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox5);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox5, TRUE, TRUE, 0);

  vfwfe_label_pid = gtk_label_new ("PID:");
  gtk_widget_show (vfwfe_label_pid);
  gtk_box_pack_start (GTK_BOX (hbox5), vfwfe_label_pid, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_pid, 100, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_pid), TRUE);

  vfwfe_entry_pid = gtk_entry_new ();
  gtk_widget_show (vfwfe_entry_pid);
  gtk_box_pack_start (GTK_BOX (hbox5), vfwfe_entry_pid, TRUE, TRUE, 0);
  gtk_editable_set_editable (GTK_EDITABLE (vfwfe_entry_pid), FALSE);

  hbox6 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox6);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox6, TRUE, TRUE, 0);

  vfwfe_label_path = gtk_label_new ("Path:");
  gtk_widget_show (vfwfe_label_path);
  gtk_box_pack_start (GTK_BOX (hbox6), vfwfe_label_path, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_path, 100, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_path), TRUE);

  vfwfe_entry_path = gtk_entry_new ();
  gtk_widget_show (vfwfe_entry_path);
  gtk_box_pack_start (GTK_BOX (hbox6), vfwfe_entry_path, TRUE, TRUE, 0);
  gtk_editable_set_editable (GTK_EDITABLE (vfwfe_entry_path), FALSE);

  hbox7 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox7, TRUE, TRUE, 0);

  vfwfe_label_checksum = gtk_label_new ("Checksum:");
  gtk_widget_show (vfwfe_label_checksum);
  gtk_box_pack_start (GTK_BOX (hbox7), vfwfe_label_checksum, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_checksum, 100, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_checksum), TRUE);

  vfwfe_entry_checksum = gtk_entry_new ();
  gtk_widget_show (vfwfe_entry_checksum);
  gtk_box_pack_start (GTK_BOX (hbox7), vfwfe_entry_checksum, TRUE, TRUE, 0);
  gtk_editable_set_editable (GTK_EDITABLE (vfwfe_entry_checksum), FALSE);

  hbox8 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox8);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox8, TRUE, TRUE, 0);

  vfwfe_label_dest_ip = gtk_label_new ("Destination IP:");
  gtk_widget_show (vfwfe_label_dest_ip);
  gtk_box_pack_start (GTK_BOX (hbox8), vfwfe_label_dest_ip, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_dest_ip, 100, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_dest_ip), TRUE);

  vfwfe_entry_dest_ip = gtk_entry_new ();
  gtk_widget_show (vfwfe_entry_dest_ip);
  gtk_box_pack_start (GTK_BOX (hbox8), vfwfe_entry_dest_ip, TRUE, TRUE, 0);
  gtk_editable_set_editable (GTK_EDITABLE (vfwfe_entry_dest_ip), FALSE);

  hbox9 = gtk_hbox_new (FALSE, 5);
  gtk_widget_show (hbox9);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox9, TRUE, TRUE, 0);

  vfwfe_label_dest_port = gtk_label_new ("Destination Port:");
  gtk_widget_show (vfwfe_label_dest_port);
  gtk_box_pack_start (GTK_BOX (hbox9), vfwfe_label_dest_port, FALSE, TRUE, 0);
  gtk_widget_set_size_request (vfwfe_label_dest_port, 100, -1);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_dest_port), TRUE);

  vfwfe_entry_dest_port = gtk_entry_new ();
  gtk_widget_show (vfwfe_entry_dest_port);
  gtk_box_pack_start (GTK_BOX (hbox9), vfwfe_entry_dest_port, TRUE, TRUE, 0);
  gtk_editable_set_editable (GTK_EDITABLE (vfwfe_entry_dest_port), FALSE);

  vfwfe_check_save = gtk_check_button_new ();
  gtk_widget_show (vfwfe_check_save);
  gtk_box_pack_start (GTK_BOX (vbox2), vfwfe_check_save, TRUE, TRUE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (vfwfe_check_save), TRUE);

  alignment5 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment5);
  gtk_container_add (GTK_CONTAINER (vfwfe_check_save), alignment5);

  hbox15 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox15);
  gtk_container_add (GTK_CONTAINER (alignment5), hbox15);

  image8 = gtk_image_new_from_stock ("gtk-save", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image8);
  gtk_box_pack_start (GTK_BOX (hbox15), image8, FALSE, FALSE, 0);

  label18 = gtk_label_new_with_mnemonic ("Save to rule list");
  gtk_widget_show (label18);
  gtk_box_pack_start (GTK_BOX (hbox15), label18, FALSE, FALSE, 0);

  vfwfe_label_ask = gtk_label_new ("Do you want to connect?");
  gtk_widget_show (vfwfe_label_ask);
  gtk_box_pack_start (GTK_BOX (vbox2), vfwfe_label_ask, TRUE, TRUE, 0);
  gtk_label_set_justify (GTK_LABEL (vfwfe_label_ask), GTK_JUSTIFY_CENTER);
  gtk_label_set_line_wrap (GTK_LABEL (vfwfe_label_ask), TRUE);

  dialog_action_area1 = GTK_DIALOG (vfwfe_alert_out)->action_area;
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_SPREAD);

  vfwfe_rule_accept = gtk_button_new ();
  gtk_widget_show (vfwfe_rule_accept);
  gtk_dialog_add_action_widget (GTK_DIALOG (vfwfe_alert_out), vfwfe_rule_accept, GTK_RESPONSE_APPLY);
  gtk_widget_set_size_request (vfwfe_rule_accept, 100, -1);
  GTK_WIDGET_SET_FLAGS (vfwfe_rule_accept, GTK_CAN_DEFAULT);

  alignment6 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment6);
  gtk_container_add (GTK_CONTAINER (vfwfe_rule_accept), alignment6);

  hbox16 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox16);
  gtk_container_add (GTK_CONTAINER (alignment6), hbox16);

  image9 = gtk_image_new_from_stock ("gtk-yes", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image9);
  gtk_box_pack_start (GTK_BOX (hbox16), image9, FALSE, FALSE, 0);

  label19 = gtk_label_new_with_mnemonic ("Accept");
  gtk_widget_show (label19);
  gtk_box_pack_start (GTK_BOX (hbox16), label19, FALSE, FALSE, 0);

  vfwfe_rule_cancel = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (vfwfe_rule_cancel);
  gtk_dialog_add_action_widget (GTK_DIALOG (vfwfe_alert_out), vfwfe_rule_cancel, GTK_RESPONSE_CANCEL);
  gtk_widget_set_size_request (vfwfe_rule_cancel, 100, -1);
  GTK_WIDGET_SET_FLAGS (vfwfe_rule_cancel, GTK_CAN_DEFAULT);

  vfwfe_rule_drop = gtk_button_new ();
  gtk_widget_show (vfwfe_rule_drop);
  gtk_dialog_add_action_widget (GTK_DIALOG (vfwfe_alert_out), vfwfe_rule_drop, GTK_RESPONSE_OK);
  gtk_widget_set_size_request (vfwfe_rule_drop, 100, -1);
  GTK_WIDGET_SET_FLAGS (vfwfe_rule_drop, GTK_CAN_DEFAULT);

  alignment7 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment7);
  gtk_container_add (GTK_CONTAINER (vfwfe_rule_drop), alignment7);

  hbox17 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox17);
  gtk_container_add (GTK_CONTAINER (alignment7), hbox17);

  image10 = gtk_image_new_from_stock ("gtk-no", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image10);
  gtk_box_pack_start (GTK_BOX (hbox17), image10, FALSE, FALSE, 0);

  label20 = gtk_label_new_with_mnemonic ("Drop");
  gtk_widget_show (label20);
  gtk_box_pack_start (GTK_BOX (hbox17), label20, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) vfwfe_alert_out, "destroy",
                    G_CALLBACK (gtk_widget_destroy),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_check_save, "toggled",
                    G_CALLBACK (on_vfwfe_check_save_toggled),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_rule_accept, "clicked",
                    G_CALLBACK (on_vfwfe_rule_accept_clicked),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_rule_cancel, "clicked",
                    G_CALLBACK (on_vfwfe_rule_cancel_clicked),
                    NULL);
  g_signal_connect ((gpointer) vfwfe_rule_drop, "clicked",
                    G_CALLBACK (on_vfwfe_rule_drop_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (vfwfe_alert_out, vfwfe_alert_out, "vfwfe_alert_out");
  GLADE_HOOKUP_OBJECT_NO_REF (vfwfe_alert_out, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox5, "hbox5");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_label_pid, "vfwfe_label_pid");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_entry_pid, "vfwfe_entry_pid");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox6, "hbox6");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_label_path, "vfwfe_label_path");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_entry_path, "vfwfe_entry_path");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox7, "hbox7");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_label_checksum, "vfwfe_label_checksum");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_entry_checksum, "vfwfe_entry_checksum");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox8, "hbox8");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_label_dest_ip, "vfwfe_label_dest_ip");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_entry_dest_ip, "vfwfe_entry_dest_ip");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox9, "hbox9");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_label_dest_port, "vfwfe_label_dest_port");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_entry_dest_port, "vfwfe_entry_dest_port");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_check_save, "vfwfe_check_save");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, alignment5, "alignment5");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox15, "hbox15");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, image8, "image8");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, label18, "label18");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_label_ask, "vfwfe_label_ask");
  GLADE_HOOKUP_OBJECT_NO_REF (vfwfe_alert_out, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_rule_accept, "vfwfe_rule_accept");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, alignment6, "alignment6");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox16, "hbox16");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, image9, "image9");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, label19, "label19");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_rule_cancel, "vfwfe_rule_cancel");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, vfwfe_rule_drop, "vfwfe_rule_drop");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, alignment7, "alignment7");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, hbox17, "hbox17");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, image10, "image10");
  GLADE_HOOKUP_OBJECT (vfwfe_alert_out, label20, "label20");

  return vfwfe_alert_out;
}

