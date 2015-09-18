/*
 * feature-suite libcommon - feature-suite common library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
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
    Source - Includes
 */

    # include "common-opencv.hpp"

/*
    Source - Image exportation interface
 */

    bool lc_imwrite( char * lcPath, cv::Mat lcImage, int lcOption ) {

        /* Extension pointer variables */
        char * lcExt = strrchr( lcPath, '.' );

        /* Search image type */
        if ( ( lcOption >= 0 ) && ( ( strcasecmp( lcExt + 1, "jpg" ) == 0 ) || ( strcasecmp( lcExt + 1, "jpeg" ) == 0 ) ) ) {

            /* Specific exportation method */
            return( lc_imwrite_jpeg( lcPath, lcImage, lcOption ) );

        } else
        if ( ( lcOption >= 0 ) && ( strcasecmp( lcExt + 1, "png" ) == 0 ) ) {

            /* Specific exportation method */
            return( lc_imwrite_png( lcPath, lcImage, lcOption ) );

        } else {

            /* Standard exportation method */
            return( imwrite( lcPath, lcImage ) );

        }

    }

/*
    Source - Image exportation methods
 */

    bool lc_imwrite_jpeg( char * lcPath, cv::Mat lcImage, int lcQuality ) {

        /* Option array variables */
        std::vector <int> lcOptions;

        /* Pushing options values */
        lcOptions.push_back( CV_IMWRITE_JPEG_QUALITY );
        lcOptions.push_back( ( lcQuality > 100 ) ? 100: ( ( lcQuality < 0 ) ? 0 : lcQuality ) );

        /* Image exportation */
        return( imwrite(  lcPath, lcImage, lcOptions ) );

    }

    bool lc_imwrite_png( char * lcPath, cv::Mat lcImage, int lcCompression ) {

        /* Option array variables */
        std::vector <int> lcOptions;

        /* Pushing options values */
        lcOptions.push_back( CV_IMWRITE_PNG_COMPRESSION );
        lcOptions.push_back( ( lcCompression > 9 ) ? 9 : ( ( lcCompression < 0 ) ? 0 : lcCompression ) );

        /* Image exportation */
        return( imwrite(  lcPath, lcImage, lcOptions ) );

    }

