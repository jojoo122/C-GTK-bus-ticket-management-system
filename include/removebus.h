void remove_bus(char *);
void remove_bus_system(GtkWidget *button);
void removeBus()
{
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    showLEV2("admin");
    showHF();

    GtkWidget *message = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), message, (width - 200) / 2, (height - 50) / 2 + 80);

    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, 1000, 140);

    GtkWidget *list = gtk_label_new(NULL);

    char licid[500], bn[200];
    int seat;
    FILE *filecheck = fopen(".files/BusSeatLicense", "r");
    FILE *filecheck1 = fopen(".files/BusSeatLicense", "r");
    FILE *filecheck2 = fopen(".files/buslist", "r");
    if (filecheck == NULL || filecheck2 == NULL || fscanf(filecheck1, "%d %s ", &seat, licid) != 2)
    {
        GtkWidget *list1 = gtk_label_new("PLEASE REGISTER A BUS FIRST!");
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(list1);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), list1, (width - 550) / 2, (height - 50) / 2);
    }
    else
    {
        fclose(filecheck);
        fclose(filecheck1);
        fclose(filecheck2);

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

        char liscenseid[200];
        int busTotalSeat;
        FILE *ticketbo, *license, *license1;
        ticketbo = fopen(".files/buslist", "r");
        license = fopen(".files/BusSeatLicense", "r");
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

        GtkWidget *remove = gtk_button_new_with_label("REMOVE");
        gtk_widget_set_size_request(remove, 200, 50);
        gtk_fixed_put(GTK_FIXED(fixed), remove, (width - 200) / 2, (height - 50) / 2 + 30);
        g_object_set_data(G_OBJECT(remove), "busid", busid);
        g_object_set_data(G_OBJECT(remove), "message", message);
        g_signal_connect(remove, "clicked", G_CALLBACK(remove_bus_system), NULL);
    }

    gtk_widget_show_all(window);
}

void remove_bus_system(GtkWidget *button)
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
                remove_bus(lsid);
                gtk_label_set_text(GTK_LABEL(message), "SUCCESSFULLY REMOVED");
                g_timeout_add(500, addDelay, NULL);
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
                remove_bus(lsid);
                gtk_label_set_text(GTK_LABEL(message), "SUCCESSFULLY REMOVED!");
                g_timeout_add(500, addDelay, NULL);
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(message), "INVALID LICENSE ID!");
            }
        }
    }
}

void remove_bus(char lesid[])
{
    char busNm[500], lsid[200];
    char boBus[1000], unboBus[1000], usrin[1000], usrph[1000],retime[1000];
    sprintf(retime,".files/ResetTime-%s",lesid);
    sprintf(boBus, ".files/Booked-%s", lesid);
    sprintf(unboBus, ".files/UnBooked-%s", lesid);
    sprintf(usrin, ".files/UserInfo-%s", lesid);
    sprintf(usrph, ".files/UserInfoPhone-%s", lesid);
    int st;
    FILE *bussl, *buslt, *temp1, *temp2;
    bussl = fopen(".files/BusSeatLicense", "r");
    temp1 = fopen(".files/temp1", "a");
    temp2 = fopen(".files/temp2", "a");
    buslt = fopen(".files/buslist", "r");
    while (fscanf(bussl, "%d %s ", &st, lsid) == 2 && fgets(busNm, 500, buslt) != NULL)
    {
        if (strcmp(lesid, lsid) != 0)
        {
            fprintf(temp1, "%d %s ", st, lsid);
            fprintf(temp2, "%s\n", busNm);
        }
    }
    fclose(bussl);
    fclose(buslt);
    fclose(temp1);
    fclose(temp2);

    remove(usrph);
    remove(boBus);
    remove(unboBus);
    remove(usrin);
    remove(retime);

    remove(".files/buslist");
    remove(".files/BusSeatLicense");

    rename(".files/temp1", ".files/BusSeatLicense");
    rename(".files/temp2", ".files/buslist");
}