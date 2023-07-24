void bus_register(GtkWidget *button, gpointer user_data);

void registerBus()
{
    clearmywindow();
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_window_fullscreen(GTK_WINDOW(window));

    GtkWidget *registrationsuccess = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), registrationsuccess, (width - 170) / 2, height - 225);

    GtkWidget *longmessage = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), longmessage, (width - 300) / 2, height - 225);

    GtkWidget *busname_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(busname_entry), "BUS NAME");
    gtk_widget_set_size_request(busname_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), busname_entry, (width - 200) / 2, (height - 50) / 2 - 60);

    GtkWidget *total_seat_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(total_seat_entry), "TOTAL NUMBER OF SEATS");
    gtk_entry_set_max_length(GTK_ENTRY(total_seat_entry), 2);
    g_signal_connect(total_seat_entry, "insert-text", G_CALLBACK(entry_insert_text), NULL);
    gtk_widget_set_size_request(total_seat_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), total_seat_entry, (width - 200) / 2, (height - 50) / 2);

    GtkWidget *bus_register_number = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(bus_register_number), "ENTER THE BUS LICENSE PLATE NUMBER");
    gtk_widget_set_size_request(bus_register_number, 300, 50);
    gtk_fixed_put(GTK_FIXED(fixed), bus_register_number, (width - 300) / 2, (height - 50) / 2 + 60);

    GtkWidget *button_register_bus = gtk_button_new_with_label("Register Bus");
    gtk_widget_set_size_request(button_register_bus, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed), button_register_bus, (width - 200) / 2, (height - 50) / 2 + 120);

    g_object_set_data(G_OBJECT(button_register_bus), "busname_entry", busname_entry);
    g_object_set_data(G_OBJECT(button_register_bus), "total_seat_entry", total_seat_entry);
    g_object_set_data(G_OBJECT(button_register_bus), "bus_register_number", bus_register_number);
    g_object_set_data(G_OBJECT(button_register_bus), "registrationsuccess", registrationsuccess);
    g_object_set_data(G_OBJECT(button_register_bus), "longmessage", longmessage);
    g_signal_connect(button_register_bus, "clicked", G_CALLBACK(bus_register), NULL);

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(adminpannel), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);

    // header and footer text
    showHF();

    GtkWidget *request2 = gtk_label_new("PLEASE ENTER THE NEW BUS INFO");
    GtkCssProvider *cssProvider2 = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider2, "label { font-size: 20pt; }", -1, NULL);
    GtkStyleContext *styleContext2 = gtk_widget_get_style_context(request2);
    gtk_style_context_add_provider(styleContext2, GTK_STYLE_PROVIDER(cssProvider2), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_fixed_put(GTK_FIXED(fixed), request2, (width - 400) / 2, 200);

    gtk_widget_show_all(window);
}
void bus_register(GtkWidget *button, gpointer user_data)
{
    GtkWidget *busname_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "busname_entry"));
    GtkWidget *total_seat_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "total_seat_entry"));
    GtkWidget *bus_register_number = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "bus_register_number"));
    GtkWidget *registrationsuccess = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "registrationsuccess"));
    GtkWidget *longmessage = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "longmessage"));

    const gchar *busname = gtk_entry_get_text(GTK_ENTRY(busname_entry));
    const gchar *total_seat = gtk_entry_get_text(GTK_ENTRY(total_seat_entry));
    const gchar *busRegisterNumber = gtk_entry_get_text(GTK_ENTRY(bus_register_number));

    char busName[500], licenseNumber[200], chklis[200];
    strcpy(busName, busname);
    char boBus[1000], unboBus[1000], usrinfo[1000],usrph[1000];
    strcpy(licenseNumber, busRegisterNumber);
    int totalSeat = atoi(total_seat);
    int len = strlen(licenseNumber), space = 0, seet;
    for (int i = 0; i < len; i++)
    {
        if (licenseNumber[i] == 32)
        {
            ++space;
            break;
        }
    }
    if (strcmp(busName, "") == 0 || strcmp(total_seat, "") == 0 || strcmp(licenseNumber, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(registrationsuccess), NULL);
        gtk_label_set_text(GTK_LABEL(longmessage), "REQUIRED INFORMATIONS ARE NOT ENTERED");
    }
    else if (strlen(busName) < 3)
    {
        gtk_label_set_text(GTK_LABEL(registrationsuccess), NULL);
        gtk_label_set_text(GTK_LABEL(longmessage), "BUS NAME MUST BE 3 OR MORE CHARACTERS!");
    }
    else if (space == 1)
    {
        gtk_label_set_text(GTK_LABEL(registrationsuccess), NULL);
        gtk_label_set_text(GTK_LABEL(longmessage), "BUS LICENSE PLATE NUMBER CAN NOT CONTAIN SPACE!");
    }
    else
    {
        FILE *check = fopen(".files/BusSeatLicense", "r");
        memset(chklis, 0, sizeof(chklis));
        if (check == NULL)
        {
            goto label;
        }
        else
        {
            while (fscanf(check, "%d %s ", &seet, chklis) == 2)
            {
                if (strcmp(licenseNumber, chklis) == 0)
                {
                    break;
                }
            }
            char linb[500];
            strcpy(linb,licenseNumber);
            len = strlen(linb);
            for (int i = 0; i < len; i++)
            {
                linb[i] = tolower(linb[i]);
            }
            len = strlen(chklis);
            for (int i = 0; i < len; i++)
            {
                chklis[i] = tolower(chklis[i]);
            }
            if (strcmp(linb, chklis) == 0)
            {
                gtk_label_set_text(GTK_LABEL(registrationsuccess), "ALREADY EXISTS!");
                gtk_label_set_text(GTK_LABEL(longmessage), NULL);
            }
            else
            {
            label:
                sprintf(boBus, ".files/Booked-%s", licenseNumber);
                sprintf(unboBus, ".files/UnBooked-%s", licenseNumber);
                sprintf(usrinfo, ".files/UserInfo-%s", licenseNumber);
                sprintf(usrph, ".files/UserInfoPhone-%s", licenseNumber);
                FILE *make1, *make2, *make3, *make4, *make5, *make6;
                make5 = fopen(".files/buslist", "a");
                fprintf(make5, "%s\n", busName);
                make1 = fopen(".files/BusSeatLicense", "a");
                fprintf(make1, "%d %s ", totalSeat, licenseNumber);
                make2 = fopen(boBus, "a");
                make3 = fopen(usrinfo, "a");
                make4 = fopen(unboBus, "a");
                make6 = fopen(usrph,"a");
                for (int i = 1; i <= totalSeat; i++)
                {
                    fprintf(make4, "%d ", i);
                }
                fclose(make6);
                fclose(make5);
                fclose(make4);
                fclose(make3);
                fclose(make2);
                fclose(make1);
                gtk_label_set_text(GTK_LABEL(registrationsuccess), "REGISTRATION SUCCESSFULL!");
                gtk_label_set_text(GTK_LABEL(longmessage), NULL);
                adminpannel();
            }
        }
    }
}