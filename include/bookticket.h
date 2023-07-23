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
    gtk_fixed_put(GTK_FIXED(fixed), grid, 1000, 140);

    GtkWidget *list = gtk_label_new(NULL);

    char liscenseid[200];
    int busTotalSeat;

    FILE *ticketbo, *license, *license1;
    ticketbo = fopen(".files/buslist", "r");
    license = fopen(".files/BusSeatLicense", "r");
    license1 = fopen(".files/BusSeatLicense", "r");
    if (ticketbo == NULL || license == NULL || fscanf(license1, "%d %s ", &busTotalSeat, liscenseid) != 2)
    {
        GtkWidget *list1 = gtk_label_new("PLEASE REGISTER A BUS FIRST!");
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(cssProvider, "label { font-size: 26pt; }", -1, NULL);
        GtkStyleContext *styleContext = gtk_widget_get_style_context(list1);
        gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_fixed_put(GTK_FIXED(fixed), list1, (width - 550) / 2, (height - 50) / 2);
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
         
    }

    gtk_widget_show_all(window);
}

void book_ticket_system(GtkWidget *button, gpointer user_data)
{
    return;
}