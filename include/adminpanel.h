void adminpannel()
{
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
    GtkWidget *welcometext = gtk_label_new("WELCOME TO TIGER'S BUS TICKET MANAGEMENT SYSTEM!");
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
    GtkStyleContext *styleContext = gtk_widget_get_style_context(welcometext);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GtkWidget *footer = gtk_label_new("DESIGNED AND CODED BY AADARSHA KHANAL, BIGYAN POKHREL & NISHANT SUBEDI");
    gtk_fixed_put(GTK_FIXED(fixed), welcometext, 155, 1);
    gtk_fixed_put(GTK_FIXED(fixed), footer, (width - 550) / 2, height - 45);

    GtkWidget *registerbus = gtk_button_new_with_label("REGISTER A NEW BUS");
    gtk_widget_set_size_request(registerbus, 400, 50);
    //g_signal_connect(registerbus, "clicked", G_CALLBACK(registerBus), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),registerbus,(width-400)/2-250,(height/2)-300);

    GtkWidget *deregisterbus = gtk_button_new_with_label("REMOVE A BUS");
    gtk_widget_set_size_request(deregisterbus, 400, 50);
    // g_signal_connect(deregisterbus, "clicked", G_CALLBACK(deRegisterBus), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),deregisterbus,(width-400)/2-250,(height/2)-200);
    
    GtkWidget *bookticket = gtk_button_new_with_label("BOOK A TICKET");
    gtk_widget_set_size_request(bookticket, 400, 50);
    // g_signal_connect(bookticket, "clicked", G_CALLBACK(bookTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),bookticket,(width-400)/2-250,(height/2)-100);

    GtkWidget *cancelticket = gtk_button_new_with_label("CANCEL A TICKET");
    gtk_widget_set_size_request(cancelticket, 400, 50);
    // g_signal_connect(cancelticket, "clicked", G_CALLBACK(cancelTicket), NULL);
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
    // g_signal_connect(listusers, "clicked", G_CALLBACK(listUsers), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),listusers,(width-400)/2+250,(height/2)-100);

    GtkWidget *bookedticketdetails = gtk_button_new_with_label("LIST BOOKED TICKET DETAILS");
    gtk_widget_set_size_request(bookedticketdetails, 400, 50);
    // g_signal_connect(bookedticketdetails, "clicked", G_CALLBACK(BookedTicketDetails), NULL);
    gtk_fixed_put(GTK_FIXED(fixed),bookedticketdetails,(width-400)/2+250,(height/2));
    
    gtk_widget_show_all(window);
}