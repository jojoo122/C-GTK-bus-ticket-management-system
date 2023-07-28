void reset_main(char *);
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
    FILE *create = fopen(file,"a");
    fclose(create);

    FILE *reset = fopen(file, "r");
    if (fscanf(reset, "%d %d %d %d %d", &scyear, &scmonth, &scday, &schour, &scmin) == 5)
    {
        if((year - scyear) >= 1 || (month - scmonth) >= 1)
        {
            reset_main(LID);
            FILE *open = fopen(file, "w");
            fprintf(open,"%d %d %d %d %d",year,month,day,hour,minute); 
            fclose(open);  
        }
        else if((day - scday) == 1 && (hour - schour) <= 0 && (minute - scmin) >= 0)
        {
            reset_main(LID);
            FILE *open = fopen(file, "w");
            fprintf(open,"%d %d %d %d %d",year,month,day,hour,minute);
            fclose(open);
        }
        else if((day - scday) >= 2)
        {
            reset_main(LID);
            FILE *open = fopen(file, "w");
            fprintf(open,"%d %d %d %d %d",year,month,day,hour,minute);
            fclose(open);
        }
    }
    else if (fscanf(reset, "%d %d %d %d %d", &scyear, &scmonth, &scday, &schour, &scmin) != 5)
    {
        FILE *open = fopen(file, "w");
        fprintf(open,"%d %d %d %d %d",year,month,day,hour,minute);
        fclose(open);
    }
    fclose(reset);
}

void reset_main(char licenseID[])
{
    char boBus[1000],unboBus[1000],usrinfo[1000],usrph[1000],li[500];
    int totalSeat;
    sprintf(boBus,".files/Booked-%s",licenseID);
    sprintf(unboBus,".files/UnBooked-%s",licenseID);
    sprintf(usrinfo,".files/UserInfo-%s",licenseID);
    sprintf(usrph,".files/UserInfoPhone-%s",licenseID);
    FILE *tose = fopen(".files/BusSeatLicense","r");
    while(fscanf(tose,"%d %s ",&totalSeat,li) == 2)
    {
        if(strcmp(li,licenseID) == 0)
        {
            break;
        }
    }
    FILE *booked,*unBooked,*userInfo,*userPhone;
    booked = fopen(boBus,"w");
    unBooked = fopen(unboBus,"w");
    userInfo = fopen(usrinfo,"w");
    userPhone = fopen(usrph,"w");
    for(int i = 1; i <= totalSeat; i++)
    {
        fprintf(unBooked,"%d ",i);
    }
    fclose(booked);
    fclose(unBooked);
    fclose(userInfo);
    fclose(userPhone);
    fclose(tose);
}