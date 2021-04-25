#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "rng.h"

typedef struct{
    int dmgZviera;
    int dmgEnemy;
}Dmg;

UnitType* findMonsterInDataset(UnitType *poleMonstier, char **argv){
    for (int i=0;i < MONSTER_TYPE_COUNT;i++){
        if (!strcmp(argv[1],poleMonstier[i].name)){
            return &poleMonstier[i];
        }
    }
    return NULL;
}

Unit generovanieMonstra(Unit zviera,char *argv[]){
    UnitType* monster=NULL;
    zviera.hp=MONSTER_INITIAL_HP;
    zviera.level=0;
    monster = findMonsterInDataset(monster_types, argv);
    zviera.type = monster;
    return zviera;
}

UnitType* findEnemy(UnitType *poleEnemy){
    return &poleEnemy[rnd(0,ENEMY_TYPE_COUNT - 1)];
}

Unit vytvorEnemy(){
    Unit enemy;
    UnitType* enemyType = findEnemy(enemy_types);
    enemy.type = enemyType;
    enemy.hp=rnd(ENEMY_MIN_INIT_HP,ENEMY_MAX_INIT_HP);
    enemy.level=rnd(0,UNIT_MAX_LEVEL);
    return enemy;
}

void generovanieEnemy(int pocet,Unit enemy[]){
    for(int i = 0; i < pocet; i++)
        enemy[i]=vytvorEnemy();
}

int zivot(Unit enemy[],int pocetNepriatelov){
    int c=0;
    for(int i=0;i<pocetNepriatelov;i++)
        if (enemy[i].hp > 0)
            c++;
    return c;
}

void vypisJednotiek(Unit *zviera,Unit enemy[],int pocetNepriatelov){
    printf("%s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n", zviera->type->name, zviera->type->att, zviera->type->def, zviera->hp,zviera->level);
    for(int i=0;i<pocetNepriatelov;i++) printf("[%d] %s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n",i,enemy[i].type->name,enemy[i].type->att,enemy[i].type->def,enemy[i].hp,enemy[i].level);
}

int vypocetDMG(Unit *utocnik,Unit *obranca){
    return (((30+utocnik->level - obranca->level)*(100+rnd(1,utocnik->hp) + utocnik->type->att))/(100+rnd(1,obranca->hp)+obranca->type->def));
}

void utokMonstra(Unit *zviera, Unit enemy[], int pocetNepriatelov, Dmg *vitaz){
    int najmensieHP=ENEMY_MAX_INIT_HP,indexNajmensichHP=0;
    for(int i=0;i<pocetNepriatelov;i++)
        if (enemy[i].hp <najmensieHP && enemy[i].hp > 0){
            najmensieHP = enemy[i].hp;
            indexNajmensichHP =i;
        }
    int dmg=vypocetDMG(zviera,&enemy[indexNajmensichHP]);
    printf("\n%s => %d => [%d] %s\n",zviera->type->name,dmg,indexNajmensichHP,enemy[indexNajmensichHP].type->name);
    enemy[indexNajmensichHP].hp -= dmg;
    vitaz->dmgZviera += dmg;
}


void utokEnemy(Unit *zviera, Unit enemy[], int pocetNepriatelov, Dmg *vitaz){
    for(int i = 0; i < pocetNepriatelov; i++){
        if (enemy[i].hp > 0 && zviera->hp > 0){
            int dmg=vypocetDMG(&enemy[i],zviera);
            printf("[%d] %s => %d => %s\n",i,enemy[i].type->name,dmg,zviera->type->name);
            zviera->hp -= dmg;
            vitaz->dmgEnemy+= dmg;
        }
    }
    printf("\n");
}

void utokVypis(Unit *zviera, Unit enemy[], int pocetNepriatelov, Dmg* vitaz){
    utokMonstra(zviera,enemy,pocetNepriatelov,vitaz);
    utokEnemy(zviera,enemy,pocetNepriatelov,vitaz);
}

void vypisVitaza(Unit* zviera, Dmg* vitaz){
    if (zviera->hp > 0) printf("\nWinner: %s\n",zviera->type->name);
    if (zviera->hp <= 0) printf("\nWinner: Enemy\n");
    printf("Total monster DMG: %d\nTotal enemies DMG: %d\n",vitaz->dmgZviera,vitaz->dmgEnemy);
}

void boj(Unit* zviera, Unit enemy[], int pocetNepriatelov, Dmg* vitaz){
    while(zivot(enemy,pocetNepriatelov) && zviera->hp>0){
        vypisJednotiek(zviera,enemy,pocetNepriatelov);
        utokVypis(zviera,enemy,pocetNepriatelov,vitaz);
        if(zviera->level < 10 && zviera->hp > 0) zviera->level++;
    }
    vypisJednotiek(zviera,enemy,pocetNepriatelov);
    vypisVitaza(zviera,vitaz);
}

int nahrada(){

    FILE *fptr;

    return 0;
}

int gamecycle(int argc,char* argv[]){
    int subor=0;
    if (argc == 6) subor = nahrada();
    if (subor != 0) return subor;
    Dmg *vitazPTR,vitaz={0, 0};
    vitazPTR = &vitaz;
    Unit *zvieraPTR,zviera= {};
    zviera=generovanieMonstra(zviera,argv);
    zvieraPTR = &zviera;
    if (zviera.type == NULL) return 1;
    int pocetNepriatelov=strtol(argv[2],NULL,0);
    Unit enemy[pocetNepriatelov];
    generovanieEnemy(pocetNepriatelov,enemy);
    boj(zvieraPTR,enemy,pocetNepriatelov,vitazPTR);
    return 0;
}

int main(int argc, char *argv[]) {
    srnd(strtol(argv[3],NULL,0));
    int c=0;
    if (c == 0) c=gamecycle(argc,argv);
    return c;
}