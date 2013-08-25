/* decode_as_dcerpc.h
 *
 * $Id: decode_as_dcerpc.h 43536 2012-06-28 22:56:06Z darkjames $
 *
 * Routines to modify dcerpc bindings on the fly.
 * Only internally used between decode_as_dlg and decode_as_dcerpc
 *
 * Copyright 2004 Ulf Lamping
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef __DECODE_AS_DCERPC_H__
#define __DECODE_AS_DCERPC_H__

/** @file
 *  "Decode As" / "User Specified Decodes" dialog box.
 *  @ingroup dialog_group
 */


/*
 * Columns for a "Select" list.
 * Note that most of these columns aren't displayed; they're attached
 * to the row of the table as additional information.
 */
#define E_LIST_S_PROTO_NAME 0
#define E_LIST_S_TABLE	    1
/* The following is for debugging in decode_add_to_list */
#define E_LIST_S_MAX	    E_LIST_S_TABLE
#define E_LIST_S_COLUMNS   (E_LIST_S_MAX + 1)

#define E_PAGE_LIST   "notebook_page_list"
#define E_PAGE_TABLE  "notebook_page_table_name"
#define E_PAGE_TITLE  "notebook_page_title"
#define E_PAGE_VALUE  "notebook_page_value"

#define E_PAGE_ACTION "notebook_page_action"

#define E_PAGE_DCERPC "notebook_page_dcerpc" /* dcerpc only */
#define E_PAGE_BINDING "notebook_page_binding" /* dcerpc only */


/*
 * Enum used to track which radio button is currently selected in the
 * dialog. These buttons are labeled "Decode" and "Do not decode".
 */
enum action_type {
    /* The "Decode" button is currently selected. */
    E_DECODE_YES,

    /* The "Do not decode" button is currently selected. */
    E_DECODE_NO
};

extern enum action_type	requested_action;

/*
 * A list of the dialog items that only have meaning when the user has
 * selected the "Decode" radio button.  When the "Do not decode"
 * button is selected these items should be dimmed.
 */
extern GSList *decode_dimmable;

/* init decode_dcerpc internals */
extern void decode_dcerpc_init(void);

/* remove all bindings */
extern void decode_dcerpc_reset_all(void);

extern void
decode_dcerpc_add_show_list(gpointer user_data);

extern GtkWidget *
decode_dcerpc_add_page(packet_info *pinfo);

extern void
decode_dcerpc_binding_free(void *binding);



/** Add an item the the Show list.
 */
extern void
decode_add_to_show_list (
gpointer list_data, 
const gchar *table_name, 
gchar *selector_name, 
const gchar *initial_proto_name, 
const gchar *current_proto_name);


/*
 * This routine creates one entry in the list of protocol dissector
 * that can be used.  It is called by the dissector_table_foreach_handle
 * routine once for each entry in a dissector table's list of handles
 * for dissectors that could be used in that table.  It guarantees unique
 * entries by iterating over the list of entries build up to this point,
 * looking for a duplicate name.  If there is no duplicate, then this
 * entry is added to the list of possible dissectors.
 *
 * @param table_name The name of the dissector table currently
 * being walked.
 *
 * @param value The dissector handle for this entry.  This is an opaque
 * pointer that can only be handed back to routines in the file packet.c
 *
 * @param user_data A data block passed into each instance of this
 * routine.  It contains information from the caller of the foreach
 * routine, specifying information about the dissector table and where
 * to store any information generated by this routine.
 */
extern void
decode_add_to_list (const gchar *table_name, const gchar *proto_name, gpointer value, gpointer user_data);

/*
 * This routine starts the creation of a List on a notebook page.  It
 * creates both a scrolled window and a list, adds the list to the
 * window, and attaches the list as a data object on the page.
 *
 * @param page A pointer to the notebook page being created.
 *
 * @param list_p Will be filled in with the address of a newly
 * created List.
 *
 * @param scrolled_win_p Will be filled in with the address of a newly
 * created GtkScrolledWindow.
 */
extern void
decode_list_menu_start(GtkWidget *page, GtkWidget **list_p,
                       GtkWidget **scrolled_win_p);

/*
 * This routine finishes the creation of a List on a notebook page.
 * It adds the default entry, sets the default entry as the
 * highlighted entry, and sorts the List.
 *
 * @param list A pointer the the List to finish.
 */
extern void
decode_list_menu_finish(GtkWidget *list);

#endif
