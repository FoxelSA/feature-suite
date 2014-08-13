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

    /*! \file   feature-match-sieve.hpp
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *  
     *  Software main header
     */

    /*! \mainpage feature-match-sieve
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

    # ifndef __FS_MATCH_SIEVE__
    # define __FS_MATCH_SIEVE__

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
    # include "common-stdap.hpp"

/* 
    Header - Preprocessor definitions
 */

/* 
    Header - Preprocessor macros
 */

    /* Standard help */
    # define FS_HELP "feature-match-sieve - feature-suite\nCopyright (c) 2013-2014 FOXEL SA - http://foxel.ch\n" \
                     "See https://github.com/FoxelSA/feature-suite for more information\n"

    /* Compute match distance */
    # define FS_DIST(m)         ( sqrt( ( m.ax - m.bx ) * ( m.ax - m.bx ) + ( m.ay - m.by ) * ( m.ay - m.by ) ) )

    /* Compute vector mean value */
    # define FS_VMEAN(v)        ( ( float ) std::accumulate( v.begin(), v.end(), 0.0) / ( float ) v.size() )

    /* Compute vector standard deviation */
    # define FS_VSTDD(v,m)      ( std::sqrt( ( float ) std::inner_product( v.begin(), v.end(), v.begin(), 0.0) / ( float ) v.size() - m * m ) )

    /* Compute sign */
    # define FS_SIGN(x)         ( ( x > 0 ) ? 1 : -1 )

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
     *  matches file is read and the desired sieve is applied according to parameters.
     *  The matches that passed the sieve are then exported in the output matches
     *  file.
     *  
     *  \param argc Standard main parameter
     *  \param argv Standard main parameter
     */

    int main ( int argc, char ** argv );

    /*! \brief Statistical distance sieve
     *  
     *  This function compute the disparity of the input matches and extract the
     *  statistical quantities of it. The sieve is applied according to those
     *  quantities and the standard deviation tolerence factor. The smaller is
     *  this factor, the more strict is the sieve.
     *  
     *  \param fsRaw Raw matches
     *  \param fsStdtol Standard deviation tolerence factor
     *  \return Matches that passed the sieve
     */

    std::vector < fs_match > fs_matchSIEVE_stat_dist ( std::vector < fs_match > fsRaw, float fsStdtol );

    /*! \brief Threshold distance sieve
     *  
     *  This function filter the matches by removing the ones that have a disparity
     *  outside of the range defined by the minimum and maximum parameters.
     *  
     *  \param fsRaw Raw matches
     *  \param fsMininum Minimum disparity threshold
     *  \param fsMaximum Maximum disparity threshold
     *  \return Matches that passed the sieve
     */

    std::vector < fs_match > fs_matchSIEVE_thre_dist ( std::vector < fs_match > fsRaw, float fsMininum, float fsMaximum );

    /*! \brief Statistical displacement sieve
     *  
     *  This function compute the statistical quantities of the x and y components of
     *  the disparity. The sieve criteria is based on distribution standard deviations
     *  and the tolerence factor.
     *  
     *  \param fsRaw Raw matches
     *  \param fsStdtol Standard deviation tolerence factor
     *  \return Matches that passed the sieve
     */

    std::vector < fs_match > fs_matchSIEVE_stat_disp ( std::vector < fs_match > fsRaw, float fsStdtol );

    /*! \brief Statistical flow sieve
     *  
     *  This function compute the statistical quantities of the normalized x and y components
     *  of the disparity. The sieve criteria is based on distribution standard deviations
     *  and the tolerence factor.
     *  
     *  \param fsRaw Raw matches
     *  \param fsStdtol Standard deviation tolerence factor
     *  \return Matches that passed the sieve
     */

    std::vector < fs_match > fs_matchSIEVE_stat_flow ( std::vector < fs_match > fsRaw, float fsStdtol );

    /*! \brief Dichotomous slop sieve
     *  
     *  This function compute the sign of the slope of the matches disparity. The matches
     *  that have the same slope as the statistically most represented one are kept.
     *  
     *  \param fsRaw Raw matches
     *  \return Matches that passed the sieve
     */

    std::vector < fs_match > fs_matchSIEVE_dich_slop ( std::vector < fs_match > fsRaw );

/*
    Header - Include guard
 */

    # endif


