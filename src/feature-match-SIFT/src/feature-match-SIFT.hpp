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

    //! @file   feature-match-SIFT.hpp
    //! @author Nils Hamel (nils.hamel@foxel.ch)
    //! 
    //! Software main header

/* 
    Header - Include guard
 */

    # ifndef __FEATURE_MATCH_SIFT__
    # define __FEATURE_MATCH_SIFT__

/* 
    Header - Includes
 */

    # include <iostream>
    # include <fstream>
    # include <opencv2/opencv.hpp>
    # include <opencv2/highgui/highgui_c.h>
    # include <opencv2/nonfree/features2d.hpp>
    # include "common-stdap.hpp"

/* 
    Header - Preprocessor definitions
 */

    /* Standard help */
    # define FS_HELP "feature-match-SIFT - feature-suite\nCopyright (c) 2013-2014 FOXEL SA - http://foxel.ch\n" \
                     "See https://github.com/FoxelSA/feature-suite for more information\n"

/* 
    Header - Preprocessor macros
 */

/* 
    Header - Typedefs
 */

/* 
    Header - Structures
 */

/* 
    Header - Function prototypes
 */

    //! Software main function

    //! The main function frame follows : parameters are initialized and read. The
    //! two input images are imported in grayscale mode and the two keypoints files
    //! are read. The OpenCV SIFT descriptor is called befor the OpenCV Flann matcher
    //! generate the matches. The list of matches is then exported.
    //! 
    //! @param argc Standard main parameter
    //! @param argv Standard main parameter

    int main ( int argc, char ** argv );

    //! Keypoints file reader

    //! The function simply load the keypoint information from the specified file.
    //!
    //! @param fsKeyfile Path of the keypoints file
    //! @return Read keypoint

    std::vector < cv::KeyPoint > fs_matchSIFT_readkey ( const char * const fsKeyfile );

/*
    Header - Include guard
 */

    # endif


