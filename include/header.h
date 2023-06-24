#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int cfp = 0;

int loginCheckAdmin();

void clicked();

void firstlanding();

int registeradmin();

void landing();

int loginCheckUser();

int width = 1366;
int height = 768;

char entered_username[20], entered_password[20];

GtkWidget *window;
GtkWidget *fixed;

void clearmywindow()
{
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    GList *node = children;
    while (node != NULL)
    {
        gtk_container_remove(GTK_CONTAINER(window), GTK_WIDGET(node->data));
        node = g_list_next(node);
    }
    g_list_free(children);
}

int osname = 0;

void oslist()
{
#ifdef _WIN32
    osname = 1;
#elif __APPLE__
    osname = 2;
#elif __linux__
    osname = 3;
#elif TARGET_OS_MAC
    osname = 4;
#else
    osname = 5;
#endif
}
