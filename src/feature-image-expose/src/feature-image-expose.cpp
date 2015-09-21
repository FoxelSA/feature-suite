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

    # include "feature-image-expose.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path variables */
        char fsImgIPath[256] = { 0 };
        char fsImgOPath[256] = { 0 };

        /* Execution mode variables */
        char fsMode[256] = { 0 };

        /* Parameters variables */
        float fsFixMean ( 0.0 );
        float fsFixStdd ( 0.0 );

        /* Statistical variables */
        float fsMean ( 0.0 );
        float fsStdD ( 0.0 );

        /* Image variable */
        cv::Mat fsImage;

        /* Search in parameters */
        lc_stdp( lc_stda( argc, argv, "--input" , "-i" ), argv,   fsImgIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--output", "-o" ), argv,   fsImgOPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--mode"  , "-d" ), argv,   fsMode    , LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--mean"  , "-m" ), argv, & fsFixMean , LC_FLOAT  );
        lc_stdp( lc_stda( argc, argv, "--stdd"  , "-s" ), argv, & fsFixStdd , LC_FLOAT  );

        /* Software swicth */
        if ( ( lc_stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {
    
            /* Read input image */
            fsImage = cv::imread( fsImgIPath, CV_LOAD_IMAGE_COLOR );

            /* Verify image reading */
            if ( fsImage.data != NULL ) {

                /* Create array on image bytes */
                std::vector < char > fsBytes( fsImage.data, fsImage.data + fsImage.rows * fsImage.cols * fsImage.channels() );

                /* Software switch */
                if ( lc_stda( argc, argv, "--get", "-g" ) ) {

                    /* Check execution mode */
                    if ( ( strcmp( fsMode, "mean" ) == 0 ) || ( strcmp( fsMode, "both" ) == 0 ) ) {

                        /* Compute histogram mean */
                        fsMean = LC_VMEAN( fsBytes );

                        /* Display mean value */
                        std::cout << fsMean << std::endl;

                    }

                    if ( ( strcmp( fsMode, "std" ) == 0 ) || ( strcmp( fsMode, "both" ) == 0 ) ) {

                        /* Compute histogram standard deviation */
                        fsStdD = LC_VSTDD( fsBytes, fsMean );

                        /* Display standard deviation value */
                        std::cout << fsStdD << std::endl;

                    }

                } else if ( lc_stda( argc, argv, "--set", "-e" ) ) {

                    /* Check execution mode */
                    if ( ( strcmp( fsMode, "mean" ) == 0 ) || ( strcmp( fsMode, "both" ) == 0 ) ) {

                        /* Compute histogram mean */
                        fsMean = LC_VMEAN( fsBytes );

                        /* Check execution mode */
                        if ( strcmp( fsMode, "both" ) != 0 ) {

                            /* Exposure correction */
                            fsImage = fsImage + ( fsFixMean - fsMean );

                        }

                    }

                    if ( ( strcmp( fsMode, "stdd" ) == 0 ) || ( strcmp( fsMode, "both" ) == 0 ) ) {

                        /* Compute histogram standard deviation */
                        fsStdD = LC_VSTDD( fsBytes, fsMean );

                        /* Check execution mode */
                        if ( strcmp( fsMode, "both" ) != 0 ) {

                            /* Exposure correction */
                            fsImage = fsImage * ( fsFixStdd / fsStdD );

                        }

                    }

                    /* Check execution mode */
                    if ( strcmp( fsMode, "both" ) == 0 ) {

                        /* Exposure correction */
                        fsImage = ( ( fsImage - fsMean ) / fsStdD ) * fsFixStdd + fsFixMean;

                    }

                    /* Write result image */
                    if ( imwrite( fsImgOPath, fsImage ) == false ) {

                        /* Display message */
                        std::cout << "Error : Unable to write output image" << std::endl;

                    }

                /* Display message */
                } else { std::cout << "Error : Execution switch not provided" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Unable to read input image" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

