/*
 * feature suite - Feature detection suite
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Stephane Flotron <s.flotron@foxel.ch>
 *
 * Contributor(s):
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

    # include "feature-match-ff.hpp"

/*
    Source - Entry point
 */

    int main( int argc, char ** argv ) {

        /* Path variables */
        char fsSMatchfile[256] = { 0 };
        char fsIMatchfile[256] = { 0 };
        char fsOMatchfile[256] = { 0 };

        /* Reading variables */
        int   fsCount  ( 0   );
        int   fsKeyIdx ( 0   );
        float fsKeyX   ( 0.0 );
        float fsKeyY   ( 0.0 );

        /* Sieve tolerence parameter */
        float fsTolerence ( 1.0 );

        /* Fundamental matrix condition */
        float fsCondition ( 0.0 );

        /* Fundamental matrix sieve variables */
        float fsEpiplA[3] = { 0.0 };
        float fsEpiplB[3] = { 0.0 };
        float fsPointA[3] = { 0.0 };
        float fsPointB[3] = { 0.0 };

        /* Match buffer */
        fs_Match_t fsBuffer = { };

        /* Strict matches arrays */
        std::vector < cv::Point2f > fsKeyA;
        std::vector < cv::Point2f > fsKeyB;

        /* Matches array */
        std::vector < fs_Match_t > fsIMatch;
        std::vector < fs_Match_t > fsOMatch;

        /* Fundamental matrix */
        cv::Mat fsFundmat;

        /* Stream variables */
        std::fstream fsStream;

        /* Arguments and parameters handle */
        lc_stdp( lc_stda( argc, argv, "--strict"   , "-s" ), argv,   fsSMatchfile, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--input"    , "-i" ), argv,   fsIMatchfile, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--output"   , "-o" ), argv,   fsOMatchfile, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--tolerance", "-t" ), argv, & fsTolerence , LC_FLOAT  );

        /* Software swicth */
        if ( ( lc_stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {

            /* Open strict match stream */
            fsStream.open( fsSMatchfile, std::ios::in );

            /* Check stream openning */
            if ( fsStream.is_open() == true ) {

                /* Read matches count */
                fsStream >> fsCount;

                /* Read matches coordinates and index */
                for ( int fsIndex( 0 ); fsIndex < fsCount; fsIndex ++ ) {

                    /* Read indexes (not used) */
                    fsStream >> fsKeyIdx >> fsKeyIdx;

                    /* Read first key parameters */
                    fsStream >> fsKeyX >> fsKeyY;

                    /* Push first key parameters */
                    fsKeyA.push_back( cv::Point2f( fsKeyX, fsKeyY ) );

                    /* Read second key parameters */
                    fsStream >> fsKeyX >> fsKeyY;

                    /* Push second key parameters */
                    fsKeyB.push_back( cv::Point2f( fsKeyX, fsKeyY ) );

                }

                /* Close input stream */
                fsStream.close();

                /* Check strict matches count */
                if ( fsCount >= 8 ) {

                    /* Compute fundamental matrix estimation */
                    fsFundmat = cv::findFundamentalMat( fsKeyA, fsKeyB, cv::FM_RANSAC, 1.0 , 0.99 );

                    /* Open input matches file */
                    fsStream.open( fsIMatchfile, std::ios::in );

                    /* Check stream openning */
                    if ( fsStream.is_open() == true ) {

                        /* Read matches count */
                        fsStream >> fsCount;

                        /* Read matches coordinates and index */
                        for ( int fsIndex( 0 ); fsIndex < fsCount; fsIndex ++ ) {

                            /* Read matches coordinates */
                            fsStream >> fsBuffer.ai >> fsBuffer.bi >> fsBuffer.ax >> fsBuffer.ay >> fsBuffer.bx >> fsBuffer.by; 

                            /* Push reading buffer */
                            fsIMatch.push_back( fsBuffer );

                        }

                        /* Close input stream */
                        fsStream.close();

                        /* Apply fundamental matrix sieve */
                        for ( unsigned int fsIndex( 0 ); fsIndex < fsIMatch.size(); fsIndex ++ ) {

                            /* Create homogenous vectors */
                            fsPointA[0] = fsIMatch[fsIndex].ax;
                            fsPointA[1] = fsIMatch[fsIndex].ay;
                            fsPointA[2] = 1.0;
                            fsPointB[0] = fsIMatch[fsIndex].bx;
                            fsPointB[1] = fsIMatch[fsIndex].by;
                            fsPointB[2] = 1.0;

                            /* Reset epipolar line coefficients */
                            fsEpiplA[0] = 0.0;
                            fsEpiplA[1] = 0.0;
                            fsEpiplA[2] = 0.0;
                            fsEpiplB[0] = 0.0;
                            fsEpiplB[1] = 0.0;
                            fsEpiplB[2] = 0.0;

                            /* Reset fundamental matrix condition */
                            fsCondition = 0.0;

                            /* Compute fundamental matrix condition and coefficients - Rows */
                            for ( int fsi ( 0 ); fsi < int( 3 ); fsi ++ ) {

                                /* Compute fundamental matrix condition and coefficients - Columns */
                                for ( int fsj ( 0 ); fsj < int( 3 ); fsj ++ ) {

                                    /* Fundamental matrix condition */
                                    fsCondition += fsPointB[fsi] * ( fsFundmat.at < double > ( fsi, fsj ) ) * fsPointA[fsj];

                                    /* Epipolar line coefficients */
                                    fsEpiplB[fsi] += ( fsFundmat.at < double > ( fsi, fsj ) ) * fsPointA[fsj];
                                    fsEpiplA[fsi] += ( fsFundmat.at < double > ( fsj, fsi ) ) * fsPointB[fsj];

                                }

                            }

                            /* Apply fundamental matrix sieve */
                            if ( ( ( fabs( fsCondition ) / sqrt( fsEpiplA[0] * fsEpiplA[0] + fsEpiplA[1] * fsEpiplA[1] ) ) <  fsTolerence ) &&
                                 ( ( fabs( fsCondition ) / sqrt( fsEpiplB[0] * fsEpiplB[0] + fsEpiplB[1] * fsEpiplB[1] ) ) <  fsTolerence ) ) {

                                /* Matches passed the fundamental matrix sieve */
                                fsOMatch.push_back( fsIMatch[fsIndex] );

                            }

                        }

                        /* Open output matches file */
                        fsStream.open( fsOMatchfile, std::ios::out );

                        /* Check stream openning */
                        if ( fsStream.is_open() == true ) {

                            /* Export matches count */
                            fsStream << fsOMatch.size() << std::endl;

                            /* Export matches coordinates and index */
                            for ( unsigned int fsIndex( 0 ); fsIndex < fsOMatch.size(); fsIndex ++ ) {

                                /* Export matches coordinates */
                                fsStream << fsOMatch[fsIndex].ai << " " 
                                         << fsOMatch[fsIndex].bi << " " 
                                         << fsOMatch[fsIndex].ax << " " 
                                         << fsOMatch[fsIndex].ay << " " 
                                         << fsOMatch[fsIndex].bx << " " 
                                         << fsOMatch[fsIndex].by << std::endl;

                            }    

                            /* Close output stream */
                            fsStream.close();

                            /* Display message */
                            std::cout << fsOMatch.size() << " matches have passed the sieve !" << std::endl;

                        /* Display message */
                        } else { std::cout << "Error : Unable to open output matches file" << std::endl; }

                    /* Display message */
                    } else { std::cout << "Error : Unable to open input matches file" << std::endl; }

                /* Display message */
                } else { std::cout << "Error : Not enough strict matches for matrix estimation" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Unable to open strict matches file" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

