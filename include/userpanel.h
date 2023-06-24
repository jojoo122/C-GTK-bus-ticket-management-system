void userpannel()
{
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback,"clicked",G_CALLBACK(landing),NULL);
    gtk_fixed_put(GTK_FIXED(fixed),goback,5,5);

    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit,"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_fixed_put(GTK_FIXED(fixed),exit,width-70,5);

    // header and footer text
    GtkWidget *welcometext = gtk_label_new("WELCOME TO TIGER'S BUS TICKET MANAGEMENT SYSTEM!");
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
    GtkStyleContext *styleContext = gtk_widget_get_style_context(welcometext);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GtkWidget *footer = gtk_label_new("DESIGNED AND CODED BY AADARSHA KHANAL, BIGYAN POKHREL & NISHANT SUBEDI");
    gtk_fixed_put(GTK_FIXED(fixed), welcometext, 155, 1);
    gtk_fixed_put(GTK_FIXED(fixed), footer, (width - 550) / 2, height - 45);

    GtkWidget *bookticket = gtk_button_new_with_label("BOOK A TICKET");
    gtk_widget_set_size_request(bookticket, 400, 50);
    // g_signal_connect(bookticket, "clicked", G_CALLBACK(bookTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),bookticket,(width-400)/2,(height/2)-50);

    GtkWidget *cancelticket = gtk_button_new_with_label("CANCEL A TICKET");
    gtk_widget_set_size_request(cancelticket, 400, 50);
    // g_signal_connect(cancelticket, "clicked", G_CALLBACK(cancelTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),cancelticket,(width-400)/2,(height/2)+50);

    gtk_widget_show_all(window);
}