void listUsers()
{
    clearmywindow();

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    showHF();

    int listnum = 100;
    GtkWidget** list = malloc(listnum * sizeof(GtkWidget*));

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(adminpannel), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);


    FILE *fp = fopen(".files/userlist", "r");
    if (fp == NULL)
    {
        list[0] = gtk_label_new("PLEASE REGISTER A USER FIRST!");
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(list[0]);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), list[0], (width - 550) / 2, (height - 50) / 2);
    }
    else
    {
        int n = 0;
        listnum = 0;
        char usr[100];
        char pass[100];
        while (fscanf(fp, "%s %s ", usr, pass) == 2)
        {
            list[listnum] = gtk_label_new(usr);
            gtk_fixed_put(GTK_FIXED(fixed), list[listnum], (width - 100) / 2, height - (700 + 2 * n * 10));
            n += 10;
            listnum++;
        }
        fclose(fp);
        free(list);
    }

    gtk_widget_show_all(window);
}