int userLogin()
{
    clearmywindow();
    // fixed container and force full screen
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    GtkWidget *loginfailed = gtk_label_new(NULL);

    // entry to take username
    GtkWidget *username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_widget_set_size_request(username_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), username_entry, (width - 200) / 2, (height - 50) / 2 - 50);

    // entry to take password
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_widget_set_size_request(password_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), password_entry, (width - 200) / 2, (height - 50) / 2);

    // login button and passing the value of username and password
    GtkWidget *login_button = gtk_button_new_with_label("Login");
    gtk_widget_set_size_request(login_button, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), login_button, (width - 200) / 2, (height - 50) / 2 + 50);
    g_object_set_data(G_OBJECT(login_button), "username_entry", username_entry);
    g_object_set_data(G_OBJECT(login_button), "password_entry", password_entry);
    g_object_set_data(G_OBJECT(login_button), "loginfailed", loginfailed);
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked_user), NULL);
    
    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback,"clicked",G_CALLBACK(landing),NULL);
    gtk_fixed_put(GTK_FIXED(fixed),goback,5,5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit,"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_fixed_put(GTK_FIXED(fixed),exit,width-70,5);
    
    gtk_fixed_put(GTK_FIXED(fixed), loginfailed, (width - 200) / 2, height - 300);

    // header and footer text
    showHF();

    // shows all the components inside the window
    gtk_widget_show_all(window);

    return 0;
}