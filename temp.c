#include <gtk/gtk.h>
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_fullscreen(GTK_WINDOW(window));

    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Create a grid widget
    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, 1220, 300);

    GtkWidget *label;

    label = gtk_label_new("  BUS TICKETS THAT\nARE BOOKED ARE RED");
    gtk_fixed_put(GTK_FIXED(fixed), label, 1200, 260);

    int totalseat = 41;
    int tems = totalseat;
    int row = 4;
    int col;
    int q = 0;
    if (totalseat % 4 != 0)
    {
        while (1)
        {
            if ((totalseat - q) % 4 == 0)
            {
                col = (totalseat - q) / row;
                break;
            }
            q++;
        }
    }
    else
    {
        q = 1;
    }
    int k = 1, te;
    int y;
    int v = 0;
    if (totalseat % 4 != 0)
    {
        for (int i = q - 1; i > 0; i--)
        {
            char button_label[10];
            sprintf(button_label, "0%d ", k);
            label = gtk_label_new(button_label);
            gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
            k++;
            v++;
        }

        for (int i = col; i > 0; i--)
        {
            y = 1;
            te = 0;
            for (int j = row; j > 0; j--)
            {
                if (te == 2)
                {
                    y = j + 2;
                }
                if (k < 10)
                {
                    char button_label[10];
                    sprintf(button_label, "0%d ", k);
                    label = gtk_label_new(button_label);
                    gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                    k++;
                }
                else
                {
                    char button_label[10];
                    sprintf(button_label, "%d ", k);

                    label = gtk_label_new(button_label);
                    gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                    k++;
                }
                if (k == totalseat - 4)
                {
                    break;
                }
                te++;
                y++;
            }
            if (k == totalseat - 4)
            {
                break;
            }
        }
        int p = 1;
        while (1)
        {
            if (k != totalseat - 1)
            {
                char button_label[10];
                sprintf(button_label, "%d ", k);
                label = gtk_label_new(button_label);
                gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
            }
            if (k == totalseat)
            {
                break;
            }
            if (k == totalseat - 1)
            {
                char button_label[10];
                sprintf(button_label, "%d ", k);
                label = gtk_label_new(button_label);
                gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                GtkStyleContext *context = gtk_widget_get_style_context(label);
                gtk_style_context_add_class(context, "red-label");
            }
            k++;
            p++;
        }
    }
    else
    {
        totalseat = totalseat - 1;
        while (1)
        {
            if ((totalseat - q) % 4 == 0)
            {
                col = (totalseat - q) / row;
                break;
            }
            q++;
        }
        q++;
        if (q % 2 != 0)
        {
            for (int i = q - 1; i > 0; i--)
            {
                char button_label[10];
                sprintf(button_label, "0%d ", k);
                label = gtk_label_new(button_label);
                gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                k++;
                v++;
            }
        }
        if (q % 2 == 0)
        {
            for (int i = q - 1; i > 0; i--)
            {
                if (i == 1)
                {
                    char button_label[10];
                    sprintf(button_label, "0%d ", k);
                    label = gtk_label_new(button_label);
                    gtk_grid_attach(GTK_GRID(grid), label, 5 - 3, 0, 1, 1);
                    k++;
                }
                else
                {
                    char button_label[10];
                    sprintf(button_label, "0%d ", k);
                    label = gtk_label_new(button_label);
                    gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                    k++;
                    v++;
                }
            }
        }

        for (int i = col; i > 0; i--)
        {
            y = 1;
            te = 0;
            for (int j = row; j > 0; j--)
            {
                if (te == 2)
                {
                    y = j + 2;
                }
                if (k < 10)
                {
                    char button_label[10];
                    sprintf(button_label, "0%d ", k);
                    label = gtk_label_new(button_label);
                    gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                    k++;
                }
                else
                {
                    char button_label[10];
                    sprintf(button_label, "%d ", k);

                    label = gtk_label_new(button_label);
                    gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                    k++;
                }
                if (k == totalseat + 1 - 4)
                {
                    break;
                }
                te++;
                y++;
            }
            if (k == totalseat + 1 - 4)
            {
                break;
            }
        }
        int p = 1;
        while (1)
        {
            totalseat = tems;
            if (k != totalseat - 1)
            {
                char button_label[10];
                sprintf(button_label, "%d ", k);
                label = gtk_label_new(button_label);
                gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
            }
            if (k == totalseat)
            {
                break;
            }
            if (k == totalseat - 1)
            {
                char button_label[10];
                sprintf(button_label, "%d ", k);
                label = gtk_label_new(button_label);
                gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                GtkStyleContext *context = gtk_widget_get_style_context(label);
                gtk_style_context_add_class(context, "red-label");
            }
            k++;
            p++;
        }
    }

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    GError *error = NULL;
    gtk_css_provider_load_from_data(cssProvider, ".red-label { color: red; }", -1, &error);
    if (error != NULL)
    {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}