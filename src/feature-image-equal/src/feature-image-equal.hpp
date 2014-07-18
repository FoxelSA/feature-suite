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

    //! @file   feature-image-equal.hpp
    //! @author Nils Hamel (nils.hamel@foxel.ch)
    //! 
    //! Software main header (single function software)

/* 
    Header - Include guard
 */

    # ifndef __FEATURE_IMAGE_EQUAL__
    # define __FEATURE_IMAGE_EQUAL__

/* 
    Header - Includes
 */

    # include <iostream>
    # include <vector>
    # include <numeric>
    # include <opencv2/opencv.hpp>
    # include <opencv2/highgui/highgui_c.h>
    # include "common-stdap.hpp"

/* 
    Header - Preprocessor definitions
 */

    /* Equalization mode */
    # define FS_MODE_TO_HIGHEST 1
    # define FS_MODE_TO_LOWEST  2

/* 
    Header - Preprocessor macros
 */

    /* Standard help */
    # define FS_HELP "feature-image-equal - feature-suite\nCopyright (c) 2013-2014 FOXEL SA - http://foxel.ch\n" \
                     "See https://github.com/FoxelSA/feature-suite for more information\n"

    /* Compute vector mean value */
    # define FS_VMEAN(v)         ( ( float ) std::accumulate( v.begin(), v.end(), 0.0) / ( float ) v.size() )

    /* Compute vector standard deviation */
    # define FS_VSTDD(v,m)       ( std::sqrt( ( float ) std::inner_product( v.begin(), v.end(), v.begin(), 0.0) / ( float ) v.size() - m * m ) )

/* 
    Header - Typedefs
 */

/* 
    Header - Structures
 */

/* 
    Header - Function prototypes
 */

    //! Software main function (single function software)

    //! The main function frame follows : parameters are initialized and read. The
    //! two images are loaded and their statistical quantities are computed. The
    //! two images are then aligned in term of exposure according to parameters.
    //! The two images are finaly both exported.
    //! 
    //! @param argc Standard main parameter
    //! @param argv Standard main parameter

    int main ( int argc, char ** argv );

/*
    Header - Include guard
 */

    # endif


