#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

/**
 * list of important definitions that are re-used often and can be simply changed from here
 */

/* Priorities */
#define HUD_PRIORITY 10

#define TILE_MAP_LAYER_NAME "TileMapLayer"

#define MAP_SCALE_HD 0.75f
#define MAP_SCALE_SD (MAP_SCALE_HD * 2)

#define TREE_SCALE_HD (MAP_SCALE_HD * 4.0f / 3)
#define TREE_SCALE_SD (TREE_SCALE_HD)   // Apparently, if you switch to MAP_SCALE_SD, it also affects the TREE_SCALE in general

#define UPDATE_TIME 0.01f

#define TEXT_SIZE_HUD 20
#define FONT "fonts/ReemKufi-Regular.ttf"

/* Time */
#define LENGTH_MONTH 1 //in minutes
#define LENGTH_YEAR 12 //in months
#endif // __DEFINITIONS_H__