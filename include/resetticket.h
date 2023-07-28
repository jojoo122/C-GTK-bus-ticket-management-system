void reset_main(char *);
void reset_bus_ticket_manual(GtkWidget *button);

void reset_bus_list()
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
        gtk_fixed_put(GTK_FIXED(fixed), handler, (width - 240) / 2 - 30, (height - 30) / 2 - 250);

        GtkWidget *handler1 = gtk_label_new("ENTER DATE:");
        styleContext = gtk_widget_get_style_context(handler1);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), handler1, (width - 60) / 2 - 30, (height - 30) / 2 - 150);

        GtkWidget *handler2 = gtk_label_new("ENTER TIME (IN 24 HOUR FORMAT):");
        styleContext = gtk_widget_get_style_context(handler2);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), handler2, (width - 240) / 2 - 30, (height - 30) / 2 - 50);

        GtkWidget *busid = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(busid), "PLEASE ENTER LIST ID OR LICENSE ID");
        gtk_widget_set_size_request(busid, 270, 50);
        gtk_fixed_put(GTK_FIXED(fixed), busid, (width - 270) / 2, (height - 50) / 2 - 210);

        GtkWidget *year = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(year), "YEAR");
        gtk_widget_set_size_request(year, 100, 50);
        gtk_entry_set_max_length(GTK_ENTRY(year), 4);
        g_signal_connect(year, "insert-text", G_CALLBACK(entry_insert_text), NULL);
        gtk_fixed_put(GTK_FIXED(fixed), year, (width - 500) / 2, (height - 50) / 2 - 110);

        GtkWidget *month = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(month), "MONTH");
        gtk_widget_set_size_request(month, 100, 50);
        gtk_entry_set_max_length(GTK_ENTRY(month), 2);
        g_signal_connect(month, "insert-text", G_CALLBACK(entry_insert_text_month), NULL);
        gtk_fixed_put(GTK_FIXED(fixed), month, (width - 160) / 2, (height - 50) / 2 - 110);

        GtkWidget *day = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(day), "DAY");
        gtk_widget_set_size_request(day, 100, 50);
        gtk_entry_set_max_length(GTK_ENTRY(day), 2);
        g_signal_connect(day, "insert-text", G_CALLBACK(entry_insert_text_days), NULL);
        gtk_fixed_put(GTK_FIXED(fixed), day, (width + 180) / 2, (height - 50) / 2 - 110);

        GtkWidget *time_hour = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(time_hour), "HOUR");
        gtk_widget_set_size_request(time_hour, 100, 50);
        gtk_entry_set_max_length(GTK_ENTRY(time_hour), 2);
        g_signal_connect(time_hour, "insert-text", G_CALLBACK(entry_insert_text_hour), NULL);
        gtk_fixed_put(GTK_FIXED(fixed), time_hour, (width - 310) / 2, (height - 50) / 2 - 10);

        GtkWidget *time_min = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(time_min), "MINUTES");
        gtk_widget_set_size_request(time_min, 100, 50);
        gtk_entry_set_max_length(GTK_ENTRY(time_min), 2);
        g_signal_connect(time_min, "insert-text", G_CALLBACK(entry_insert_text_min), NULL);
        gtk_fixed_put(GTK_FIXED(fixed), time_min, (width + 30) / 2, (height - 50) / 2 - 10);

        GtkWidget *book = gtk_button_new_with_label("SET RESET TIME MANUALLY");
        gtk_widget_set_size_request(book, 200, 50);
        gtk_fixed_put(GTK_FIXED(fixed), book, (width - 220) / 2, (height - 50) / 2 + 50);
        g_object_set_data(G_OBJECT(book), "busid", busid);
        g_object_set_data(G_OBJECT(book), "message", message);
        g_object_set_data(G_OBJECT(book), "year", year);
        g_object_set_data(G_OBJECT(book), "month", month);
        g_object_set_data(G_OBJECT(book), "day", day);
        g_object_set_data(G_OBJECT(book), "time_hour", time_hour);
        g_object_set_data(G_OBJECT(book), "time_min", time_min);
        g_signal_connect(book, "clicked", G_CALLBACK(reset_bus_ticket_manual), NULL);
    }

    gtk_widget_show_all(window);
}

void reset_bus_ticket_manual(GtkWidget *button)
{
    GtkWidget *bus_id = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "busid"));
    GtkWidget *year_widget = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "year"));
    GtkWidget *month_widget = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "month"));
    GtkWidget *day_widget = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "day"));
    GtkWidget *time_hour_widget = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "time_hour"));
    GtkWidget *time_min_widget = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "time_min"));
    GtkWidget *message = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "message"));

    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    int current_year = localTime->tm_year + 1900;
    int current_month = localTime->tm_mon + 1;
    int current_day = localTime->tm_mday;
    int current_hour = localTime->tm_hour;
    int current_minute = localTime->tm_min;
    int current_second = localTime->tm_sec;

    const gchar *busId = gtk_entry_get_text(GTK_ENTRY(bus_id));
    const gchar *year = gtk_entry_get_text(GTK_ENTRY(year_widget));
    const gchar *month = gtk_entry_get_text(GTK_ENTRY(month_widget));
    const gchar *day = gtk_entry_get_text(GTK_ENTRY(day_widget));
    const gchar *time_hour = gtk_entry_get_text(GTK_ENTRY(time_hour_widget));
    const gchar *time_minutes = gtk_entry_get_text(GTK_ENTRY(time_min_widget));

    int user_entered_year = atoi(year);
    int user_entered_month = atoi(month);
    int user_entered_day = atoi(day);
    int hour = atoi(time_hour);
    int minutes = atoi(time_minutes);

    int lenbid = strlen(busId), count = 0;
    for (int i = 0; i < lenbid; i++)
    {
        if (busId[i] == 32)
        {
            ++count;
            break;
        }
    }
    if (strcmp(busId, "") == 0 && strcmp(year, "") == 0 && strcmp(month, "") == 0 && strcmp(day, "") == 0 && strcmp(time_hour, "") == 0 && strcmp(time_minutes, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(message), "PLEASE ENTER ALL THE REQUIRED INFORMATIONS");
    }
    else if (strcmp(busId, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(message), "PLEASE ENTER THE BUS ID OR LICENSE PLATE NUMBER");
    }
    else if (strcmp(year, "") == 0 || strcmp(month, "") == 0 || strcmp(day, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(message), "PLEASE ENTER THE DATE");
    }
    else if (strcmp(time_hour, "") == 0 || strcmp(time_minutes, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(message), "PLEASE ENTER THE TIME");
    }
    else if (count == 1)
    {
        gtk_label_set_text(GTK_LABEL(message), "BUS ID CAN NOT CONTAIN SPACE");
    }
    else if ((user_entered_year - current_year) < 0)
    {
        gtk_label_set_text(GTK_LABEL(message), "INVALID DATE");
    }
    else if (user_entered_year == current_year)
    {
        if ((user_entered_month - current_month) < 0)
        {
            gtk_label_set_text(GTK_LABEL(message), "INVALID DATE");
        }
        else if (user_entered_month == current_month)
        {
            if ((user_entered_day - current_day) < 0)
            {
                gtk_label_set_text(GTK_LABEL(message), "INVALID DATE");
            }
            else if (user_entered_day == current_day)
            {
                if ((hour - current_hour) < 0)
                {
                    gtk_label_set_text(GTK_LABEL(message), "INVALID TIME");
                }
                else if (hour == current_hour)
                {
                    if ((minutes - current_minute) < 0)
                    {
                        gtk_label_set_text(GTK_LABEL(message), "INVALID TIME");
                    }
                    else if (minutes == current_minute)
                    {
                        gtk_label_set_text(GTK_LABEL(message), "INVALID TIME");
                    }
                    else
                    {
                        goto label;
                    }
                }
                else
                {
                    goto label;
                }
            }
            else
            {
                goto label;
            }
        }
        else
        {
            goto label;
        }
    }
    else
    {
    label:
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
                char resetfile[1000];
                sprintf(resetfile, ".files/ResetTime-%s", lsid);
                FILE *resetTime = fopen(resetfile, "w");
                fprintf(resetTime, "%d %d %d %d %d", user_entered_year, user_entered_month, user_entered_day, hour, minutes);
                fclose(resetTime);
                gtk_label_set_text(GTK_LABEL(message), "SUCCESS");
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
                char resetfile[1000];
                sprintf(resetfile, ".files/ResetTime-%s", lsid);
                FILE *resetTime = fopen(resetfile, "w");
                fprintf(resetTime, "%d %d %d %d %d", user_entered_year, user_entered_month, user_entered_day, hour, minutes);
                fclose(resetTime);
                gtk_label_set_text(GTK_LABEL(message), "SUCCESS");
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(message), "INVALID LICENSE ID!");
            }
        }
    }
}

void resetbus(char LID[])
{
    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    char file[1000];
    int scyear, scmonth, scday, schour, scmin;
    sprintf(file, ".files/ResetTime-%s", LID);
    FILE *create = fopen(file, "a");
    fclose(create);

    FILE *reset = fopen(file, "r");
    if (fscanf(reset, "%d %d %d %d %d", &scyear, &scmonth, &scday, &schour, &scmin) == 5)
    {
        if ((year - scyear) >= 1 || (month - scmonth) >= 1)
        {
            reset_main(LID);
            FILE *open = fopen(file, "w");
            fprintf(open, "%d %d %d %d %d", year, month, day, hour, minute);
            fclose(open);
        }
        else if ((day - scday) == 1 && (hour - schour) <= 0 && (minute - scmin) >= 0)
        {
            reset_main(LID);
            FILE *open = fopen(file, "w");
            fprintf(open, "%d %d %d %d %d", year, month, day, hour, minute);
            fclose(open);
        }
        else if ((day - scday) >= 2)
        {
            reset_main(LID);
            FILE *open = fopen(file, "w");
            fprintf(open, "%d %d %d %d %d", year, month, day, hour, minute);
            fclose(open);
        }
    }
    else if (fscanf(reset, "%d %d %d %d %d", &scyear, &scmonth, &scday, &schour, &scmin) != 5)
    {
        FILE *open = fopen(file, "w");
        fprintf(open, "%d %d %d %d %d", year, month, day, hour, minute);
        fclose(open);
    }
    fclose(reset);
}

void reset_main(char licenseID[])
{
    char boBus[1000], unboBus[1000], usrinfo[1000], usrph[1000], li[500];
    int totalSeat;
    sprintf(boBus, ".files/Booked-%s", licenseID);
    sprintf(unboBus, ".files/UnBooked-%s", licenseID);
    sprintf(usrinfo, ".files/UserInfo-%s", licenseID);
    sprintf(usrph, ".files/UserInfoPhone-%s", licenseID);
    FILE *tose = fopen(".files/BusSeatLicense", "r");
    while (fscanf(tose, "%d %s ", &totalSeat, li) == 2)
    {
        if (strcmp(li, licenseID) == 0)
        {
            break;
        }
    }
    FILE *booked, *unBooked, *userInfo, *userPhone;
    booked = fopen(boBus, "w");
    unBooked = fopen(unboBus, "w");
    userInfo = fopen(usrinfo, "w");
    userPhone = fopen(usrph, "w");
    for (int i = 1; i <= totalSeat; i++)
    {
        fprintf(unBooked, "%d ", i);
    }
    fclose(booked);
    fclose(unBooked);
    fclose(userInfo);
    fclose(userPhone);
    fclose(tose);
}