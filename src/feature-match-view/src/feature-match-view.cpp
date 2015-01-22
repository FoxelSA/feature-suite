/*
 * feature suite - Feature detection suite
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

    # include "feature-match-view.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path strings */
        char fsImAIPath[256] = { 0 };
        char fsImBIPath[256] = { 0 };
        char fsMatIPath[256] = { 0 };
        char fsImgOPath[256] = { 0 };

        /* Keypoint matrix size */
        int fsRows ( 0 );

        /* Keypoint coordinates */
        float fsKeyAI ( 0.0 );
        float fsKeyAX ( 0.0 );
        float fsKeyAY ( 0.0 );
        float fsKeyBI ( 0.0 );
        float fsKeyBX ( 0.0 );
        float fsKeyBY ( 0.0 );

        /* Input stream */
        std::ifstream fsMatchfile;

        /* Image variable */
        cv::Mat fsInputA;
        cv::Mat fsInputB;
        cv::Mat fsOutput;

        /* Search in parameters */
        lc_stdp( lc_stda( argc, argv, "--input-a"  , "-i" ), argv, fsImAIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--input-b"  , "-j" ), argv, fsImBIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--matchfile", "-m" ), argv, fsMatIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--output"   , "-o" ), argv, fsImgOPath, LC_STRING );

        /* Software swicth */
        if ( ( lc_stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {
    
            /* Read input image */
            fsInputA = cv::imread( fsImAIPath, CV_LOAD_IMAGE_GRAYSCALE );
            fsInputB = cv::imread( fsImBIPath, CV_LOAD_IMAGE_GRAYSCALE );

            /* Verify image reading */
            if ( ( fsInputA.data != NULL ) && ( fsInputB.data != NULL ) ) {

                /* Channel mixing parameters */
                cv::Mat fsMixArray[] = { fsInputA, 0.5 * fsInputB }; int fsMixParam[] = { 0, 0, 1, 1 };

                /* Create output matrix */
                fsOutput.create( fsInputA.rows, fsInputA.cols, CV_8UC3 );

                /* Create composite image by channel mixing */
                cv::mixChannels( fsMixArray, 2, & fsOutput, 1, fsMixParam, 2 );

                /* Open keypoint output file */
                fsMatchfile.open( fsMatIPath, std::ios::in );

                /* Verify stream state */
                if ( fsMatchfile.is_open() == true ) {

                    /* Read keypoint matrix size */
                    fsMatchfile >> fsRows;

                    /* Export results */
                    for ( int fsIndex( 0 ); fsIndex < fsRows; fsIndex ++ ) {

                        /* Read current keypoint */
                        fsMatchfile >> fsKeyAI >> fsKeyBI >> fsKeyAX >> fsKeyAY >> fsKeyBX >> fsKeyBY;

                        /* Draw match line */
                        cv::line( fsOutput, cv::Point2f( fsKeyAX, fsKeyAY ), cv::Point( fsKeyBX, fsKeyBY ), cv::Scalar( 0, 177, 235 ) );

                    }

                    /* Close output stream */
                    fsMatchfile.close();

                    /* Write result image */
                    if ( imwrite( fsImgOPath, fsOutput ) ) {

                        /* Display message */
                        std::cout << "Exported " << fsImgOPath << " using keyfile " << fsMatIPath << std::endl;

                    /* Display message */
                    } else { std::cout << "Error : Unable to write output image" << std::endl; }

                /* Display message */
                } else { std::cout << "Error : Unable to read input matchfile" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Unable to read input images" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

