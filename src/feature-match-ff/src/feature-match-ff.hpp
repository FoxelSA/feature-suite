/*
 * feature suite - Feature detection suite
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Stephane Flotron <s.flotron@foxel.ch>
 *
 * Contributor(s):
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

    /*! \file   feature-match-ff.hpp
     *  \author Stephane Flotron (s.flotron@foxel.ch)
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *  
     *  Software main header (single function software)
     */

    /*! \mainpage feature-match-ff
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

    # ifndef __FS_MATCH_FF__
    # define __FS_MATCH_FF__

/* 
    Header - Includes
 */

    # include <iostream>
    # include <fstream>
    # include <vector>
    # include <cstring>
    # include <cstdlib>
    # include <cmath>
    # include <numeric>
    # include <climits>
    # include <opencv2/opencv.hpp>
    # include <opencv2/highgui/highgui_c.h>
    # include "common-stdap.hpp"

/* 
    Header - Preprocessor definitions
 */

    /* Standard help */
    # define FS_HELP "feature-match-ff - feature-suite\nCopyright (c) 2013-2014 FOXEL SA - http://foxel.ch\n" \
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

    /*! \struct fs_matchSIEVE_match_struct
     *  \brief Match structure
     *  
     *  Structure that stores the description of a match between two keypoints.
     *  
     *  \var fs_matchSIEVE_match_struct::ai
     *  Index of the first keypoint in the keypoints list
     *  \var fs_matchSIEVE_match_struct::ax
     *  Position x of the keypoint on the first image
     *  \var fs_matchSIEVE_match_struct::ay 
     *  Position y of the keypoint on the first image
     *  \var fs_matchSIEVE_match_struct::bi 
     *  Index of the second keypoint in the keypoints list
     *  \var fs_matchSIEVE_match_struct::bx
     *  Position x of the keypoint on the second image
     *  \var fs_matchSIEVE_match_struct::by 
     *  Position z of the keypoint on the second image
     */

    typedef struct fs_matchSIEVE_match_struct {

        int   ai;
        float ax;
        float ay;
        int   bi;
        float bx;
        float by;

    } fs_match;

/* 
    Header - Function prototypes
 */

    /*! \brief Software main function
     *  
     *  The main function frame follows : parameters are initialized and read. The
     *  assumed good matches are read and the fundamental matrix estimation is
     *  performed on their basis. The set of matches to filter is read and the
     *  fundamental matrix sieve applies. The filtered matches are then exported.
     *  
     *  \param argc Standard main parameter
     *  \param argv Standard main parameter
     */

    int main ( int argc, char ** argv );

/*
    Header - Include guard
 */

    # endif

