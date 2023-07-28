void resetApp();
void adminpannel()
{
    iden = 1;
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    showLE();

    // header and footer text
    showHF();

    GtkWidget *registerbus = gtk_button_new_with_label("REGISTER A NEW BUS");
    gtk_widget_set_size_request(registerbus, 400, 50);
    g_signal_connect(registerbus, "clicked", G_CALLBACK(registerBus), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),registerbus,(width-400)/2-250,(height/2)-300);

    GtkWidget *deregisterbus = gtk_button_new_with_label("REMOVE A BUS");
    gtk_widget_set_size_request(deregisterbus, 400, 50);
    g_signal_connect(deregisterbus, "clicked", G_CALLBACK(removeBus), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),deregisterbus,(width-400)/2-250,(height/2)-200);
    
    GtkWidget *bookticket = gtk_button_new_with_label("BOOK A TICKET");
    gtk_widget_set_size_request(bookticket, 400, 50);
    g_signal_connect(bookticket, "clicked", G_CALLBACK(bookTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),bookticket,(width-400)/2-250,(height/2)-100);

    GtkWidget *cancelticket = gtk_button_new_with_label("CANCEL A TICKET");
    gtk_widget_set_size_request(cancelticket, 400, 50);
    g_signal_connect(cancelticket, "clicked", G_CALLBACK(cancelTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),cancelticket,(width-400)/2-250,(height/2));

    GtkWidget *adduser = gtk_button_new_with_label("ADD A NEW USER");
    gtk_widget_set_size_request(adduser, 400, 50);
    g_signal_connect(adduser, "clicked", G_CALLBACK(registerUser), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),adduser,(width-400)/2-250,(height/2)+100);

    GtkWidget *removeuser = gtk_button_new_with_label("REMOVE A USER");
    gtk_widget_set_size_request(removeuser, 400, 50);
    g_signal_connect(removeuser, "clicked", G_CALLBACK(removeUser), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),removeuser,(width-400)/2-250,(height/2)+200);

    GtkWidget *listusers = gtk_button_new_with_label("LIST ALL THE USERS");
    gtk_widget_set_size_request(listusers, 400, 50);
    g_signal_connect(listusers, "clicked", G_CALLBACK(listUsers), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),listusers,(width-400)/2+250,(height/2) - 300);

    GtkWidget *bookedticketdetails = gtk_button_new_with_label("LIST BOOKED TICKET DETAILS");
    gtk_widget_set_size_request(bookedticketdetails, 400, 50);
    g_signal_connect(bookedticketdetails, "clicked", G_CALLBACK(listDetail), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),bookedticketdetails,(width-400)/2+250,(height/2) - 200);

    GtkWidget *bookedticketdetails = gtk_button_new_with_label("SET TICKET RESET TIME");
    gtk_widget_set_size_request(bookedticketdetails, 400, 50);
    g_signal_connect(bookedticketdetails, "clicked", G_CALLBACK(reset_bus_list), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),bookedticketdetails,(width-400)/2+250,(height/2) - 200);

    GtkWidget *resetapp = gtk_button_new_with_label("RESET APP");
    gtk_widget_set_size_request(resetapp, 40, 40);
    g_signal_connect(resetapp, "clicked", G_CALLBACK(resetApp), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), resetapp, 1255, height - 47);
    
    
    gtk_widget_show_all(window);
}

void resetApp()
{
    if(osname == 1)
    {
        system("rmdir .files");
    }
    else if(osname == 3)
    {
        system("rm -r .files");
    }
    firstlanding();
}