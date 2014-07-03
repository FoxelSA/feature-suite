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

    # ifndef __FEATURE_MATCH_SIEVE__
    # define __FEATURE_MATCH_SIEVE__

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

    /* Define match structure */
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

    std::vector < fs_match > fs_matchSIEVE_stat_dist ( std::vector < fs_match > fsRaw, float fsStdtol );
    std::vector < fs_match > fs_matchSIEVE_thre_dist ( std::vector < fs_match > fsRaw, float fsMininum, float fsMaximum );
    std::vector < fs_match > fs_matchSIEVE_stat_disp ( std::vector < fs_match > fsRaw, float fsStdtol );
    std::vector < fs_match > fs_matchSIEVE_stat_flow ( std::vector < fs_match > fsRaw, float fsStdtol );
    std::vector < fs_match > fs_matchSIEVE_dich_slop ( std::vector < fs_match > fsRaw );

/*
    Header - Include guard
 */

    # endif


