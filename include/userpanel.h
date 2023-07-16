void userpannel()
{
    iden = 0;
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    GtkWidget *goback = gtk_button_new_with_label("LOG OUT");
    g_signal_connect(goback,"clicked",G_CALLBACK(landing),NULL);
    gtk_fixed_put(GTK_FIXED(fixed),goback,5,5);

    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit,"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_fixed_put(GTK_FIXED(fixed),exit,width-70,5);

    // header and footer text
    showHF();

    GtkWidget *bookticket = gtk_button_new_with_label("BOOK A TICKET");
    gtk_widget_set_size_request(bookticket, 400, 50);
    g_signal_connect(bookticket, "clicked", G_CALLBACK(bookTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),bookticket,(width-400)/2,(height/2)-50);

    GtkWidget *cancelticket = gtk_button_new_with_label("CANCEL A TICKET");
    gtk_widget_set_size_request(cancelticket, 400, 50);
    // g_signal_connect(cancelticket, "clicked", G_CALLBACK(cancelTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),cancelticket,(width-400)/2,(height/2)+50);

    gtk_widget_show_all(window);
}