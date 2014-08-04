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

    # include "feature-file-concat.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path variables */
        char fsFileA[256] = { };
        char fsFileB[256] = { };
        char fsFileO[256] = { };

        /* Reading variables */
        int fsCountA ( 0 );
        int fsCountB ( 0 );

        /* Stream variables */
        std::fstream fsStreamA;
        std::fstream fsStreamB;
        std::fstream fsStreamO;

        /* Line buffer */
        std::string fsLine;

        /* Arguments and parameters handle */
        stdp( stda( argc, argv, "--input-a", "-a" ), argv, fsFileA, __STDP_STRING );
        stdp( stda( argc, argv, "--input-b", "-b" ), argv, fsFileB, __STDP_STRING );
        stdp( stda( argc, argv, "--output" , "-o" ), argv, fsFileO, __STDP_STRING );

        /* Software swicth */
        if ( stda( argc, argv, "--help", "-h" ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {

            /* Open input stream */
            fsStreamA.open( fsFileA, std::ios::in );

            /* Check stream openning */
            if ( fsStreamA.is_open() == true ) {

                /* Open input stream */
                fsStreamB.open( fsFileB, std::ios::in );

                /* Check stream openning */
                if ( fsStreamB.is_open() == true ) {

                    /* Open output stream */
                    fsStreamO.open( fsFileO, std::ios::out );

                    /* Check stream openning */
                    if ( fsStreamO.is_open() == true ) {
                
                        /* Read elements count */
                        std::getline( fsStreamA, fsLine ); fsCountA = std::stoi( fsLine );
                        std::getline( fsStreamB, fsLine ); fsCountB = std::stoi( fsLine );

                        /* Export concatenation count */
                        fsStreamO << fsCountA + fsCountB << std::endl;

                        /* Read matches coordinates */
                        for ( int fsIndex( 0 ); fsIndex < fsCountA; fsIndex ++ ) {

                            /* Import input file line */
                            std::getline( fsStreamA, fsLine );

                            /* Export line in output file */
                            fsStreamO << fsLine << std::endl;


                        }

                        /* Close input stream */
                        fsStreamA.close();

                        /* Read matches coordinates */
                        for ( int fsIndex( 0 ); fsIndex < fsCountB; fsIndex ++ ) {

                            /* Import input file line */
                            std::getline( fsStreamB, fsLine );

                            /* Export line in output file */
                            fsStreamO << fsLine << std::endl;


                        }

                        /* Close input stream */
                        fsStreamB.close();

                        /* Close output stream */
                        fsStreamO.close();

                        /* Display message */
                        std::cout << "Exported " << fsCountA + fsCountB << " in " << fsFileO << " output file" << std::endl;

                    /* Display message */
                    } else { std::cout << "Error : Unable to open output file" << std::endl; }

                /* Display message */
                } else { std::cout << "Error : Unable to open second input file" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Unable to open first input file" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }
