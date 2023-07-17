int userregister();
void user_register(GtkWidget *button, gpointer user_data);
void registerUser(){
    clearmywindow();
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_window_fullscreen(GTK_WINDOW(window));

    GtkWidget *registrationsuccess = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), registrationsuccess, (width - 200) / 2, height - 300);

    GtkWidget *username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_widget_set_size_request(username_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), username_entry, (width - 200) / 2, (height - 50) / 2 - 50);

    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_widget_set_size_request(password_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), password_entry, (width - 200) / 2, (height - 50) / 2);

    GtkWidget *login_button = gtk_button_new_with_label("Register User");
    gtk_widget_set_size_request(login_button, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), login_button, (width - 200) / 2, (height - 50) / 2 + 50);
    g_object_set_data(G_OBJECT(login_button), "username_entry", username_entry);
    g_object_set_data(G_OBJECT(login_button), "password_entry", password_entry);
    g_object_set_data(G_OBJECT(login_button), "registrationsuccess", registrationsuccess);
    g_signal_connect(login_button, "clicked", G_CALLBACK(user_register), NULL);

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(adminpannel), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);

    showHF();

    GtkWidget *request1 = gtk_label_new("PLEASE ENTER THE NEW USER INFO");
    GtkCssProvider *cssProvider1 = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 20pt; }", -1, NULL);
    GtkStyleContext *styleContext1 = gtk_widget_get_style_context(request1);
    gtk_style_context_add_provider(styleContext1, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_fixed_put(GTK_FIXED(fixed), request1, (width - 400) / 2, 200);

    gtk_widget_show_all(window);
}

void user_register(GtkWidget *button, gpointer user_data)
{
    GtkWidget *username_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "username_entry"));
    GtkWidget *password_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "password_entry"));
    GtkWidget *registrationsuccess = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "registrationsuccess"));

    // Get the text from the entry widgets
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    strcpy(entered_username, username);
    strcpy(entered_password, password);
    if (strcmp(entered_password, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(registrationsuccess), "PLEASE ENTER PASSWORD!");
    }
    else
    {
        if (userregister() == 1)
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "SUCCESSFULLY REGISTERED!");
            adminpannel();
        }
        else if (userregister() == -1)
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "USER ALREADY EXISTS!");
        }
        else if (userregister() == 9)
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "USERNAME MUST BE > 2");
        }
        else if (userregister() == 10)
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "PASSWORD MUST BE > 7");
        }
        else
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "UNKNWON ERROR!");
        }
    }
}
int userregister()
{
    if(strlen(entered_username) < 3)
    {
        return 9;
    }
    if(strlen(entered_password) < 8)
    {
        return 10;
    }
    if (osname == 1 || osname == 3)
    {
        char usrnm[20], pass[20];
        FILE *fp2, *fp3, *fp;
        fp2 = fopen(".files/userlist", "r");
        fp3 = fopen(".files/adminlist", "r");
        if (fp2 == NULL)
        {
            goto label;
        }
        while (fscanf(fp2, "%s %s", usrnm, pass) == 2)
        {
            if (strcmp(usrnm, entered_username) == 0)
            {
                return -1;
            }
        }
        while (fscanf(fp3, "%s %s", usrnm, pass) == 2)
        {
            if (strcmp(usrnm, entered_username) == 0)
            {
                return -1;
            }
        }
        fclose(fp2);
    label:
        fp = fopen(".files/userlist", "a");
        while (fscanf(fp3, "%s %s", usrnm, pass) == 2)
        {
            if (strcmp(usrnm, entered_username) == 0)
            {
                return -1;
            }
        }
        if (fopen(".files/userlist", "r") == NULL)
        {
            return 0;
        }
        fprintf(fp, "%s %s ", entered_username, entered_password);
        fclose(fp);
        fclose(fp3);
    }
    return 1;
}
