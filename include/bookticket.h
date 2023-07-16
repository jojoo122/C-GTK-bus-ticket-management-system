void book_ticket_system(GtkWidget *button, gpointer user_data);
void bookTicket()
{
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    if(iden == 1){
    showLEV2("admin");
    }
    else if(iden == 0)
    {
        showLEV2("user");
    }
    showHF();

    GtkWidget *label;
    label = gtk_label_new("BUS LIST:");
    gtk_fixed_put(GTK_FIXED(fixed), label, 1200, 100);

    GtkWidget *label_1;
    label_1 = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), label_1, (width - 210) / 2, (height - 50) / 2 + 100);

    GtkWidget *book_ticket = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(book_ticket), "ENTER BUS NUMBER");
    gtk_widget_set_size_request(book_ticket, 240, 30);
    gtk_entry_set_max_length(GTK_ENTRY(book_ticket), 3);
    g_signal_connect(book_ticket, "insert-text", G_CALLBACK(entry_insert_text), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), book_ticket, (width - 240) / 2, (height - 30) / 2);

    GtkWidget *book_now = gtk_button_new_with_label("Book Now");
    gtk_widget_set_size_request(book_now, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), book_now, (width - 200) / 2, (height - 50) / 2 + 50);
    g_object_set_data(G_OBJECT(book_now), "book_ticket", book_ticket);
    g_object_set_data(G_OBJECT(book_now), "label_1", label_1);
    g_signal_connect(book_now, "clicked", G_CALLBACK(book_ticket_system), NULL);

    int seat_seat, totalBusList = 0, busNumber;
    char busName[200];
    FILE *ticketbo;
    ticketbo = fopen(".files/buslist", "r");
    while (fscanf(ticketbo, "%s %d %d", busName, &seat_seat, &busNumber) == 3)
    {
        totalBusList++;
    }
    fclose(ticketbo);
    gtk_widget_show_all(window);
}

void book_ticket_system(GtkWidget *button, gpointer user_data)
{
    GtkWidget *label_1 = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "label_1"));
    GtkWidget *book_ticket = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "book_ticket"));
    const gchar *ticket_num = gtk_entry_get_text(GTK_ENTRY(book_ticket));
    if (strcmp(ticket_num, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(label_1), "PLEASE ENTER BUS NUMBER");
    }
    else{
        gtk_label_set_text(GTK_LABEL(label_1), NULL);
    }
    int ticketNum = atoi(ticket_num);
}