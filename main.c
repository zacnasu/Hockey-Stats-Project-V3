#include <stdio.h>

//global variables to hold the overall and period totals as they are otherwise held in separate instances according to gameplay type
int totalSOGF = 0;
int totalSOGA = 0;
int totalMSF = 0;
int totalMSA = 0;
int totalOF = 0;
int totalOA = 0;
int perSOGF[5] = {0,0,0,0,0};
int perSOGA[5] = {0,0,0,0,0};
int perMSF[5] = {0,0,0,0,0};
int perMSA[5] = {0,0,0,0,0};
int perOF[5] = {0,0,0,0,0};
int perOA[5] = {0,0,0,0,0};

//meant hold a gametype; even strength, penalty kill, powerplay
typedef struct playerStats{
    int SOGF;
    int MSF;
    int OF;
    int SOGA;
    int MSA;
    int OA;
    int shifts;
}playerStats;

//checks if a player was on the previous line as well because line changes are not symmetric
int checkShift(int LastShift[], int number){
    for(int i = 0; i<5; i++){
        if(LastShift[i] == number){
            return 1;
        }
    }
    return 0;
}
//checks if line is valid by seeing if a value was missing and threw the reader onto a different line
int checkValid(int SOGF,int MSF, int OF, int SOGA,int MSA , int OA){
    if(SOGF > 8 || MSF > 8 || OF > 8 || SOGA > 8 || MSA > 8 || OA > 8){
        return 2;
    }
    return 0;
}

//scans a gameplay type file (es,pk,pp) and prints out a file for each game type
playerStats * scanSection(char link[],playerStats data[], int type){

    int localSOGF= 0;
    int localMSF=0;
    int localSOGA=0;
    int localOF=0;
    int localMSA=0;
    int localOA=0;

    FILE* input_file = fopen(link, "r");
    int SOGF, MSF,SOGA, OF, MSA, OA, p1, p2, p3, p4, p5 = 0;
    if(input_file == NULL){
        printf("%d",type);
    }
    //array that holds order that players appear in. Meant to count shifts without repeat
    int PlayersOn[200][5];
    for(int i = 0 ; i<200; i++){
        for(int j = 0; j<5; j++){
            PlayersOn[i][j] = 99;
        }
    }
    int line = 0;
    int per = 0;
    while( fscanf(input_file, "%d %d %d %d %d %d %d %d %d %d %d", &p1, &p2, &p3, &p4, &p5, &SOGF, &MSF, &OF, &SOGA , &MSA, &OA)==11 ){
        line++;
        if((p1 + p2 + p3 + p4 + p5) == 0){
            per++;
        }
        perSOGF[per] += SOGF;
        perMSF[per] += MSF;
        perOF[per] += OF;
        perSOGA[per] += SOGA;
        perMSA[per] += MSA;
        perOA[per] += OA;
        PlayersOn[line][0] = p1;
        PlayersOn[line][1] = p2;
        PlayersOn[line][2] = p3;
        PlayersOn[line][3] = p4;
        PlayersOn[line][4] = p5;
        //checks if any of the players were also on the previous line so we don't double count shifts
        if(line!=0) {
            if (checkShift(PlayersOn[line - 1], p1) != 1) {
                data[p1].shifts++;
            }
            if (checkShift(PlayersOn[line - 1], p2) != 1) {
                data[p2].shifts++;
            }
            if (checkShift(PlayersOn[line - 1], p3) != 1) {
                data[p3].shifts++;
            }
            if (checkShift(PlayersOn[line - 1], p4) != 1) {
                data[p4].shifts++;
            }
            if (checkShift(PlayersOn[line - 1], p5) != 1) {
                data[p5].shifts++;
            }
        }
        //checks if players were both put on the same line as we want to avoid double counting stats on a single player
        if(p2!=1&&p2!= 0) {
            if (p1 == p2 | p1 == p3 | p1 == p4 | p1 == p5 | p2 == p3 | p2 == p4 | p2 == p5 | p3 == p4 | p3 == p5 |
                p4 == p5) {
                printf("%d %d\n", line, type);
            }
        }
        //meant to check for missing values as they end up bleeding onto different lines as they are read in
        if(checkValid(SOGF,MSF, OF,SOGA,MSA,OA) == 2){
            printf("%d %d\n", line,type);
        }
        totalSOGF += SOGF;
        totalMSF += MSF;
        totalOF += OF;
        totalSOGA += SOGA;
        totalOA += OA;
        totalMSA += MSA;
    
        localSOGF += SOGF;
        localMSF += MSF;
        localOF += OF;
        localSOGA += SOGA;
        localOA += OA;
        localMSA += MSA;


        data[p1].SOGF += SOGF;
        data[p1].MSF += MSF;
        data[p1].OF += OF;
        data[p1].SOGA += SOGA;
        data[p1].MSA += MSA;
        data[p1].OA += OA;

        data[p2].SOGF += SOGF;
        data[p2].MSF += MSF;
        data[p2].OF += OF;
        data[p2].SOGA += SOGA;
        data[p2].MSA += MSA;
        data[p2].OA += OA;

        data[p3].SOGF += SOGF;
        data[p3].MSF += MSF;
        data[p3].OF += OF;
        data[p3].SOGA += SOGA;
        data[p3].MSA += MSA;
        data[p3].OA += OA;

        data[p4].SOGF += SOGF;
        data[p4].MSF += MSF;
        data[p4].OF += OF;
        data[p4].SOGA += SOGA;
        data[p4].MSA += MSA;
        data[p4].OA += OA;

        data[p5].SOGF += SOGF;
        data[p5].MSF += MSF;
        data[p5].OF += OF;
        data[p5].SOGA += SOGA;
        data[p4].MSA += MSA;
        data[p5].OA += OA;
    }
    fclose(input_file);
    if(type != 1){
        if(type == 2){
            printf("PowerPlay: SOGF: %d, MSF: %d SOF: %d\n", localSOGF,localMSF, localOF);
        }else if(type == 3){
            printf("Penalty Kill: SOGA: %d, MSA: %d SOA: %d\n", localSOGA,localMSA, localOA);
        }
    }

    return data;
}
//writes output of even strength statistics to file in latex table format
void outputESstats(playerStats data[], char outputFile[]){

    FILE* output = fopen( outputFile, "w");

    fprintf(output,"Team & %.1f\\%% & %.1f\\%% & & & & &\\\\\n\\hline\n",(100.0)*(totalSOGF+totalMSF)/(totalSOGA+totalSOGF+totalMSA+totalMSF), (100.0)*(totalOF)/(totalOF+totalOA));

    for(int i = 2; i < 100; i++){
        if(data[i].shifts > 0) {
            fprintf(output, "%d & %.1f\\%% & %.1f\\%% & %.2f & %.2f & %.2f & %.2f & %d\\\\\n\\hline\n", i, ((100.0)*(data[i].SOGF+data[i].MSF)/ ((data[i].SOGA+ data[i].MSF) + data[i].SOGF+data[i].MSA)),
                    (100.0*(data[i].OF)/(data[i].OF + data[i].OA)) , (1.0)*data[i].SOGF/data[i].shifts, (1.0)*data[i].OF/data[i].shifts,(1.0)*data[i].SOGA/data[i].shifts,(1.0)*data[i].OA/data[i].shifts,data[i].shifts);
        }
        //Number, Corsi, Opportunities For %, SOGF/Shift, OF/shift, SOGA/shift, OA/shift/, num shifts
    }
    fclose(output);
}
//writes output of powerplay statistics to file in latex table format
void outputPPstats(playerStats data[], char outputFile[]){
    FILE* output = fopen( outputFile, "w");

    for(int i = 2; i < 100; i++){
        if(data[i].shifts > 0){
            fprintf(output,"%d & %.1f & %.1f & %d\\\\\n\\hline\n", i, (1.0)*data[i].OF/data[i].shifts,(1.0)*data[i].SOGF/data[i].shifts, data[i].shifts);
        }
    }
    fclose(output);
}

//writes output of penalty kill statistics to file in latex table format
void outputPKstats(playerStats data[], char outputFile[]){
    FILE* output = fopen( outputFile, "w");

    for(int i = 2; i < 100; i++){
        if(data[i].shifts > 0){
            fprintf(output,"%d & %.1f & %.1f & %d\\\\\n\\hline\n", i, (1.0)*data[i].OA/data[i].shifts,(1.0)*data[i].SOGA/data[i].shifts, data[i].shifts);
        }
    }
    fclose(output);
}

int main() {
    playerStats Data1[100];
    playerStats Data2[100];
    playerStats Data3[100];

    //intializes all values in each of the three game type structures to zero
    for(int i = 0; i < 100; i++){
        Data1[i].MSA = 0;
        Data1[i].MSF = 0;
        Data2[i].MSA = 0;
        Data2[i].MSF = 0;
        Data1[i].SOGF = 0;
        Data1[i].OA = 0;
        Data1[i].OF = 0;
        Data1[i].SOGA = 0;
        Data1[i].shifts = 0;
        Data2[i].SOGF = 0;
        Data2[i].OA = 0;
        Data2[i].OF = 0;
        Data2[i].SOGA = 0;
        Data2[i].shifts = 0;
        Data3[i].MSA = 0;
        Data3[i].MSF = 0;
        Data3[i].SOGF = 0;
        Data3[i].OA = 0;
        Data3[i].OF = 0;
        Data3[i].SOGA = 0;
        Data3[i].shifts = 0;
    }

    //names of input and output files, to be changed when game changes. Typed and changed here as file is optimized for IDE and is run often during a game to check current stats
    char* ESOGFILE = "Mar04ES.txt";
    char *PKFILE = "Mar04PK.txt";
    char *PPFILE = "Mar04PP.txt";
    char ESOUTFILE[] = "Mar04ES.table.txt";
    char PKOUTFILE[] = "Mar04PK.table.txt";
    char PPOUTFILE[] = "Mar04PP.table.txt";
    char Opponent[] = "Panthers";

    //three different objects for each type of gameplay; even strength, penalty kill, powerplay
    playerStats* ESData = scanSection(ESOGFILE, Data1, 1);
    playerStats* PKData = scanSection(PKFILE, Data2, 3);
    playerStats* PPData = scanSection(PPFILE, Data3, 2);

    //writes output into three separate files according to gameplay type
    outputESstats(ESData, ESOUTFILE);
    outputPPstats(PPData, PPOUTFILE);
    outputPKstats(PKData, PKOUTFILE);
/* To debug and find errors in input if need be*/
    /*
 
    for(int i = 1; i< 100; i++){
        if(ESData[i].shifts>0){
            printf("%d %d %d %d %d %d %d\n",i, ESData[i].SOGF,ESData[i].MSF, ESData[i].OF, ESData[i].SOGA, ESData[i].MSA, ESData[i].OA);
        }
    }
*/
    //Prints out shots on goal in latex table format
    printf("SOG:\nWolves & %d & %d & %d & %d & %d & %d\\\\\n\\hline\n%s & %d & %d & %d & %d & %d & %d\\\\\n\\hline\n", perSOGF[0],perSOGF[1],perSOGF[2],perSOGF[3], perSOGF[4]  ,perSOGF[0]+perSOGF[1]+perSOGF[2]+perSOGF[3]+perSOGF[4], Opponent ,perSOGA[0],perSOGA[1],perSOGA[2],perSOGA[3],perSOGA[4], perSOGA[0]+perSOGA[1]+perSOGA[2]+perSOGA[3]+perSOGA[4]);
    //Prints out missed shots in latex table format
    printf("Missed:\nWolves & %d & %d & %d & %d & %d & %d\\\\\n\\hline\n%s & %d & %d & %d & %d & %d & %d\\\\\n\\hline\n", perMSF[0],perMSF[1],perMSF[2],perMSF[3],perMSF[4],perMSF[0]+perMSF[1]+perMSF[2]+perMSF[3]+perMSF[4], Opponent ,perMSA[0],perMSA[1],perMSA[2],perMSA[3],perMSA[4],perMSA[0]+perMSA[1]+perMSA[2]+perMSA[3]+perMSF[4]);
    //prints out scoring opportunity in latex table format
    printf("Scoring Opps:\nWolves & %d & %d & %d & %d & %d & %d\\\\\n\\hline\n%s & %d & %d & %d & %d & %d & %d\\\\\n\\hline\n", perOF[0],perOF[1],perOF[2],perOF[3],perOF[4],perOF[0]+perOF[1]+perOF[2]+perOF[3]+perOF[4], Opponent ,perOA[0],perOA[1],perOA[2],perOA[3],perOA[4],perOA[0]+perOA[1]+perOA[2]+perOA[3]+perOA[4]);


    return 0;
}
