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
    if(osname == 3)
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