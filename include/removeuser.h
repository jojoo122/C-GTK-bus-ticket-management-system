void user_unregister(GtkWidget *button, gpointer user_data);
int userunregister();
void removeUser()
{
    clearmywindow();
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_window_fullscreen(GTK_WINDOW(window));

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

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(adminpannel), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);

    // header and footer text
    GtkWidget *welcometext = gtk_label_new("WELCOME TO TIGER'S BUS TICKET MANAGEMENT SYSTEM!");
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
    GtkStyleContext *styleContext = gtk_widget_get_style_context(welcometext);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GtkWidget *footer = gtk_label_new("DESIGNED AND CODED BY AADARSHA KHANAL, BIGYAN POKHREL & NISHANT SUBEDI");
    gtk_fixed_put(GTK_FIXED(fixed), welcometext, 155, 1);
    gtk_fixed_put(GTK_FIXED(fixed), footer, (width - 550) / 2, height - 45);

    GtkWidget *request1 = gtk_label_new("PLEASE ENTER THE USERNAME TO REMOVE");
    GtkCssProvider *cssProvider1 = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 20pt; }", -1, NULL);
    GtkStyleContext *styleContext1 = gtk_widget_get_style_context(request1);
    gtk_style_context_add_provider(styleContext1, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_widget_set_halign(request1, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(request1, GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(fixed), request1, (width - 500) / 2, 200);

    gtk_widget_show_all(window);
}

void user_unregister(GtkWidget *button, gpointer user_data)
{
    GtkWidget *username_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "username_entry"));
    GtkWidget *unregistrationsuccess = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "unregistrationsuccess"));

    // Get the text from the entry widgets
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    strcpy(entered_username, username);
    if (userunregister()==1)
    {
        gtk_label_set_text(GTK_LABEL(unregistrationsuccess), "SUCCESSFULLY UNREGISTERED!");
        adminpannel();
    }
    else if(userunregister() == 2)
    {
        gtk_label_set_text(GTK_LABEL(unregistrationsuccess), "YOU CAN ONLY REMOVE USERS!");
    }
    else if(userunregister() == 3)
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
        fp3 = fopen(".files/adminlist","r");
        while(fscanf(fp3, "%s %s",usrnm,pass) == 2)
        {
            if(strcmp(usrnm,entered_username) == 0)
            {
                return 2;
            }
        }
        fclose(fp3);
        FILE *fp, *fp2;
        fp = fopen(".files/userlist", "r");
        if (fopen(".files/userlist", "r") == NULL)
        {
            return 0;
        }
        while(fscanf(fp,"%s %s",usrnm,pass) == 2)
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
        while (fscanf(fp, "%s %s", usrnm, pass) == 2)
        {
            if (strcmp(usrnm, entered_username) != 0)
            {
                fprintf(fp2, "%s %s ", usrnm, pass);
            }
        }
        fclose(fp2);
        fclose(fp);
        remove(".files/userlist");
        rename(".files/temp",".files/userlist");
    }
    return 1;
}