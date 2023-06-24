void firstlanding()
{
    cfp = 1;
    // fixed container and force full screen
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_window_fullscreen(GTK_WINDOW(window));

    GtkWidget *registrationsuccess = gtk_label_new(NULL);

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
    g_object_set_data(G_OBJECT(login_button), "registrationsuccess", registrationsuccess);
    g_signal_connect(login_button, "clicked", G_CALLBACK(admin_register), NULL);

    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 90, 10);

    // header and footer text
    GtkWidget *welcometext = gtk_label_new("WELCOME TO TIGER'S BUS TICKET MANAGEMENT SYSTEM!");
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 30pt; }", -1, NULL);
    GtkStyleContext *styleContext = gtk_widget_get_style_context(welcometext);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GtkWidget *footer = gtk_label_new("DESIGNED AND CODED BY AADARSHA KHANAL, BIGYAN POKHREL & NISHANT SUBEDI");
    gtk_fixed_put(GTK_FIXED(fixed), welcometext, 82, 1);
    gtk_fixed_put(GTK_FIXED(fixed), footer, (width - 550) / 2, height - 45);

    GtkWidget *request1 = gtk_label_new("LOOKS LIKE THIS IS THE FIRST TIME YOU ARE USING THIS APP \n     PLEASE SETUP AN ADMIN ACCOUNT FOR FURTHER USE");
    GtkCssProvider *cssProvider1 = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 20pt; }", -1, NULL);
    GtkStyleContext *styleContext1 = gtk_widget_get_style_context(request1);
    gtk_style_context_add_provider(styleContext1, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_widget_set_halign(request1, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(request1, GTK_ALIGN_CENTER);
    gtk_fixed_put(GTK_FIXED(fixed), request1, (width - 775) / 2, 200);

    gtk_fixed_put(GTK_FIXED(fixed), registrationsuccess, (width - 200) / 2, height - 300);

    // shows all the components inside the window
    gtk_widget_show_all(window);
}