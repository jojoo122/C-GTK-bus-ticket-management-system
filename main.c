#include "include/header.h"
#include "include/loginAdminCheck.h"
#include "include/loginAdmin.h"
#include "include/loginUserCheck.h"
#include "include/loginUser.h"
#include "include/registeradmin.h"
#include "include/firstlanding.h"
#include "include/landing.h"
int main(int argc, char **argv)
{
    oslist();
    gtk_init(&argc, &argv);
    g_object_set (gtk_settings_get_default (), "gtk-application-prefer-dark-theme", TRUE, NULL);
    if(osname == 3 || osname == 1)
    {
    if (fopen(".files/adminlist", "r") == NULL)
    {
        firstlanding();
    }
    else
    {
        landing();
    }
    }
    gtk_main();
    return 0;
}
