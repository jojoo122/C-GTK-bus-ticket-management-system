void landing()
{
    if(cfp==1){
    clearmywindow();}
    //declaring widgets
    GtkWidget *button;
    GtkWidget *button1;

    //create the window & close the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //create a fixed coordinate component
    fixed = gtk_fixed_new();

    //the header and text
    GtkWidget *welcometext = gtk_label_new("WELCOME TO TIGER'S BUS TICKET MANAGEMENT SYSTEM!");
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 30pt; }", -1, NULL);
    GtkStyleContext *styleContext = gtk_widget_get_style_context(welcometext);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GtkWidget *footer = gtk_label_new("DESIGNED AND CODED BY AADARSHA KHANAL, BIGYAN POKHREL & NISHANT SUBEDI");

    //buttons
    button = gtk_button_new_with_label("LOGIN AS ADMIN");
    gtk_widget_set_size_request(button, 200, 50);
    g_signal_connect(button, "clicked", G_CALLBACK(adminLogin), NULL);
    button1 = gtk_button_new_with_label("LOGIN AS USER");
    g_signal_connect(button1, "clicked", G_CALLBACK(userLogin), NULL);
    gtk_widget_set_size_request(button1, 200, 50);

    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit,"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_fixed_put(GTK_FIXED(fixed),exit,width-90,10);

    //fixing the buttons and texts position
    gtk_fixed_put(GTK_FIXED(fixed), button, (width - 200) / 2, (height - 50) / 2);
    gtk_fixed_put(GTK_FIXED(fixed), button1, (width - 200) / 2, (height - 50) / 2 + 100);
    gtk_fixed_put(GTK_FIXED(fixed), welcometext, 82, 1);
    gtk_fixed_put(GTK_FIXED(fixed), footer, (width - 550) / 2, height - 45);

    //adding component to the window
    gtk_container_add(GTK_CONTAINER(window), fixed);

    //force full screen
    gtk_window_fullscreen(GTK_WINDOW(window));

    //set window title
    gtk_window_set_title(GTK_WINDOW(window), "TIGER'S BUS MANAGEMENT SYSTEM");


    //shows all the components inside the window
    gtk_widget_show_all(window);
    // gtk_main();
}