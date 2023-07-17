void listUsers()
{
    clearmywindow();

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    showHF();

    int listnum = 100;
    GtkWidget *list = gtk_label_new(NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, (width - 150) / 2, (height - 500) / 2);

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(adminpannel), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);

    FILE *fp = fopen(".files/userlist", "r"), *fp2 = fopen(".files/userlist", "r");
    char usr[100];
    char pass[100];
    if (fp == NULL || fscanf(fp2, "%s %s ", usr, pass) != 2)
    {
        list = gtk_label_new("PLEASE REGISTER A USER FIRST!");
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(list);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), list, (width - 550) / 2, (height - 50) / 2);
    }
    else
    {
        memset(usr, 0, sizeof(usr));
        memset(pass, 0, sizeof(pass));
        int n = 0;
        int userNumList = 1;
        char listUser[200];
        while (fscanf(fp, "%s %s ", usr, pass) == 2)
        {
            GtkWidget *wh = gtk_label_new("REGISTERED USERS: ");
            gtk_fixed_put(GTK_FIXED(fixed), wh, (width - 350) / 2, (height - 620) / 2);
            sprintf(listUser,"%d. %s",userNumList, usr);
            list = gtk_label_new(listUser);
            GtkCssProvider *cssProvider = gtk_css_provider_new();
            gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
            GtkStyleContext *styleContext = gtk_widget_get_style_context(list);
            GtkCssProvider *cssProvider1 = gtk_css_provider_new();
            gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 18pt; }", -1, NULL);
            gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            GtkStyleContext *styleContext1 = gtk_widget_get_style_context(wh);
            gtk_style_context_add_provider(styleContext1, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            gtk_grid_attach(GTK_GRID(grid), list, 1, 0 + n, 1, 1);
            n += 10;
            userNumList++;
        }
        fclose(fp2);
        fclose(fp);
    }

    gtk_widget_show_all(window);
}