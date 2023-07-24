int chkarr(int arr[], int n, int pp)
{
    for (int i = 0; i < pp; i++)
    {
        if (arr[i] == n)
        {
            return 1;
        }
    }
    return 0;
}
char lid[500];
void returnNumberTicket(GtkWidget *button, gpointer data);
void book_ticket_system(GtkWidget *button);
void listBUSTicket();
void bookTicket()
{
    clearmywindow();
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
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
        g_signal_connect(book, "clicked", G_CALLBACK(book_ticket_system), NULL);
    }

    gtk_widget_show_all(window);
}

void book_ticket_system(GtkWidget *button)
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
            FILE *fptr = fopen(".files/BusSeatLicense", "r");
            while (fscanf(fptr, "%d %s ", &seat, lsid) == 2)
            {
                if (listnum == elistnum)
                {
                    break;
                }
                listnum++;
            }
            if (listnum != elistnum)
            {
                gtk_label_set_text(GTK_LABEL(message), "INVALID LIST ID!");
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(message), "REDIRECTING");
                listBUSTicket(seat, lsid);
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
                listBUSTicket(seat, lsid);
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(message), "INVALID LICENSE ID!");
            }
        }
    }
}
void listBUSTicket(int seat, char lcid[])
{
    clearmywindow();
    strcpy(lid, lcid);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    showHF();

    GtkWidget *goback = gtk_button_new_with_label("GO BACK");
    g_signal_connect(goback, "clicked", G_CALLBACK(bookTicket), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), goback, 5, 5);
    GtkWidget *exit = gtk_button_new_with_label("EXIT");
    g_signal_connect(exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), exit, width - 70, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(fixed), grid, 1220, 300);

    GtkWidget *label;

    GtkWidget *message = gtk_label_new(NULL);
    gtk_fixed_put(GTK_FIXED(fixed), message, (width - 110) / 2, (height - 10) / 2 + 150);

    label = gtk_label_new("  BUS TICKETS THAT\nARE BOOKED ARE RED");
    gtk_fixed_put(GTK_FIXED(fixed), label, 1200, 260);

    GtkWidget *handler1 = gtk_label_new("ENTER TICKET NUMBER:");
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 14pt; }", -1, NULL);
    GtkStyleContext *styleContext = gtk_widget_get_style_context(handler1);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_fixed_put(GTK_FIXED(fixed), handler1, (width - 240) / 2, (height - 30) / 2 - 180);

    GtkWidget *bus_ticket_number = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(bus_ticket_number), "PLEASE ENTER TICKET NUMBER");
    gtk_widget_set_size_request(bus_ticket_number, 240, 50);
    gtk_entry_set_max_length(GTK_ENTRY(bus_ticket_number), 3);
    g_signal_connect(bus_ticket_number, "insert-text", G_CALLBACK(entry_insert_text), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), bus_ticket_number, (width - 240) / 2, (height - 30) / 2 - 150);

    GtkWidget *handler2 = gtk_label_new("ENTER PASSENGER'S NAME:");
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 13pt; }", -1, NULL);
    styleContext = gtk_widget_get_style_context(handler2);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_fixed_put(GTK_FIXED(fixed), handler2, (width - 240) / 2, (height - 30) / 2 - 80);

    GtkWidget *usernamedetail = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(usernamedetail), "PLEASE ENTER PASSENGER'S NAME");
    gtk_widget_set_size_request(usernamedetail, 240, 50);
    gtk_fixed_put(GTK_FIXED(fixed), usernamedetail, (width - 240) / 2, (height - 30) / 2 - 50);

    GtkWidget *handler3 = gtk_label_new("ENTER PASSENGER'S PHONE NUMBER:");
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, "label { font-size: 11pt; }", -1, NULL);
    styleContext = gtk_widget_get_style_context(handler3);
    gtk_style_context_add_provider(styleContext, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_fixed_put(GTK_FIXED(fixed), handler3, (width - 240) / 2 - 20, (height - 30) / 2 + 20);

    GtkWidget *userphnumber = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(userphnumber), "PLEASE ENTER PASSENGER'S PHONE NUMBER");
    gtk_widget_set_size_request(userphnumber, 300, 50);
    gtk_entry_set_max_length(GTK_ENTRY(userphnumber), 10);
    g_signal_connect(userphnumber, "insert-text", G_CALLBACK(entry_insert_text), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), userphnumber, (width - 300) / 2, (height - 30) / 2 + 50);

    GtkWidget *book_button = gtk_button_new_with_label("BOOK NOW");
    gtk_widget_set_size_request(book_button, 100, 40);
    g_object_set_data(G_OBJECT(book_button), "bus_ticket_number", bus_ticket_number);
    g_object_set_data(G_OBJECT(book_button), "usernamedetail", usernamedetail);
    g_object_set_data(G_OBJECT(book_button), "userphnumber", userphnumber);
    g_object_set_data(G_OBJECT(book_button), "message", message);
    gtk_fixed_put(GTK_FIXED(fixed), book_button, (width - 100) / 2 - 10, (height - 10) / 2 + 100);
    g_object_set_data(G_OBJECT(book_button), "bus_ticket_number", bus_ticket_number);
    g_signal_connect(book_button, "clicked", G_CALLBACK(returnNumberTicket), (gpointer)lcid);

    int totalseat = seat;
    int tems = totalseat;
    int row = 4;
    int col;
    int q = 0;

    char boBus[800];
    sprintf(boBus, ".files/Booked-%s", lcid);

    int qr = 0, ar[totalseat];
    memset(ar, 0, sizeof(ar));

    FILE *booked, *booked1;
    booked = fopen(boBus, "r");
    booked1 = fopen(boBus, "r");
    if (fscanf(booked1, "%d ", &ar[qr]) != 1)
    {
        qr++;
    }
    else
    {
        while (fscanf(booked, "%d", &ar[qr]) == 1)
        {
            qr++;
        }
    }
    if (booked != NULL)
    {
        fclose(booked);
        fclose(booked1);
    }

    if (totalseat % 4 != 0)
    {
        while (1)
        {
            if ((totalseat - q) % 4 == 0)
            {
                col = (totalseat - q) / row;
                break;
            }
            q++;
        }
    }
    else
    {
        q = 1;
    }
    int k = 1, te;
    int y;
    int v = 0;
    if (totalseat % 4 != 0)
    {
        for (int i = q - 1; i > 0; i--)
        {
            for (int yy = 0; yy < qr; yy++)
            {
                if (ar[yy] == k)
                {
                    char button_label[10];
                    sprintf(button_label, "0%d ", k);
                    label = gtk_label_new(button_label);
                    GtkStyleContext *context = gtk_widget_get_style_context(label);
                    gtk_style_context_add_class(context, "red-label");
                    gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                }
                else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                {
                    char button_label[10];
                    sprintf(button_label, "0%d ", k);
                    label = gtk_label_new(button_label);
                    gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                }
            }
            k++;
            v++;
        }

        for (int i = col; i > 0; i--)
        {
            y = 1;
            te = 0;
            for (int j = row; j > 0; j--)
            {
                if (te == 2)
                {
                    y = j + 2;
                }
                if (k < 10)
                {
                    for (int yy = 0; yy < qr; yy++)
                    {
                        if (ar[yy] == k)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            GtkStyleContext *context = gtk_widget_get_style_context(label);
                            gtk_style_context_add_class(context, "red-label");
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                        else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                    }
                    k++;
                }
                else
                {
                    for (int yy = 0; yy < qr; yy++)
                    {
                        if (ar[yy] == k)
                        {
                            char button_label[10];
                            sprintf(button_label, "%d ", k);
                            label = gtk_label_new(button_label);
                            GtkStyleContext *context = gtk_widget_get_style_context(label);
                            gtk_style_context_add_class(context, "red-label");
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                        else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                        {
                            char button_label[10];
                            sprintf(button_label, "%d ", k);
                            label = gtk_label_new(button_label);
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                    }
                    k++;
                }
                if (k == totalseat - 4)
                {
                    break;
                }
                te++;
                y++;
            }
            if (k == totalseat - 4)
            {
                break;
            }
        }
        int p = 1;
        while (1)
        {
            if (k != totalseat - 1)
            {
                for (int yy = 0; yy < qr; yy++)
                {
                    if (ar[yy] == k)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        GtkStyleContext *context = gtk_widget_get_style_context(label);
                        gtk_style_context_add_class(context, "red-label");
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                    else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                }
            }
            if (k == totalseat)
            {
                break;
            }
            if (k == totalseat - 1)
            {
                for (int yy = 0; yy < qr; yy++)
                {
                    if (ar[yy] == k)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        GtkStyleContext *context = gtk_widget_get_style_context(label);
                        gtk_style_context_add_class(context, "red-label");
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                    else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                }
            }
            k++;
            p++;
        }
    }
    else
    {
        totalseat = totalseat - 1;
        while (1)
        {
            if ((totalseat - q) % 4 == 0)
            {
                col = (totalseat - q) / row;
                break;
            }
            q++;
        }
        q++;
        if (q % 2 != 0)
        {
            for (int i = q - 1; i > 0; i--)
            {
                for (int yy = 0; yy < qr; yy++)
                {
                    if (ar[yy] == k)
                    {
                        char button_label[10];
                        sprintf(button_label, "0%d ", k);
                        label = gtk_label_new(button_label);
                        GtkStyleContext *context = gtk_widget_get_style_context(label);
                        gtk_style_context_add_class(context, "red-label");
                        gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                        break;
                    }
                    else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                    {
                        char button_label[10];
                        sprintf(button_label, "0%d ", k);
                        label = gtk_label_new(button_label);
                        gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                        break;
                    }
                }
                k++;
                v++;
            }
        }
        if (q % 2 == 0)
        {
            for (int i = q - 1; i > 0; i--)
            {
                if (i == 1)
                {
                    for (int yy = 0; yy < qr; yy++)
                    {
                        if (ar[yy] == k)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            GtkStyleContext *context = gtk_widget_get_style_context(label);
                            gtk_style_context_add_class(context, "red-label");
                            gtk_grid_attach(GTK_GRID(grid), label, 5 - 3, 0, 1, 1);
                            break;
                        }
                        else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            gtk_grid_attach(GTK_GRID(grid), label, 5 - 3, 0, 1, 1);
                            break;
                        }
                    }
                    k++;
                }
                else
                {
                    for (int yy = 0; yy < qr; yy++)
                    {
                        if (ar[yy] == k)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            GtkStyleContext *context = gtk_widget_get_style_context(label);
                            gtk_style_context_add_class(context, "red-label");
                            gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                            break;
                        }
                        else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            gtk_grid_attach(GTK_GRID(grid), label, 5 - v, 0, 1, 1);
                            break;
                        }
                    }
                    k++;
                    v++;
                }
            }
        }

        for (int i = col; i > 0; i--)
        {
            y = 1;
            te = 0;
            for (int j = row; j > 0; j--)
            {
                if (te == 2)
                {
                    y = j + 2;
                }
                if (k < 10)
                {
                    for (int yy = 0; yy < qr; yy++)
                    {
                        if (ar[yy] == k)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            GtkStyleContext *context = gtk_widget_get_style_context(label);
                            gtk_style_context_add_class(context, "red-label");
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                        else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                        {
                            char button_label[10];
                            sprintf(button_label, "0%d ", k);
                            label = gtk_label_new(button_label);
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                    }
                    k++;
                }
                else
                {
                    for (int yy = 0; yy < qr; yy++)
                    {
                        if (ar[yy] == k)
                        {
                            char button_label[10];
                            sprintf(button_label, "%d ", k);
                            label = gtk_label_new(button_label);
                            GtkStyleContext *context = gtk_widget_get_style_context(label);
                            gtk_style_context_add_class(context, "red-label");
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                        else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                        {
                            char button_label[10];
                            sprintf(button_label, "%d ", k);
                            label = gtk_label_new(button_label);
                            gtk_grid_attach(GTK_GRID(grid), label, y, col - i + 1, 1, 1);
                            break;
                        }
                    }
                    k++;
                }
                if (k == totalseat + 1 - 4)
                {
                    break;
                }
                te++;
                y++;
            }
            if (k == totalseat + 1 - 4)
            {
                break;
            }
        }
        int p = 1;
        totalseat = tems;
        while (1)
        {
            if (k != totalseat - 1)
            {
                for (int yy = 0; yy < qr; yy++)
                {
                    if (ar[yy] == k)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        GtkStyleContext *context = gtk_widget_get_style_context(label);
                        gtk_style_context_add_class(context, "red-label");
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                    else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                }
            }
            if (k == totalseat)
            {
                break;
            }
            if (k == totalseat - 1)
            {
                for (int yy = 0; yy < qr; yy++)
                {
                    if (ar[yy] == k)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        GtkStyleContext *context = gtk_widget_get_style_context(label);
                        gtk_style_context_add_class(context, "red-label");
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                    else if (ar[yy] != k && chkarr(ar, k, tems) == 0)
                    {
                        char button_label[10];
                        sprintf(button_label, "%d ", k);
                        label = gtk_label_new(button_label);
                        gtk_grid_attach(GTK_GRID(grid), label, p, col + 1, 1, 1);
                        break;
                    }
                }
            }
            k++;
            p++;
        }
    }
    cssProvider = gtk_css_provider_new();
    GError *error = NULL;
    gtk_css_provider_load_from_data(cssProvider, ".red-label { color: red; }", -1, &error);
    if (error != NULL)
    {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_widget_show_all(window);
}

void returnNumberTicket(GtkWidget *button, gpointer data)
{
    GtkWidget *busTicketNumber = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "bus_ticket_number"));
    GtkWidget *usernamedetail = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "usernamedetail"));
    GtkWidget *userphnumber = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "userphnumber"));

    GtkWidget *message = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "message"));

    const gchar *ticket = gtk_entry_get_text(GTK_ENTRY(busTicketNumber));
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(usernamedetail));
    const gchar *userph = gtk_entry_get_text(GTK_ENTRY(userphnumber));

    if (strcmp(ticket, "") == 0 || strcmp(username, "") == 0 || strcmp(userph, "") == 0)
    {
        gtk_label_set_text(GTK_LABEL(message), "PLEASE ENETERED ALL THE REQUIRED INFORMATIONS");
    }
    else
    {
        int busTicketNum;
        int len = strlen(username);
        char passengerName[len];
        len = strlen(userph);
        char passengerPhoneNumber[len];
        busTicketNum = atoi(ticket);
        strcpy(passengerName, username);
        strcpy(passengerPhoneNumber, userph);
        char BSL[] = ".files/BusSeatLicense", chkli[500];
        int totalSeat;
        FILE *chk = fopen(BSL, "r");
        while (fscanf(chk, "%d %s ", &totalSeat, chkli) == 2)
        {
            if (strcmp(lid, chkli) == 0)
            {
                break;
            }
        }
        fclose(chk);
        if (strcmp(lid, chkli) == 0)
        {
            gtk_label_set_text(GTK_LABEL(message),"SUCCESS!");
        }
    }
}