void admin_register(GtkWidget *button, gpointer user_data)
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
        if (registeradmin() == 1)
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "SUCCESSFULLY REGISTERED!");
            landing();
        }
        else if (registeradmin() == 10)
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "PASSOWRD MUST BE > 7");
        }
        else if (registeradmin() == 9)
        {
            
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "USERNAME MUST BE > 2");
        }
        else
        {
            gtk_label_set_text(GTK_LABEL(registrationsuccess), "UNKNOWN ERROR!");
        }
    }
}

struct stat st = {0};

int registeradmin()
{
    if (strlen(entered_username) < 3)
    {
        return 9;
    }
    if (strlen(entered_password) < 8)
    {
        return 10;
    }
    if (osname == 1)
    {
        if (stat(".files", &st) == -1)
        {
            system("mkdir .files");
            system("attrib +h .files");
        }
        FILE *fp;
        fp = fopen(".files/adminlist", "a");
        if (fopen(".files/adminlist", "r") == NULL)
        {
            return 0;
        }
        fprintf(fp, "%s %s ", entered_username, entered_password);
        fclose(fp);
    }
    if (osname == 3)
    {
        if (stat(".files", &st) == -1)
        {
            system("mkdir .files");
        }
        FILE *fp;
        fp = fopen(".files/adminlist", "a");
        if (fopen(".files/adminlist", "r") == NULL)
        {
            return 0;
        }
        fprintf(fp, "%s %s ", entered_username, entered_password);
        fclose(fp);
    }
    return 1;
}
