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
    Source - Includes
 */

    # include "feature-key-view.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path strings */
        char  fsImgIPath[256] = { '\0' };
        char  fsImgOPath[256] = { '\0' };
        char  fsKeyIPath[256] = { '\0' };

        /* Keypoint coordinates */
        float fsKeyX = 0.0;
        float fsKeyY = 0.0;
        float fsVoid = 0.0;

        /* Keypoint matrix size */
        int   fsRows = 0;

        /* Input stream */
        std::ifstream fsKeyfile;

        /* Image variable */
        cv::Mat fsImage;

        /* Search in parameters */
        stdp( stda( argc, argv, "--input"   , "-i" ), argv, fsImgIPath, __STDP_STRING );
        stdp( stda( argc, argv, "--output"  , "-o" ), argv, fsImgOPath, __STDP_STRING );
        stdp( stda( argc, argv, "--keyfile" , "-k" ), argv, fsKeyIPath, __STDP_STRING );

        /* Software swicth */
        if ( stda( argc, argv, "--help", "-h" ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {
    
            /* Read input image */
            fsImage = cv::imread( fsImgIPath, CV_LOAD_IMAGE_GRAYSCALE );

            /* Verify image reading */
            if ( fsImage.data != NULL ) {

                /* Convert image to RGB */
                cvtColor( fsImage, fsImage, CV_GRAY2RGB );

                /* Open keypoint output file */
                fsKeyfile.open( fsKeyIPath, std::ios::in );

                /* Verify stream state */
                if ( fsKeyfile.is_open() == true ) {

                    /* Read keypoint matrix size */
                    fsKeyfile >> fsRows;

                    /* Export results */
                    for ( int fsIndex = 0; fsIndex < fsRows; fsIndex ++ ) {

                        /* Read current keypoint */
                        fsKeyfile >> fsKeyX >> fsKeyY >> fsVoid >> fsVoid >> fsVoid >> fsVoid;

                        /* Draw cricle in image */
                        cv::circle( fsImage, cv::Point2f( fsKeyX, fsKeyY ), 4, cv::Scalar( 0, 177, 235 ) );

                    }

                    /* Close output stream */
                    fsKeyfile.close();

                    /* Write result image */
                    if ( imwrite( fsImgOPath, fsImage ) ) {

                        /* Display message */
                        std::cout << "Exported " << fsImgOPath << " using keyfile " << fsKeyIPath << std::endl;

                    /* Display message */
                    } else { std::cout << "Error : Unable to write output image" << std::endl; }

                /* Display message */
                } else { std::cout << "Error : Unable to read keyfile" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Unable to read input image" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

