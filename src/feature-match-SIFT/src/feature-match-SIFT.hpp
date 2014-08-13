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

    /*! \file   feature-match-SIFT.hpp
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *  
     *  Software main header
     */

    /*! \mainpage feature-match-SIFT
     *
     *  \section feature-suite
     *  \section _ Features detection suite
     *  
     *  The feature-suite provides tools in the context of automatic image matching.
     *  The suite is separated into small softwares that solve a specific part of
     *  the problem. It is designed so in order to perform research using each
     *  software as a brick of the overall solver.
     *
     *  \section Documentation
     *
     *  More documentation can be found on the wiki provided on the project github
     *  repository (https://github.com/FoxelSA/feature-suite/wiki).
     *
     *  \section Copyright
     * 
     *  Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch \n
     *  This program is part of the FOXEL project <http://foxel.ch>.
     *  
     *  Please read the COPYRIGHT.md file for more information.
     *
     *  \section License
     *
     *  This program is licensed under the terms of the GNU Affero General Public License
     *  v3 (GNU AGPL), with two additional terms. The content is licensed under the terms 
     *  of the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA) license.
     *
     *  You must read <http://foxel.ch/license> for more information about our Licensing
     *  terms and our Usage and Attribution guidelines.
     */

/* 
    Header - Include guard
 */

    # ifndef __FS_MATCH_SIFT__
    # define __FS_MATCH_SIFT__

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

    /*! \brief Software main function
     *  
     *  The main function frame follows : parameters are initialized and read. The
     *  two input images are imported in grayscale mode and the two keypoints files
     *  are read. The OpenCV SIFT descriptor is called befor the OpenCV Flann matcher
     *  generate the matches. The list of matches is then exported.
     *  
     *  \param argc Standard main parameter
     *  \param argv Standard main parameter
     */

    int main ( int argc, char ** argv );

    /*! \brief Keypoints file reader
     *  
     *  The function simply load the keypoint information from the specified file.
     *  
     *  \param fsKeyfile Path of the keypoints file
     *  \return Read keypoint
     */

    std::vector < cv::KeyPoint > fs_matchSIFT_readkey ( const char * const fsKeyfile );

/*
    Header - Include guard
 */

    # endif


