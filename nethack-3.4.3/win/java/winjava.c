/* Copyright (c) Lance Purple, 2015				  */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

#include <jni.h>
#include <limits.h>

#ifdef JAVA_GRAPHICS

#include "winjava.h"
#include "wintty.h"

void win_java_init(void) {
    win_tty_init();
}

JNIEnv* jni_env;
JavaVM* java_vm;

/* Interface definition, for windows.c */

struct window_procs java_procs = {
    "java",

    WC_COLOR|WC_HILITE_PET|WC_INVERSE|WC_EIGHT_BIT_IN,
    0L,
    java_init_nhwindows,
    java_player_selection,
    java_askname,
    java_get_nh_event,
    java_exit_nhwindows,
    java_suspend_nhwindows,
    java_resume_nhwindows,
    java_create_nhwindow,
    java_clear_nhwindow,
    java_display_nhwindow,
    java_destroy_nhwindow,
    java_curs,
    java_putstr,
    java_display_file,
    java_start_menu,
    java_add_menu,
    java_end_menu,
    java_select_menu,
    java_message_menu,
    java_update_inventory,
    java_mark_synch,
    java_wait_synch,
    java_cliparound,
    java_print_glyph,
    java_raw_print,
    java_raw_print_bold,
    java_nhgetch,
    java_nh_poskey,
    java_nhbell,
    java_doprev_message,
    java_yn_function,
    java_getlin,
    java_get_ext_cmd,
    java_number_pad,
    java_delay_output,

    /* other defs that really should go away (they're tty specific) */
    java_start_screen,
    java_end_screen,
    java_outrip,
    java_preference_update,
};

void java_init_nhwindows(int* argcp, char** argv) {
    tty_init_nhwindows(argcp, argv);

    const char* java_home = getenv("JAVA_HOME");
    if (NULL != java_home) {

        char java_library_path[PATH_MAX];
        sprintf(java_library_path, "-Djava.library.path=%s/lib/", java_home);

        char java_class_path[PATH_MAX];
        sprintf(java_class_path, "-Djava.class.path=%s", getenv("CLASSPATH"));

        JavaVMOption options[3];
        options[0].optionString = java_library_path;
        options[1].optionString = java_class_path;
        options[2].optionString = "-verbose:jni";

        JavaVMInitArgs vm_args;
        vm_args.version = JNI_VERSION_1_8;
        vm_args.nOptions = 2;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = 0;

        int jc = JNI_CreateJavaVM(&java_vm, (void**)&jni_env, &vm_args);
        if (JNI_OK != jc) {
            printf("\nFailed to Launch JVM\n");
            exit(jc);
        }

        jclass class = (*jni_env)->FindClass(jni_env, "rec/games/roguelike/nh4j/ui/GUI");
        if ((*jni_env)->ExceptionCheck(jni_env)) {
            (*jni_env)->ExceptionDescribe(jni_env);
        }

        jmethodID methodID = (*jni_env)->GetStaticMethodID(jni_env, class, "start", "()V");
        if ((*jni_env)->ExceptionCheck(jni_env)) {
            (*jni_env)->ExceptionDescribe(jni_env);
        }

        (*jni_env)->CallStaticVoidMethod(jni_env, class, methodID);
        if ((*jni_env)->ExceptionCheck(jni_env)) {
            (*jni_env)->ExceptionDescribe(jni_env);
        }

    }
    else {
        fprintf(stderr, "\nJAVA_HOME must be specified\n");
        exit(1);
    }
}

void java_player_selection(void) {
    tty_player_selection();
}

void java_askname(void) {
    tty_askname();
}

void java_get_nh_event(void) {
    tty_get_nh_event();
}

void java_exit_nhwindows(const char* str) {
    tty_exit_nhwindows(str);

    if (NULL != java_vm) {
        int jc = (*java_vm)->DestroyJavaVM(java_vm);
        if (0 != jc) {
            fprintf(stderr, "\nFailed to destroy JVM: %d\n", jc);
        }
    }
}

void java_suspend_nhwindows(const char* str) {
    tty_suspend_nhwindows(str);
}

void java_resume_nhwindows(void) {
    tty_resume_nhwindows();
}

winid java_create_nhwindow(int type) {
    return tty_create_nhwindow(type);
}

void java_clear_nhwindow(winid window) {
    tty_clear_nhwindow(window);
}

void java_display_nhwindow(winid window, int blocking) {
    tty_display_nhwindow(window, blocking);
}

void java_destroy_nhwindow(winid window) {
    tty_destroy_nhwindow(window);
}

void java_curs(winid window, int x, int y) {
    tty_curs(window, x, y);
}

void java_putstr(winid window, int attr, const char* str) {
    tty_putstr(window, attr, str);
}

void java_display_file(const char* filename, int complain) {
    tty_display_file(filename, complain);
}

void java_start_menu(winid window) {
    tty_start_menu(window);
}

void java_add_menu(winid window, int glyph, const anything* identifier,
                   int ch, int gch, int attr, const char* str,
                   int preselected) {
    tty_add_menu(window, glyph, identifier, ch, gch, attr, str, preselected);
}

void java_end_menu(winid window, const char* prompt) {
    tty_end_menu(window, prompt);
}

int java_select_menu(winid window, int how, menu_item** menu_list) {
    return tty_select_menu(window, how, menu_list);
}

char java_message_menu(int let, int how, const char* message) {
    return tty_message_menu(let, how, message);
}

void java_update_inventory(void) {
    tty_update_inventory();
}

void java_mark_synch(void) {
    tty_mark_synch();
}

void java_wait_synch(void) {
    tty_wait_synch();
}

void java_cliparound(int x, int y) {
    tty_cliparound(x, y);
}

void java_print_glyph(winid window, int x, int y, int glyph) {
    tty_print_glyph(window, x, y, glyph);
}

void java_raw_print(const char* str) {
    tty_raw_print(str);
}

void java_raw_print_bold(const char* str) {
    tty_raw_print_bold(str);
}

int java_nhgetch(void) {
    return tty_nhgetch();
};

int java_nh_poskey(int *x, int *y, int* mod) {
    return tty_nh_poskey(x, y, mod);
}

void java_nhbell(void) {
    tty_nhbell();
}

int java_doprev_message(void) {
    return tty_doprev_message();
}

char java_yn_function(const char* query, const char* resp, int def) {
    return tty_yn_function(query, resp, def);
}

void java_getlin(const char* query, char* buffer) {
    tty_getlin(query, buffer);
}

int java_get_ext_cmd(void) {
    return tty_get_ext_cmd();
}

void java_number_pad(int state) {
    tty_number_pad(state);
}

void java_delay_output(void) {
    tty_delay_output();
}

/* other defs that really should go away (they're tty specific) */

void java_start_screen(void) {
    tty_start_screen();
}

void java_end_screen(void) {
    tty_end_screen();
}

void java_outrip(winid tmpwin, int how) {
    genl_outrip(tmpwin, how);
}

void java_preference_update(const char* pref) {
    genl_preference_update(pref);
}

#endif /* JAVA_GRAPHICS */

/*winjava.c*/
