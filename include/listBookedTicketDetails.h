void list_ticket_system(GtkWidget *button);
void listBus(char *);
void listDetail()
{
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    showLEV2("admin");
    showHF();

    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, 1000, 140);

    GtkWidget *list = gtk_label_new(NULL);

    GtkWidget *message = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), message, (width - 200) / 2, (height - 50) / 2 + 100);

    char liscenseid[200];
    int busTotalSeat;

    FILE *ticketbo, *license, *license1;
    ticketbo = fopen(".files/buslist", "r");
    license = fopen(".files/BusSeatLicense", "r");
    license1 = fopen(".files/BusSeatLicense", "r");
    if (ticketbo == NULL || license == NULL || fscanf(license1, "%d %s ", &busTotalSeat, liscenseid) != 2)
    {
        GtkWidget *list1;
        if (iden == 1)
        {
            list1 = gtk_label_new("PLEASE REGISTER A BUS FIRST!");
            gtk_fixed_put(GTK_FIXED(fixed), list1, (width - 550) / 2, (height - 50) / 2);
        }
        if (iden == 0)
        {
            list1 = gtk_label_new("NO BUS FOUND!");
            gtk_fixed_put(GTK_FIXED(fixed), list1, (width - 270) / 2, (height - 50) / 2);
        }
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(list1);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }
    else if (ticketbo != NULL && license != NULL)
    {
        fclose(license1);
        memset(liscenseid, 0, sizeof(liscenseid));
        int totalBusList = 0, busNumber, chkseat, n = 0, bus = 1;
        char busName[500], busNameList[800], prlid[200];
        GtkWidget *label;
        label = gtk_label_new("BUS LIST:");
        GtkCssProvider *cssProvider1 = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 20pt; }", -1, NULL);
        GtkStyleContext *styleContext1 = gtk_widget_get_style_context(label);
        gtk_style_context_add_provider(styleContext1, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), label, 1120, 100);

        while (fgets(busName, 500, ticketbo) != NULL && fscanf(license, "%d %s ", &chkseat, prlid) == 2)
        {
            for (int i = 0; i < strlen(busName); i++)
            {
                if (busName[i] == '\n')
                {
                    busName[i] = 32;
                }
            }
            if (strlen(busName) < 40)
            {
                sprintf(busNameList, "%d. %s- %s\n", bus, busName, prlid);
            }
            else
            {
                if (strlen(busName) > 50)
                {
                    int len;
                    if (strlen(busName) % 2 == 0)
                    {
                        len = strlen(busName) / 2;
                    }
                    else
                    {
                        len = (strlen(busName) + 1) / 2;
                    }
                    char half1[len], half2[len];
                    int n = 0;
                    for (int i = 0; i < strlen(busName); i++)
                    {
                        if (i < len)
                        {
                            half1[n] = busName[i];
                            n++;
                        }
                        if (i == len)
                        {
                            n = 0;
                        }
                        if (i >= len)
                        {
                            half2[n] = busName[i];
                            n++;
                        }
                    }
                    sprintf(busNameList, "%d. %s \n %s - %s\n", bus, half1, half2, prlid);
                }
            }

            list = gtk_label_new(busNameList);

            GtkStyleContext *styleContext = gtk_widget_get_style_context(list);
            GtkCssProvider *cssProvider1 = gtk_css_provider_new();
            gtk_css_provider_load_from_data(cssProvider1, "label { font-size: 12pt; }", -1, NULL);
            gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            gtk_grid_attach(GTK_GRID(grid), list, 1, 0 + n, 1, 1);
            n += 10;
            bus++;
        }
        fclose(ticketbo);
        fclose(license);

        GtkWidget *handler = gtk_label_new("ENTER BUS LIST ID OR LICENSE ID:");
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 14pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(handler);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), handler, (width - 240) / 2 - 30, (height - 30) / 2 - 80);

        GtkWidget *busid = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(busid), "PLEASE ENTER LIST ID OR LICENSE ID");
        gtk_widget_set_size_request(busid, 270, 50);
        gtk_fixed_put(GTK_FIXED(fixed), busid, (width - 270) / 2, (height - 50) / 2 - 30);

        GtkWidget *book = gtk_button_new_with_label("GO TO BOOKING PORTAL");
        gtk_widget_set_size_request(book, 200, 50);
        gtk_fixed_put(GTK_FIXED(fixed), book, (width - 200) / 2, (height - 50) / 2 + 30);
        g_object_set_data(G_OBJECT(book), "busid", busid);
        g_object_set_data(G_OBJECT(book), "message", message);
        g_signal_connect(book, "clicked", G_CALLBACK(list_ticket_system), NULL);
    }

    gtk_widget_show_all(window);
}

void list_ticket_system(GtkWidget *button)
{
    GtkWidget *bus_id = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "busid"));
    GtkWidget *message = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "message"));

    const gchar *busId = gtk_entry_get_text(GTK_ENTRY(bus_id));

    int lenbid = strlen(busId), count = 0;
    for (int i = 0; i < lenbid; i++)
    {
        if (busId[i] == 32)
        {
            ++count;
            break;
        }
    }

    if (strcmp(busId, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(message), "PLEASE ENTER THE BUS ID OR LICENSE PLATE NUMBER");
    }
    else if (count == 1)
    {
        gtk_label_set_text(GTK_LABEL(message), "CAN NOT CONTAIN SPACE");
    }
    else
    {
        count = 0;
        for (int i = 0; i < lenbid; i++)
        {
            if (busId[i] >= 33 && busId[i] <= 47 || busId[i] >= 58 && busId[i] <= 126)
            {
                count++;
                break;
            }
        }
        if (count == 0)
        {
            int elistnum = atoi(busId);
            int seat, listnum = 1;
            char lsid[200];
            count = 0;
            FILE *fptrr = fopen(".files/BusSeatLicense", "r");
            while (fscanf(fptrr, "%d %s ", &seat, lsid) == 2)
            {
                ++count;
            }
            fclose(fptrr);
            FILE *fptr = fopen(".files/BusSeatLicense", "r");
            while (fscanf(fptr, "%d %s ", &seat, lsid) == 2)
            {
                if (listnum == elistnum)
                {
                    break;
                }
                if (listnum < count)
                {
                    ++listnum;
                }
            }
            if (listnum != elistnum)
            {
                gtk_label_set_text(GTK_LABEL(message), "INVALID LIST ID!");
            }
            else
            {
                listBus(lsid);
            }
            if (fptr != NULL)
            {
                fclose(fptr);
            }
        }
        else
        {
            int a = strlen(busId);
            char busid[a];
            strcpy(busid, busId);
            int seat = 0;
            char lsid[500], lsId[500];
            memset(lsid, 0, sizeof(lsid));
            for (int i = 0; i < a; i++)
            {
                busid[i] = tolower(busid[i]);
            }
            FILE *fptr1 = fopen(".files/BusSeatLicense", "r");
            while (fscanf(fptr1, "%d %s ", &seat, lsid) == 2)
            {
                strcpy(lsId, lsid);
                int b = strlen(lsId);
                for (int i = 0; i < b; i++)
                {
                    lsId[i] = tolower(lsId[i]);
                }
                if (strcmp(lsId, busid) == 0)
                {
                    break;
                }
            }
            fclose(fptr1);
            if (strcmp(lsId, busid) == 0)
            {
                listBus(lsid);
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(message), "INVALID LICENSE ID!");
            }
        }
    }
}

void listBus(char llid[])
{
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    showHF();

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(listDetail), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, 1220, 300);

    GtkWidget *label = gtk_label_new(NULL);

    char FullBusName[2000], lid[500], bn[1000];
    int seat;
    FILE *fptr = fopen(".files/buslist", "r"), *fptr2 = fopen(".files/BusSeatLicense", "r");
    while (fscanf(fptr2, "%d %s ", &seat, lid) == 2 && fgets(bn, 1000, fptr) != NULL)
    {
        if (strcmp(llid, lid) == 0)
        {
            break;
        }
    }
    fclose(fptr);
    fclose(fptr2);

    int len = strlen(bn);
    for (int i = 0; i < len; i++)
    {
        if (bn[i] == '\n')
        {
            bn[i] = 32;
            break;
        }
    }

    sprintf(FullBusName, "%s- %s", bn, lid);

    char tempch[1000];
    sprintf(tempch, ".files/Booked-%s", lid);

    FILE *chk = fopen(tempch, "r");
    if (fscanf(chk, "%d ", &seat) != 1)
    {
        GtkWidget *list1 = gtk_label_new("NO BOOKED TICKET FOUND!");
        gtk_fixed_put(GTK_FIXED(fixed), list1, (width - 460) / 2, (height - 50) / 2);
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(list1);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        fclose(chk);
    }
    else
    {
        fclose(chk);
        GtkWidget *busName = gtk_label_new(FullBusName);
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 20pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(busName);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), busName, (width - 350) / 2, (height - 620) / 2);

        GtkWidget *passengerName = gtk_label_new("Passenger's Name:");
        cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 16pt; }", -1, NULL);
        styleContext = gtk_widget_get_style_context(passengerName);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), passengerName, (width - 1300) / 2, (height - 510) / 2);

        GtkWidget *passengerPhNum = gtk_label_new("Passenger's Phone Number:");
        cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 16pt; }", -1, NULL);
        styleContext = gtk_widget_get_style_context(passengerPhNum);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), passengerPhNum, (width - 300) / 2, (height - 510) / 2);

        GtkWidget *ticketNumber = gtk_label_new("Passenger's Seat Number:");
        cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 16pt; }", -1, NULL);
        styleContext = gtk_widget_get_style_context(ticketNumber);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), ticketNumber, (width + 760) / 2, (height - 510) / 2);

        GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        gtk_widget_set_size_request(scrolled_window, width - 60, height - 300);
        gtk_fixed_put(GTK_FIXED(fixed), scrolled_window, (width - 1300) / 2, (height - 420) / 2);

        GtkWidget *main_grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(scrolled_window), main_grid);

        GtkWidget *event_box1 = gtk_event_box_new();
        GtkWidget *event_box2 = gtk_event_box_new();
        GtkWidget *event_box3 = gtk_event_box_new();

        gtk_widget_set_size_request(event_box1, 600, 100);
        gtk_widget_set_size_request(event_box2, 580, 100);
        gtk_widget_set_size_request(event_box3, 100, 100);

        GtkWidget *grid1 = gtk_grid_new();
        GtkWidget *grid2 = gtk_grid_new();
        GtkWidget *grid3 = gtk_grid_new();

        gtk_container_add(GTK_CONTAINER(event_box1), grid1);
        gtk_container_add(GTK_CONTAINER(event_box2), grid2);
        gtk_container_add(GTK_CONTAINER(event_box3), grid3);

        gtk_grid_attach(GTK_GRID(main_grid), event_box1, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(main_grid), event_box2, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(main_grid), event_box3, 2, 0, 1, 1);

        char userName[1000], userPhoneNumber[1000], SeatNumber[20];
        char file1[1000], file2[1000], file3[1000];
        int temp;
        seat = 0;

        sprintf(file1, ".files/UserInfo-%s", llid);
        sprintf(file2, ".files/UserInfoPhone-%s", llid);
        sprintf(file3, ".files/Booked-%s", llid);

        FILE *userDetail_1, *userDetail_2, *seatnumber;
        userDetail_1 = fopen(file1, "r");
        userDetail_2 = fopen(file2, "r");
        seatnumber = fopen(file3, "r");
        int i = 0;

        while (fscanf(seatnumber, "%d ", &seat) == 1 && fgets(userName, 1000, userDetail_1) != NULL && fscanf(userDetail_2, "%s ", userPhoneNumber) == 1)
        {
            label = gtk_label_new(userName);
            gtk_grid_attach(GTK_GRID(grid1), label, 0, 1 + i, 1, 1);

            cssProvider = gtk_css_provider_new();
            gtk_css_provider_load_from_data(cssProvider, "label { font-size: 12pt; }", -1, NULL);
            styleContext = gtk_widget_get_style_context(label);
            gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

            temp = strlen(userPhoneNumber);
            userPhoneNumber[temp] = '\n';
            label = gtk_label_new(userPhoneNumber);
            gtk_grid_attach(GTK_GRID(grid2), label, 0, 1 + i, 1, 1);

            cssProvider = gtk_css_provider_new();
            gtk_css_provider_load_from_data(cssProvider, "label { font-size: 12pt; }", -1, NULL);
            styleContext = gtk_widget_get_style_context(label);
            gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

            sprintf(SeatNumber, "%d\n", seat);
            label = gtk_label_new(SeatNumber);
            gtk_grid_attach(GTK_GRID(grid3), label, 0, 1 + i, 1, 1);

            cssProvider = gtk_css_provider_new();
            gtk_css_provider_load_from_data(cssProvider, "label { font-size: 12pt; }", -1, NULL);
            styleContext = gtk_widget_get_style_context(label);
            gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
            i++;
        }
        fclose(userDetail_1);
        fclose(userDetail_2);
        fclose(seatnumber);
    }

    gtk_widget_show_all(window);
}