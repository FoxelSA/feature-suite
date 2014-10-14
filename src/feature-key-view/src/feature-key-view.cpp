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
        char  fsImgIPath[256] = { };
        char  fsImgOPath[256] = { };
        char  fsKeyIPath[256] = { };

        /* Keypoint coordinates */
        float fsKeyX ( 0.0 );
        float fsKeyY ( 0.0 );
        float fsVoid ( 0.0 );

        /* Keypoint matrix size */
        int fsRows ( 0 );

        /* Input stream */
        std::ifstream fsKeyfile;

        /* Image variable */
        cv::Mat fsImage;

        /* Search in parameters */
        stdp( stda( argc, argv, "--input"   , "-i" ), argv, fsImgIPath, FS_STRING );
        stdp( stda( argc, argv, "--output"  , "-o" ), argv, fsImgOPath, FS_STRING );
        stdp( stda( argc, argv, "--keyfile" , "-k" ), argv, fsKeyIPath, FS_STRING );

        /* Software swicth */
        if ( ( stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

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

                    /* Read keypoint count */
                    fsKeyfile >> fsRows;

                    /* Export results */
                    for ( int fsIndex( 0 ); fsIndex < fsRows; fsIndex ++ ) {

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

/*
    Source - Arguments common handler
 */

    int stda( int argc, char ** argv, char const * const ltag, char const * const stag ) {

        /* Search for argument */
        while ( ( -- argc ) > 0 ) {

            /* Search for tag matching */
            if ( ( strcmp( argv[ argc ], ltag ) == 0 ) || ( strcmp( argv[ argc ], stag ) == 0 ) ) {

                /* Return pointer to argument parameter */
                return( argc + 1 );

            }

        /* Argument not found */
        } return( FS_NULL );

    }

/*
    Source - Parameters common handler
 */

    void stdp( int argi, char ** argv, void * const param, int const type ) {

        /* Index consistency */
        if ( argi == FS_NULL ) return;

        /* Select type */
        switch ( type ) {

            /* Specific reading operation - Integers */
            case ( FS_CHAR   ) : { * ( signed char        * ) param = atoi ( ( const char * ) argv[argi] ); } break;
            case ( FS_SHORT  ) : { * ( signed short       * ) param = atoi ( ( const char * ) argv[argi] ); } break;
            case ( FS_INT    ) : { * ( signed int         * ) param = atoi ( ( const char * ) argv[argi] ); } break;
            case ( FS_LONG   ) : { * ( signed long        * ) param = atol ( ( const char * ) argv[argi] ); } break;
            case ( FS_LLONG  ) : { * ( signed long long   * ) param = atoll( ( const char * ) argv[argi] ); } break;
            case ( FS_UCHAR  ) : { * ( unsigned char      * ) param = atol ( ( const char * ) argv[argi] ); } break;
            case ( FS_USHORT ) : { * ( unsigned short     * ) param = atol ( ( const char * ) argv[argi] ); } break;
            case ( FS_UINT   ) : { * ( unsigned int       * ) param = atol ( ( const char * ) argv[argi] ); } break;
            case ( FS_ULONG  ) : { * ( unsigned long      * ) param = atoll( ( const char * ) argv[argi] ); } break;
            case ( FS_ULLONG ) : { * ( unsigned long long * ) param = atoll( ( const char * ) argv[argi] ); } break;

            /* Specific reading operation - Floating point */
            case ( FS_FLOAT  ) : { * ( float              * ) param = atof ( ( const char * ) argv[argi] ); } break;
            case ( FS_DOUBLE ) : { * ( double             * ) param = atof ( ( const char * ) argv[argi] ); } break;

            /* Specific reading operation - String */
            case ( FS_STRING ) : { strcpy( ( char * ) param, ( const char * ) argv[argi] );  } break;

        };

    }

