/*
 * Visual Firewall Monitor
 * Copyright (C) 2006 Nguyen Minh Nhat <ngmnhat@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */ 

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

void on_vfwfe_switch_monitor_toggled(GtkToggleButton *togglebutton,
				     gpointer user_data)
{
}

void on_vfwfe_switch_notifier_toggled(GtkToggleButton *togglebutton,
				      gpointer user_data)
{
}

void on_vfwfe_switch_logger_toggled(GtkToggleButton *togglebutton,
				    gpointer user_data)
{
}

void on_vfwfe_apply_direction_clicked(GtkButton *button,
				      gpointer user_data)
{
}

void on_vfwfe_check_save_toggled(GtkToggleButton *togglebutton,
				 gpointer user_data)
{
}

void on_vfwfe_rule_accept_clicked(GtkButton *button,
				  gpointer user_data)
{
}

void on_vfwfe_rule_cancel_clicked(GtkButton *button,
				  gpointer user_data)
{
	GtkWidget *vfwfe_alert_out;

	vfwfe_alert_out = lookup_widget(GTK_WIDGET(button), "vfwfe_alert_out");
	gtk_widget_destroy(vfwfe_alert_out);
}

void on_vfwfe_rule_drop_clicked(GtkButton *button,
				gpointer user_data)
{
}

