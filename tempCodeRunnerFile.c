void showAnUser(stUser toShow)
{
    stWord auxPass;
    printf("__________________________________\n");
    printf("%s", toShow.fullName);
    printf("\t\tID:%d\n", toShow.idUser);
    if (toShow.off == 1)
    {
        printf("\t*DADO DE BAJA*\n");
    }
    printf("__________________________________\n");
    printf("Anio de nacimiento:\t%d\n", toShow.birthYear);
    printf("Pais: \t\t\t%s\n", toShow.country);
    if (toShow.gender == 'm' || 'M')
    {
        printf("Genero: \t\tMASCULINO\n");
    }
    else
    {
        printf("Genero: \t\tFEMENINO\n");
    }
    printf("Password: \t\t");
    showPassword(toShow);

    printf("Total de cacnciones escuchadas: \t%d \n\n", toShow.totalSongsPlayed);
}