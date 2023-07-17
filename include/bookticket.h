void book_ticket_system(GtkWidget *button, gpointer user_data);
void bookTicket()
{
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    if (iden == 1)
    {
        showLEV2("admin");
    }
    else if (iden == 0)
    {
        showLEV2("user");
    }
    showHF();

    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, 1010, 140);

    GtkWidget *list = gtk_label_new(NULL);

    GtkWidget *list1 = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), list1, (width - 200) / 2, (height - 50) / 2 + 100);

    int seat_seat, totalBusList = 0, busNumber;
    char busName[200], busNameList[300], liscenseid[50];
    FILE *ticketbo, *license;
    ticketbo = fopen(".files/buslist", "r");
    license = fopen(".files/buslistSeatLicence", "r");
    if (ticketbo == NULL || license == NULL)
    {
        list = gtk_label_new("PLEASE REGISTER A BUS FIRST!");
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(list);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), list, (width - 550) / 2, (height - 50) / 2);
    }
    else
    {
        int n = 1;
        while (fgets(busName, 200, ticketbo) != NULL && fscanf(license, "%s %d", liscenseid, &seat_seat) == 2)
        {
            totalBusList++;
            int len = strlen(busName);
            for (int i = 0; i < len; i++)
            {
                if (busName[i] == '\n')
                {
                    busName[i] = ' ';
                    break;
                }
            }
            sprintf(busNameList, "%d. %s- %s", n, busName, liscenseid);
            list = gtk_label_new(busNameList);
            GtkCssProvider *cssProvider = gtk_css_provider_new();
            gtk_css_provider_load_from_data(cssProvider, "label { font-size: 14pt; }", -1, NULL);
            GtkStyleContext *styleContext = gtk_widget_get_style_context(list);
            gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            gtk_grid_attach(GTK_GRID(grid), list, 1, 0 + n, 1, 1);
            n++;
        }
        fclose(ticketbo);

        GtkWidget *label;
        label = gtk_label_new("BUS LIST:");
        GtkCssProvider *cssProvider1 = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 20pt; }", -1, NULL);
        GtkStyleContext *styleContext1 = gtk_widget_get_style_context(label);
        gtk_style_context_add_provider(styleContext1, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), label, 1120, 100);

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
        g_object_set_data(G_OBJECT(book_now), "list1", list1);
        g_signal_connect(book_now, "clicked", G_CALLBACK(book_ticket_system), NULL);
    }
    gtk_widget_show_all(window);
}

void book_ticket_system(GtkWidget *button, gpointer user_data)
{
    GtkWidget *label_1 = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "list1"));
    GtkWidget *book_ticket = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "book_ticket"));
    const gchar *ticket_num = gtk_entry_get_text(GTK_ENTRY(book_ticket));
    if (strcmp(ticket_num, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(label_1), "PLEASE ENTER BUS NUMBER");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(label_1), NULL);
    }
    int ticketNum = atoi(ticket_num);
}