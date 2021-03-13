#pragma once

#include <iostream>
#include "Vector.h"

/* defines useful constants used throughout the project */


/* Material constants */
const Vector	DEF_COLOR(.3f, .8f, .3f);

const float 	DEF_REFL	= .00f;
const float	DEF_REFR	= .00f;
const float	DEF_DIFF	= .3f;
const float	DEF_SPEC	= .3f;
const float	DEF_AMB 	= .8f;
const float	DEF_EXP 	= 100.0f;
const float 	DEF_ETA 	= 1.0f;

/* Light constants */
const Vector	DEF_LIGHT_COL(1.0f, 1.0f, 1.0f);

/* Renderer constants */
const Vector	BCK_COLOR(.2f, .2f, .2f);
const int 	MAX_RECURSION_DEPTH	= 7;
const float 	DELTA		= .0001f;
const float	ZERO_TOLL	= .00001f;

/* PPM save/read constants */

const int 	WIDTH 		= 500;
const int 	HEIGHT 		= 500;
