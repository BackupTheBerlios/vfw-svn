#include <gtk/gtk.h>


void
on_vfwfe_switch_monitor_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_vfwfe_switch_notifier_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_vfwfe_switch_logger_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_vfwfe_apply_direction_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_vfwfe_check_save_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_vfwfe_rule_accept_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_vfwfe_rule_cancel_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_vfwfe_rule_drop_clicked             (GtkButton       *button,
                                        gpointer         user_data);
