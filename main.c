#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: miesto pre pripojenie externej funkcionality z ostatnych
//  suborov projektu.

#include "data.h"
#include "rng.h"

// TODO: miesto pre implementaciu vasich vlastnych funkcii, datovych
//  typov a vlastne makra.

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
    for(int i = 0; i < pocet; i++){
        enemy[i]=vytvorEnemy();
    }
}

int zivot(Unit enemy[],int pocetNepriatelov){
    int c=0;
    for(int i=0;i<pocetNepriatelov;i++) if (enemy[i].hp > 0) c++;
    return c;
}

void vypisJednotiek(Unit zviera,Unit enemy[],int pocetNepriatelov){
    printf("%s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n", zviera.type->name, zviera.type->att, zviera.type->def, zviera.hp,zviera.level);
    for(int i=0;i<pocetNepriatelov;i++) printf("[%d] %s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n",i,enemy[i].type->name,enemy[i].type->att,enemy[i].type->def,enemy[i].hp,enemy[i].level);
}

void utokVypis(Unit zviera,Unit enemy[],int pocetNepriatelov){

}

void boj(Unit zviera,Unit enemy[],int pocetNepriatelov){
    while(zivot(enemy,pocetNepriatelov) && zviera.hp>0){
        vypisJednotiek(zviera,enemy,pocetNepriatelov);
        utokVypis(zviera,enemy,pocetNepriatelov);
    }
}


int gamecycle(int argc,char* argv[]){
    Unit zviera= generovanieMonstra(zviera,argv);
    if (zviera.type == NULL) return 1;
    int pocetNepriatelov=atoi(argv[2]);
    Unit enemy[pocetNepriatelov];
    generovanieEnemy(pocetNepriatelov,enemy);
    boj(zviera,enemy,pocetNepriatelov);
    return 0;
}

int main(int argc, char *argv[]) {
    srnd(atoi(argv[3]));
    int c=0;
    if (c == 0) c=gamecycle(argc,argv);
    return c;
}