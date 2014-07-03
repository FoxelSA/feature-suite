/*
 * feature suite - Feature detection suite
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Nils Hamel <n.hamel@foxel.ch>
 *
 *
 * This file is part of the FOXEL project <http://foxel.ch>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Additional Terms:
 *
 *      You are required to preserve legal notices and author attributions in
 *      that material or in the Appropriate Legal Notices displayed by works
 *      containing it.
 *
 *      You are required to attribute the work as explained in the "Usage and
 *      Attribution" section of <http://foxel.ch/license>.
 */


/* 
    Header - Include guard
 */

    # ifndef __FEATURE_IMAGE_DECENT__
    # define __FEATURE_IMAGE_DECENT__

/* 
    Header - Includes
 */

    # include <iostream>
    # include <vector>
    # include <cmath>
    # include <opencv2/opencv.hpp>
    # include <opencv2/highgui/highgui_c.h>
    # include "common-stdap.hpp"

/* 
    Header - Preprocessor definitions
 */

    /* Define entropic sampling rectangle */
    # define FS_SAMPLE_X 4
    # define FS_SAMPLE_Y 4
    # define FS_SAMPLE_C ( ( FS_SAMPLE_X + 1 ) * ( FS_SAMPLE_X + 1 ) )

/* 
    Header - Preprocessor macros
 */

    /* Min and max macro */
    # define FS_MIN(x,y) ( ( ( x ) < ( y ) ) ? ( x ) : ( y ) )
    # define FS_MAX(x,y) ( ( ( x ) > ( y ) ) ? ( x ) : ( y ) )

/* 
    Header - Typedefs
 */

/* 
    Header - Structures
 */

/* 
    Header - Function prototypes
 */

    float fs_imagedecent_shannon( float fsAccum[], int fsStack );

/*
    Header - Include guard
 */

    # endif


