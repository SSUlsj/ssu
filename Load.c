void Save_Ranking()
{
        int i=0;
        FILE * rank = fopen("ranking.txt", "w");
        for (i; i<5; i++) {
                fprintf(rank, "map %d %d\n", i+1, cnt);
        }
        fclose(rank);
        return;
}

void Load_Ranking()
{
        int i=0, j=0;
        int stage_num;
        FILE *rank = fopen("ranking.txt", "rt");
        for(i; i<5;i++) {
                fscanf(rank, "map %d %d\n", &stage_num, &cnt);
                for (j; j<5;j++) {
                        fscanf(rank, "%s\n", &username);
                }
                fprintf(rank, "map %d %d %s", stage_num, cnt, username);
        }
        fclose(rank);
        return;
}

