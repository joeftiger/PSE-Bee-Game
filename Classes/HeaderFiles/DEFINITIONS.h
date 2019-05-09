#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

/**
 * list of important definitions that are re-used often and can be simply changed from here
 */

/* Priorities */
#define HUD_PRIORITY 10

#define TILE_MAP_LAYER_NAME "TileMapLayer"

#define MAP_SCALE_SD 0.5f
#define MAP_SCALE_HD 0.5f

#define TREE_SCALE_HD (2.0f / 3)
#define TREE_SCALE_SD (MAP_SCALE_SD * TREE_SCALE_HD)

#define UPDATE_TIME 0.01f

#define TEXT_SIZE_HUD 20
#define FONT "fonts/ReemKufi-Regular.ttf"

#define USE_SD true

/* Time */
#define LENGTH_MONTH 1 //in minutes
#define LENGTH_YEAR 12 //in months
#endif // __DEFINITIONS_H__