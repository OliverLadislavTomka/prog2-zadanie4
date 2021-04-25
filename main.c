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

}

Unit vytvorEnemy(){
    Unit enemy;
    UnitType* enemyType = NULL;


}

void generovanieEnemy(int pocet,Unit enemy[]){
    for(int i = 0; i < pocet; i++){
        enemy[i]=vytvorEnemy();
    }
}



int gamecycle(int argc,char* argv[]){
    Unit zviera= generovanieMonstra(zviera,argv);
    if (zviera.type == NULL) return 1;
    printf("%s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n", zviera.type->name, zviera.type->att, zviera.type->def, zviera.hp,zviera.level);
    int pocetNepriatelov=atoi(argv[2]);
    Unit enemy[pocetNepriatelov];
    generovanieEnemy(atoi(argv[2]),enemy);
    return 0;
}

int main(int argc, char *argv[]) {
    int c=0;
    if (c == 0) c=gamecycle(argc,argv);
    return c;
}