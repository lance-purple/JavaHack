/* Copyright (c) Lance Purple, 2015				  */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef WINJAVA_H
#define WINJAVA_H

#define E extern

E void win_java_init(void);

E struct window_procs java_procs;

E void java_init_nhwindows(int* argcp, char** argv);
E void java_player_selection(void);
E void java_askname(void);
E void java_get_nh_event(void);
E void java_exit_nhwindows(const char* str);
E void java_suspend_nhwindows(const char* str);
E void java_resume_nhwindows(void);
E winid java_create_nhwindow(int type);
E void java_clear_nhwindow(winid window);
E void java_display_nhwindow(winid window, int blocking);
E void java_destroy_nhwindow(winid window);
E void java_curs(winid window, int x, int y);
E void java_putstr(winid window, int attr, const char* str);
E void java_display_file(const char* filename, int complain);
E void java_start_menu(winid window);
E void java_add_menu(winid window, int glyph, const anything* identifier,
                     int ch, int gch, int attr, const char* str,
                     int preselected);
E void java_end_menu(winid window, const char* prompt);
E int java_select_menu(winid window, int how, menu_item** menu_list);
E char java_message_menu(int let, int how, const char* message);
E void java_update_inventory(void);
E void java_mark_synch(void);
E void java_wait_synch(void);
E void java_cliparound(int x, int y);
E void java_print_glyph(winid window, int x, int y, int glyph);
E void java_raw_print(const char* str);
E void java_raw_print_bold(const char* str);
E int java_nhgetch(void);
E int java_nh_poskey(int *x, int *y, int* mod);
E void java_nhbell(void);
E int java_doprev_message(void);
E char java_yn_function(const char* query, const char* resp, int def);
E void java_getlin(const char* query, char* buffer);
E int java_get_ext_cmd(void);
E void java_number_pad(int state);
E void java_delay_output(void);

/* other defs that really should go away (they're tty specific) */
E void java_start_screen(void);
E void java_end_screen(void);
E void java_outrip(winid tmpwin, int how);
E void java_preference_update(const char* pref);

#endif /* WINJAVA_H */
