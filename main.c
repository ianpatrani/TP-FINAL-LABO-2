#include "cellLib.h"

int main()
{
    int admin = 0;
    int idUser = start();
    if(idUser >= 0)
    {
        admin = validAdmin(idUser);
        if (admin == 1)
        {
            adminMenu(idUser);
        }
        else
            userMenu(idUser);
    }
//    showUserFile();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    return 0;
}

