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

    # include "feature-match-SIFT.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path variables */
        char * fsImAIPath( NULL );
        char * fsKeAIPath( NULL );
        char * fsImBIPath( NULL );
        char * fsKeBIPath( NULL );
        char * fsMatOPath( NULL );

        /* Image variable */
        cv::Mat fsImageA, fsImageB;

        /* Output stream variable */
        std::ofstream fsMatchfile;

        /* Search in parameters */
        lc_stdp( lc_stda( argc, argv,  "--input-a"  , "-i" ), argv, & fsImAIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv,  "--input-b"  , "-j" ), argv, & fsImBIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv,  "--keyfile-a", "-k" ), argv, & fsKeAIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv,  "--keyfile-b", "-l" ), argv, & fsKeBIPath, LC_STRING );
        lc_stdp( lc_stda( argc, argv,  "--output"   , "-o" ), argv, & fsMatOPath, LC_STRING );

        /* Software swicth */
        if ( ( lc_stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {

            /* Verify path strings */
            if ( ( fsImAIPath != NULL ) && ( fsKeAIPath != NULL ) && ( fsImBIPath != NULL ) && ( fsKeBIPath != NULL ) && ( fsMatOPath != NULL ) ) {
    
                /* Read input image */
                fsImageA = cv::imread( fsImAIPath, CV_LOAD_IMAGE_GRAYSCALE );
                fsImageB = cv::imread( fsImBIPath, CV_LOAD_IMAGE_GRAYSCALE );

                /* Verify image reading */
                if ( ( fsImageA.data != NULL ) && ( fsImageB.data != NULL ) ) {

                    /* Keypoint vectors */
                    std::vector < cv::KeyPoint > fsKeyA = fs_matchSIFT_readkey( fsKeAIPath );
                    std::vector < cv::KeyPoint > fsKeyB = fs_matchSIFT_readkey( fsKeBIPath );

                    /* Verify keyfile reading */
                    if ( ( fsKeyA.size() > 0 ) && ( fsKeyB.size() > 0 ) ) {

                        /* Instance SIFT detector */
                        cv::SIFT fsSift;

                        /* Instance SIFT descriptor */
                        cv::Mat fsDescriptA, fsDescriptB;

                        /* Instance match feature */
                        cv::FlannBasedMatcher fsMatcher;

                        /* Instance matches array */
                        std::vector < cv::DMatch > fsMatches;

                        /* Compute images descriptors */
                        fsSift.compute( fsImageA, fsKeyA, fsDescriptA );
                        fsSift.compute( fsImageB, fsKeyB, fsDescriptB );

                        /* Compute matches */
                        fsMatcher.match( fsDescriptA, fsDescriptB, fsMatches );

                        /* Open output match file */
                        fsMatchfile.open( fsMatOPath );

                        /* Verify file openning */
                        if ( fsMatchfile.is_open() == true ) {

                            /* Export match count */
                            fsMatchfile << fsMatches.size() << std::endl;

                            /* Export match coordinates */
                            for ( unsigned int fsIndex( 0 ); fsIndex < fsMatches.size(); fsIndex ++ ) {

                                /* Export match index */
                                fsMatchfile << fsMatches[fsIndex].queryIdx << " "
                                            << fsMatches[fsIndex].trainIdx << " ";

                                /* Export match coordinates */
                                fsMatchfile << fsKeyA[fsMatches[fsIndex].queryIdx].pt.x << " " 
                                            << fsKeyA[fsMatches[fsIndex].queryIdx].pt.y << " "
                                            << fsKeyB[fsMatches[fsIndex].trainIdx].pt.x << " " 
                                            << fsKeyB[fsMatches[fsIndex].trainIdx].pt.y << std::endl;

                            }

                            /* Close file */
                            fsMatchfile.close();

                        /* Display message */
                        } else { std::cout << "Error : Unable to write output matchfile" << std::endl; }                

                    /* Display message */
                    } else { std::cout << "Error : Unable to read input keyfiles" << std::endl; }

                /* Display message */
                } else { std::cout << "Error : Unable to read input images" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Invalid path specification" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

/*
    Source - Read keypoint file
*/

    std::vector < cv::KeyPoint > fs_matchSIFT_readkey( char const * const fsKeyfile ) {

        /* Instance return variable */
        std::vector < cv::KeyPoint > fsKey;

        /* File stream variable */
        std::ifstream fsFile( fsKeyfile, std::ios::in );

        /* Size parameters */
        int fsRows ( 0 ), fsCols ( 0 );

        /* Reading variable */
        float fsX ( 0.0 ), fsY ( 0.0 ), fsSize ( 0.0 ), fsAngle ( 0.0 ), fsResponse ( 0.0 ), fsOctave ( 0.0 );

        /* Verify file */
        if ( fsFile.is_open() == true ) {

            /* Read parameters */
            fsFile >> fsRows >> fsCols;

            /* Reading keypoints */
            for ( int fsIndex( 0 ); fsIndex < fsRows; fsIndex ++ ) {

                /* Read keypoints */
                fsFile >> fsX >> fsY >> fsSize >> fsAngle >> fsResponse >> fsOctave;

                /* Push keypoint */
                fsKey.push_back( cv::KeyPoint( cv::Point2f( fsX, fsY ), fsSize, fsAngle, fsResponse, fsOctave ) );

            }

            /* Close stream */
            fsFile.close();

        }

        /* Return readed keypoints */
        return( fsKey );

    }

