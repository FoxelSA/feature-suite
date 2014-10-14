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

    # include "feature-key-SIFT.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path variables */
        char fsImgIPath[256] = { };
        char fsKeyOPath[256] = { };

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
        stdp( stda( argc, argv, "--input"   , "-i" ), argv,   fsImgIPath    , FS_STRING );
        stdp( stda( argc, argv, "--output"  , "-o" ), argv,   fsKeyOPath    , FS_STRING );
        stdp( stda( argc, argv, "--maximum" , "-m" ), argv, & fsSIFTmaximum , FS_INT    );
        stdp( stda( argc, argv, "--octave"  , "-a" ), argv, & fsSIFToctave  , FS_INT    );
        stdp( stda( argc, argv, "--contrast", "-c" ), argv, & fsSIFTcontrast, FS_FLOAT  );
        stdp( stda( argc, argv, "--edge"    , "-e" ), argv, & fsSIFTedge    , FS_FLOAT  );
        stdp( stda( argc, argv, "--sigma"   , "-s" ), argv, & fsSIFTsigma   , FS_FLOAT  );
        stdp( stda( argc, argv, "--edge-x"  , "-x" ), argv, & fsEdgeX       , FS_INT    );
        stdp( stda( argc, argv, "--edge-y"  , "-y" ), argv, & fsEdgeY       , FS_INT    );

        /* Software swicth */
        if ( ( stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {
    
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
                    std::cout << "Exported " << fsSIFTexported << " in file " << fsKeyOPath << std::endl;

                /* Display message */
                } else { std::cout << "Error : Unable to write output file" << std::endl; }

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

