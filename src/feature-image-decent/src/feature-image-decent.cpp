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

    # include "feature-image-decent.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path varaibles */
        char  fsImgIPath[256] = { '\0' };
        char  fsImgOPath[256] = { '\0' };

        /* Parameters variables */
        float fsMin   = 0.5;
        float fsMax   = 0.7;

        /* Entropy comuptation variables */
        int   fsSampleX1 = 0;
        int   fsSampleX2 = 0;
        int   fsSampleY1 = 0;
        int   fsSampleY2 = 0;

        /* Entropy accumulator stack */
        int   fsStack = 0;

        /* Entropy accumulator */
        float fsAccum[ FS_SAMPLE_C ] = { 0.0 };

        /* Images variables */
        cv::Mat fsImage;
        cv::Mat fsHmaps;

        /* Arguments and parameters handle */
        stdp( stda( argc, argv, "--input" , "-i" ), argv,   fsImgIPath, __STDP_STRING );
        stdp( stda( argc, argv, "--output", "-o" ), argv,   fsImgOPath, __STDP_STRING );
        stdp( stda( argc, argv, "--min"   , "-n" ), argv, & fsMin     , __STDP_FLOAT  );
        stdp( stda( argc, argv, "--max"   , "-x" ), argv, & fsMax     , __STDP_FLOAT  );

        /* Software swicth */
        if ( stda( argc, argv, "--help", "-h" ) ) {

            /* Display message */
            std::cout << "Dave, this conversation can serve no purpose anymore. Goodbye." << std::endl;

        } else {

            /* Read images */
            fsImage = cv::imread( fsImgIPath, CV_LOAD_IMAGE_GRAYSCALE );

            /* Check images reading */
            if ( fsImage.data != NULL ) {

                // Allocate entropy map */
                fsHmaps.create( fsImage.rows, fsImage.cols, CV_32FC1 );

                /* Parse entire image */
                for ( int fsY = 0; fsY < fsImage.rows; fsY ++ )
                for ( int fsX = 0; fsX < fsImage.cols; fsX ++ ) {

                    /* Compute area boundaries */
                    fsSampleX1 = FS_MAX( 0               , fsX - FS_SAMPLE_X );
                    fsSampleX2 = FS_MIN( fsImage.cols - 1, fsX + FS_SAMPLE_X );
                    fsSampleY1 = FS_MAX( 0               , fsY - FS_SAMPLE_Y );
                    fsSampleY2 = FS_MIN( fsImage.rows - 1, fsY + FS_SAMPLE_Y );

                    /* Reset entropy sampling */
                    fsStack = 0;

                    /* Compute entropy accumulator */
                    for ( int fsSY = fsSampleY1; fsSY <= fsSampleY2; fsSY ++ )
                    for ( int fsSX = fsSampleX1; fsSX <= fsSampleX2; fsSX ++ ) {

                        /* Accumulate values */
                        fsAccum[fsStack++] = fsImage.at < uchar > ( fsSY, fsSX );

                    }

                    /* Compute Shannon entropy */
                    fsHmaps.at < float > ( fsY, fsX ) = 1.0 - FS_MAX( 0, FS_MIN( 1.0, ( fs_imagedecent_shannon( fsAccum, fsStack ) - fsMin ) / ( fsMax - fsMin ) ) );

                }

                /* Entropy map blurring */
                cv::GaussianBlur( fsHmaps, fsHmaps, cv::Size( 65, 65 ), 0 ); 

                /* Parse entire image */
                for ( int fsY = 0; fsY < fsImage.rows; fsY ++ )
                for ( int fsX = 0; fsX < fsImage.cols; fsX ++ ) {

                    /* Apply entropic filter */
                    fsImage.at < uchar > ( fsY, fsX ) *= fsHmaps.at < float > ( fsY, fsX );

                }

                /* Write result image */
                if ( imwrite( fsImgOPath, fsImage ) ) {

                    /* Display message */
                    std::cout << "Exported " << fsImgOPath << std::endl;

                /* Display message */
                } else { std::cout << "Error : Unable to write output image" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Unable to read input images" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

/*
    Source - Compute Shannon entropy
 */

    float fs_imagedecent_shannon( float fsAccum[], int fsStack ) {

        /* Entropy variable */
        float fsResult = 0.0;

        /* Probability distribution */
        int fsPDF[256] = { 0 };

        /* Compute PDF */
        for ( int fsIndex = 0; fsIndex < fsStack; fsIndex ++ ) {

            /* Update probability */
            fsPDF[int(fsAccum[fsIndex])] ++;

        }

        /* Compute entropy */
        for ( int fsIndex = 0; fsIndex < 256; fsIndex ++ ) {

            if ( fsPDF[fsIndex] > 0 ) {

            /* Update entropy */
            fsResult -= ( float( fsPDF[fsIndex] ) / fsStack ) 
                 * ( log( float( fsPDF[fsIndex] ) / fsStack ) / log( 256.0 ) );

            }

        }

        /* Return entropy value */
        return( fsResult );

    }
 
