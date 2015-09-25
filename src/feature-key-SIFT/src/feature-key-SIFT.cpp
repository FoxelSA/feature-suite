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

    # include "feature-key-SIFT.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path variables */
        char * fsImgIPath( NULL );
        char * fsKeyOPath( NULL );

        /* SIFT variables */
        int   fsSIFTexported ( 0    );
        int   fsSIFTmaximum  ( 0    );
        int   fsSIFToctave   ( 3    );
        float fsSIFTcontrast ( 0.04 );
        float fsSIFTedge     ( 10   );
        float fsSIFTsigma    ( 1.6  );

        /* Geometric filter */
        int fsEdgeX ( 0 );
        int fsEdgeY ( 0 );

        /* Output stream */
        std::ofstream fsKeyfile;

        /* Image variable */
        cv::Mat fsImage;

        /* Search in parameters */
        lc_stdp( lc_stda( argc, argv, "--input"   , "-i" ), argv, & fsImgIPath    , LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--output"  , "-o" ), argv, & fsKeyOPath    , LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--maximum" , "-m" ), argv, & fsSIFTmaximum , LC_INT    );
        lc_stdp( lc_stda( argc, argv, "--octave"  , "-a" ), argv, & fsSIFToctave  , LC_INT    );
        lc_stdp( lc_stda( argc, argv, "--contrast", "-c" ), argv, & fsSIFTcontrast, LC_FLOAT  );
        lc_stdp( lc_stda( argc, argv, "--edge"    , "-e" ), argv, & fsSIFTedge    , LC_FLOAT  );
        lc_stdp( lc_stda( argc, argv, "--sigma"   , "-s" ), argv, & fsSIFTsigma   , LC_FLOAT  );
        lc_stdp( lc_stda( argc, argv, "--edge-x"  , "-x" ), argv, & fsEdgeX       , LC_INT    );
        lc_stdp( lc_stda( argc, argv, "--edge-y"  , "-y" ), argv, & fsEdgeY       , LC_INT    );

        /* Software swicth */
        if ( ( lc_stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {

            /* Verify path strings */
            if ( ( fsImgIPath != NULL ) && ( fsKeyOPath != NULL ) ) {
    
                /* Read input image */
                fsImage = cv::imread( fsImgIPath, CV_LOAD_IMAGE_GRAYSCALE );

                /* Verify image reading */
                if ( fsImage.data != NULL ) {

                    /* Instance SIFT detector */
                    cv::SIFT fsSift( fsSIFTmaximum, fsSIFToctave, fsSIFTcontrast, fsSIFTedge, fsSIFTsigma );

                    /* Keypoint vector */
                    std::vector < cv::KeyPoint > fsKey;

                    /* SIFT detection */
                    fsSift.detect( fsImage, fsKey );

                    /* Open keypoint output file */
                    fsKeyfile.open( fsKeyOPath, std::ios::out );

                    /* Verify stream state */
                    if ( fsKeyfile.is_open() == true ) {

                        /* Export keypoint count */
                        fsKeyfile << fsKey.size() << std::endl;

                        /* Export results */
                        for ( unsigned int fsIndex( 0 ); fsIndex < fsKey.size(); fsIndex ++ ) {

                            /* Apply geometric filtering */
                            if ( ( fsKey[fsIndex].pt.x >= fsEdgeX ) && ( fsKey[fsIndex].pt.x < fsImage.cols - fsEdgeX ) &&
                                 ( fsKey[fsIndex].pt.y >= fsEdgeY ) && ( fsKey[fsIndex].pt.y < fsImage.rows - fsEdgeY ) ) {

                                /* Export keypoint coordinates */
                                fsKeyfile << fsKey[fsIndex].pt.x     << " " 
                                          << fsKey[fsIndex].pt.y     << " " 
                                          << fsKey[fsIndex].size     << " "
                                          << fsKey[fsIndex].angle    << " " 
                                          << fsKey[fsIndex].response << " " 
                                          << fsKey[fsIndex].octave   << std::endl; 

                                /* Increment exportation count */
                                fsSIFTexported ++;

                            }

                        }

                        /* Close output stream */
                        fsKeyfile.close();

                    /* Display message */
                    } else { std::cerr << "Error : Unable to write output file" << std::endl; }

                /* Display message */
                } else { std::cerr << "Error : Unable to read input image" << std::endl; }

            /* Display message */
            } else { std::cerr << "Error : Invalid path specification" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

