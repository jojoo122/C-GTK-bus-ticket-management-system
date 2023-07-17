void user_unregister(GtkWidget *button, gpointer user_data);
int userunregister();
void removeUser()
{
    clearmywindow();
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_window_fullscreen(GTK_WINDOW(window));
    showHF();

    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, (width - 200), height - 650);

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(adminpannel), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);

    GtkWidget *list = gtk_label_new(NULL);

    FILE *fpp = fopen(".files/userlist", "r"), *fpp2 = fopen(".files/userlist", "r");
    char usr[100];
    char pass[100];
    if (fpp == NULL || fscanf(fpp2, "%s %s ", usr, pass) != 2)
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
        int n = 0, userNumList = 1;
        char listUser[110];
        while (fscanf(fpp, "%s %s ", usr, pass) == 2)
        {
            GtkWidget *wh = gtk_label_new("REGISTERED USERS: ");
            gtk_fixed_put(GTK_FIXED(fixed), wh, (width - 350), (height - 620) / 2);
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
        fclose(fpp2);
        fclose(fpp);
        GtkWidget *unregistrationsuccess = gtk_label_new(NULL);
        gtk_fixed_put(GTK_FIXED(fixed), unregistrationsuccess, (width - 200) / 2, height - 300);

        // entry to take username
        GtkWidget *username_entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
        gtk_widget_set_size_request(username_entry, 200, 50);
        gtk_fixed_put(GTK_FIXED(fixed), username_entry, (width - 200) / 2, (height - 50) / 2 - 50);

        // login button and passing the value of username and password
        GtkWidget *login_button = gtk_button_new_with_label("Remove");
        gtk_widget_set_size_request(login_button, 200, 50);
        gtk_fixed_put(GTK_FIXED(fixed), login_button, (width - 200) / 2, (height - 50) / 2 + 50);
        g_object_set_data(G_OBJECT(login_button), "username_entry", username_entry);
        g_object_set_data(G_OBJECT(login_button), "unregistrationsuccess", unregistrationsuccess);
        g_signal_connect(login_button, "clicked", G_CALLBACK(user_unregister), NULL);

        GtkWidget *request1 = gtk_label_new("PLEASE ENTER THE USERNAME TO REMOVE");
        GtkCssProvider *cssProvider1 = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 20pt; }", -1, NULL);
        GtkStyleContext *styleContext1 = gtk_widget_get_style_context(request1);
        gtk_style_context_add_provider(styleContext1, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), request1, (width - 500) / 2, 200);
    }

    gtk_widget_show_all(window);
}

void user_unregister(GtkWidget *button, gpointer user_data)
{
    GtkWidget *username_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "username_entry"));
    GtkWidget *unregistrationsuccess = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "unregistrationsuccess"));

    // Get the text from the entry widgets
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    strcpy(entered_username, username);
    if (userunregister() == 1)
    {
        gtk_label_set_text(GTK_LABEL(unregistrationsuccess), "SUCCESSFULLY UNREGISTERED!");
        adminpannel();
    }
    else if (userunregister() == 2)
    {
        gtk_label_set_text(GTK_LABEL(unregistrationsuccess), "YOU CAN ONLY REMOVE USERS!");
    }
    else if (userunregister() == 3)
    {
        gtk_label_set_text(GTK_LABEL(unregistrationsuccess), "USER NOT FOUND!");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(unregistrationsuccess), "UNKNOWN ERROR!");
    }
}

int userunregister()
{
    char usrnm[20], pass[20];
    if (osname == 1 || osname == 3)
    {
        FILE *fp3;
        fp3 = fopen(".files/adminlist", "r");
        while (fscanf(fp3, "%s %s", usrnm, pass) == 2)
        {
            if (strcmp(usrnm, entered_username) == 0)
            {
                return 2;
            }
        }
        fclose(fp3);
        FILE *fp, *fp2,*fp5;
        fp = fopen(".files/userlist", "r");
        if (fp == NULL)
        {
            return 0;
        }
        while (fscanf(fp, "%s %s", usrnm, pass) == 2)
        {
            if (strcmp(usrnm, entered_username) == 0)
            {
                break;
            }
        }
        if (strcmp(usrnm, entered_username) != 0)
        {
            return 3;
        }
        fp2 = fopen(".files/temp", "a");
        fp5 = fopen(".files/userlist", "r");
        while (fscanf(fp5, "%s %s", usrnm, pass) == 2)
        {
            if (strcmp(usrnm, entered_username) != 0)
            {
                fprintf(fp2, "%s %s ", usrnm, pass);
            }
        }
        fclose(fp5);
        fclose(fp2);
        fclose(fp);
        remove(".files/userlist");
        rename(".files/temp", ".files/userlist");
    }
    return 1;
}