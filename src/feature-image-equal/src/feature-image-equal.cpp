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

    # include "feature-image-equal.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path variables */
        char * fsImAIPath( NULL );
        char * fsImBIPath( NULL );
        char * fsEqAOPath( NULL );
        char * fsEqBOPath( NULL );

        /* Parameters variables */
        int fsMode = FS_MODE_TO_HIGHEST;

        /* Equalization variables */
        double fsMeanA ( 0.0 );
        double fsMeanB ( 0.0 );
        double fsStddA ( 0.0 );
        double fsStddB ( 0.0 );

        /* Images variables */
        cv::Mat fsImageA;
        cv::Mat fsImageB;

        /* Arguments and parameters handle */
        lc_stdp( lc_stda( argc, argv, "--input-a" , "-a" ), argv, & fsImAIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--input-b" , "-b" ), argv, & fsImBIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--output-a", "-c" ), argv, & fsEqAOPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--output-b", "-d" ), argv, & fsEqBOPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--mode"    , "-m" ), argv, & fsMode    , LC_INT    );

        /* Software swicth */
        if ( ( lc_stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {

            /* Verify path strings */
            if ( ( fsImAIPath != NULL ) && ( fsImBIPath != NULL ) && ( fsEqAOPath != NULL ) && ( fsEqBOPath != NULL ) ) {

                /* Read images */
                fsImageA = cv::imread( fsImAIPath, CV_LOAD_IMAGE_GRAYSCALE );
                fsImageB = cv::imread( fsImBIPath, CV_LOAD_IMAGE_GRAYSCALE );

                /* Check images reading */
                if ( ( fsImageA.data != NULL ) && ( fsImageB.data != NULL ) ) {

                    /* Statistical buffers */
                    std::vector < char > fsByteA( fsImageA.data, fsImageA.data + fsImageA.rows * fsImageA.cols * fsImageA.channels() );
                    std::vector < char > fsByteB( fsImageB.data, fsImageB.data + fsImageB.rows * fsImageB.cols * fsImageB.channels() );
                    
                    /* Compute statistical means */
                    fsMeanA = LC_VMEAN( fsByteA );
                    fsMeanB = LC_VMEAN( fsByteB );

                    /* Compute statistical standard deviation */
                    fsStddA = LC_VSTDD( fsByteA, fsMeanA );
                    fsStddB = LC_VSTDD( fsByteB, fsMeanB );

                    /* Check equalization mode */
                    if ( fsMode == FS_MODE_TO_HIGHEST ) {

                        /* Retrieve highest contrast */
                        if ( fsMeanA > fsMeanB ) {

                            /* Apply exposure correction */
                            fsImageB = ( ( fsImageB - fsMeanB ) / ( 2.0 * fsStddB ) ) * 2.0 * fsStddA + fsMeanA;

                        } else {

                            /* Apply exposure correction */
                            fsImageA = ( ( fsImageA - fsMeanA ) / ( 2.0 * fsStddA ) ) * 2.0 * fsStddB + fsMeanB;

                        }

                    } else {

                        /* Retrieve highest contrast */
                        if ( fsMeanA > fsMeanB ) {

                            /* Apply exposure correction */
                            fsImageA = ( ( fsImageA - fsMeanA ) / ( 2.0 * fsStddA ) ) * 2.0 * fsStddB + fsMeanB;

                        } else {

                            /* Apply exposure correction */
                            fsImageB = ( ( fsImageB - fsMeanB ) / ( 2.0 * fsStddB ) ) * 2.0 * fsStddA + fsMeanA;

                        }

                    }

                    /* Write result image */
                    if ( imwrite( fsEqAOPath, fsImageA ) == false ) {

                        std::cerr << "Error : Unable to write " << fsEqAOPath << " output image" << std::endl;

                    }

                    /* Write result image */
                    if ( imwrite( fsEqBOPath, fsImageB ) == false ) {

                        /* Display message */
                        std::cerr << "Error : Unable to write " << fsEqBOPath << " output image" << std::endl;

                    }

                /* Display message */
                } else { std::cerr << "Error : Unable to read input images" << std::endl; }

            /* Display message */
            } else { std::cerr << "Error : Invalid path specification" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

