#ifndef __GLOBAL_H__
#define __GLOBAL_H__


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//player & enemy

//ID
 extern int G_BULLET_PLAYER_ID;
 extern int G_BULLET_ENEMY_ID;

 extern float G_ENEMY_TYPE;

 extern int G_ITEM_UPGRADE_BULLET;
 extern int G_ITEM_ARMOR;
 extern int G_ITEM_BOOM;

const static int G_MOVE_STRAINGH = 0;
const static int G_MOVE_CIRCLE_LEFT = 1;
const static int G_MOVE_CIRCLE_RIGHT = 2;

//////////////////////////////////////////////////////////////////////////

//Variant
 extern float G_DESIGN_WIDTH;
 extern float G_DESIGN_HEIGHT;
 extern float G_SCALE_FACTOR;

 extern int G_PLAYER_HP;
 extern int G_PLAYER_DAMAGE;
 extern int G_MIN_PLAYER_BULLET_LEVEL;
 extern int G_MAX_PLAYER_BULLET_LEVEL;

 extern float G_TIMEOUT_BULLET_LEVEL;

 extern float G_ITEM_BULLET_RANDOM_PERCENT;
 extern float G_ITEM_ARMOR_RANDOM_PERCENT;
 extern float G_ITEM_BOOM_RANDOM_PERCENT;


 extern int G_MAX_PLAYER_BOOM;

 extern int G_MIN_ENEMY_HP;
 extern int G_MIN_ENEMY_DAM;
 extern float G_PLAYER_ARMOR_TIME;
 extern float G_PLAYER_BULLET_VY;

 extern float G_PLAYER_TIME_TO_FIRE;
 extern float G_ENEMY_TIME_TO_FIRE;

 extern float G_DEFAULT_TIME_TO_GENERATE_ENEMY;

 extern float G_MIN_ENEMY_VY;
 extern float G_MAX_ENEMY_VY;

 extern float G_MIN_ENEMY_TIME;
 extern float G_MAX_ENEMY_TIME;

 extern float G_MIN_ENEMY_BULLET_VY;
 extern float G_BULLET_VY_FROM_ENEMY; //bulletVy =  BULLET_VY_FROM_ENEMY * enemyVy

 extern float G_DEFAULT_DIFFICULTY;

 extern float G_VELOCITY_IN_DIFFICULTY;		//velocity = diff / G_VELOCITY_IN_DIFFICULTY
 extern float G_HP_IN_DIFFICULTY;			//hp = diff / G_HP_IN_DIFFICULTY
 extern float G_DAMAGE_IN_DIFFICULTY;		//damage = diff / G_DAMAGE_IN_DIFFICULTY



#endif //__GLOBAL_H__
