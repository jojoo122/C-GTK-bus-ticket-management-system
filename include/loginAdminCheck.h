void on_login_clicked_admin(GtkWidget *button, gpointer user_data)
{
    GtkWidget *username_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "username_entry"));
    GtkWidget *password_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "password_entry"));
    GtkWidget *loginfailed = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "loginfailed"));

    // Get the text from the entry widgets
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    strcpy(entered_username, username);
    strcpy(entered_password, password);

    int result = loginCheckAdmin();

    if (result == 1)
    {
        gtk_label_set_text(GTK_LABEL(loginfailed), "SUCCESSFULLY LOGGED IN!");
        adminpannel();
    }
    else if (result == 0)
    {
        gtk_label_set_text(GTK_LABEL(loginfailed), "INCORRECT PASSWORD!");
    }
    else if (result == -1)
    {
        gtk_label_set_text(GTK_LABEL(loginfailed), "USER NOT FOUND!");
    }
    else if (result == 2)
    {
        gtk_label_set_text(GTK_LABEL(loginfailed), "WRONG LOGIN PANNEL!");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(loginfailed), "UNKNOWN ERROR");
    }
}
int loginCheckAdmin()
{
    char usrnm[20], pass[20];
    FILE *chk;
    if(osname == 3 || osname == 1)
    {
        chk = fopen(".files/userlist","r");
        while (fscanf(chk, "%s %s ", usrnm, pass) == 2)
    {
        if (strcmp(entered_username, usrnm) == 0)
        {
            return 2;
        }
    }
    }
    fclose(chk);
    FILE *fp;
    if(osname == 3 || osname == 1)
    {
    fp = fopen(".files/adminlist", "r");
    if (fopen(".files/adminlist", "r") == NULL)
    {
        return 99;
    }
    while (fscanf(fp, "%s %s ", usrnm, pass) == 2)
    {
        if (strcmp(entered_username, usrnm) == 0)
        {
            break;
        }
    }
    fclose(fp);
    }
    if (strcmp(entered_username, usrnm) == 0)
    {
        if (strcmp(entered_password, pass) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }
}