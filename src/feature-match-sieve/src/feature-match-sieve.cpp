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

    # include "feature-match-sieve.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path variables */
        char fsMatchfile[256] = { 0 };
        char fsSievefile[256] = { 0 };

        /* Reading variables */
        int fsCount ( 0 );

        /* Filters parameters */
        float fsStrength ( 1.0   );
        float fsMinimum  ( 10.0  );
        float fsMaximum  ( 100.0 );

        /* Matches reading buffer */
        fs_Match_t fsBuffer = { };

        /* Matches array variables */
        std::vector < fs_Match_t > fsMatch;

        /* Stream variables */
        std::fstream fsStream;

        /* Arguments and parameters handle */
        lc_stdp( lc_stda( argc, argv, "--input"   , "-i" ), argv,   fsMatchfile, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--output"  , "-o" ), argv,   fsSievefile, LC_STRING );
        lc_stdp( lc_stda( argc, argv, "--strenght", "-s" ), argv, & fsStrength , LC_FLOAT  );
        lc_stdp( lc_stda( argc, argv, "--minimum" , "-m" ), argv, & fsMinimum  , LC_FLOAT  );
        lc_stdp( lc_stda( argc, argv, "--maximum" , "-a" ), argv, & fsMaximum  , LC_FLOAT  );

        /* Software swicth */
        if ( ( lc_stda( argc, argv, "--help", "-h" ) ) || ( argc <= 1 ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {

            /* Open input stream */
            fsStream.open( fsMatchfile, std::ios::in );

            /* Check stream openning */
            if ( fsStream.is_open() == true ) {

                /* Read matches count */
                fsStream >> fsCount;

                /* Read matches coordinates */
                for ( int fsIndex( 0 ); fsIndex < fsCount; fsIndex ++ ) {

                    /* Read matches coordinates */
                    fsStream >> fsBuffer.ai >> fsBuffer.bi >> fsBuffer.ax >> fsBuffer.ay >> fsBuffer.bx >> fsBuffer.by; 

                    /* Push reading buffer */
                    fsMatch.push_back( fsBuffer );

                }

                /* Close input stream */
                fsStream.close();

                /* Switch filters */
                if ( lc_stda( argc, argv, "--stat-dist", "-r" ) ) {

                    /* Statistical distance */
                    fsMatch = fs_matchSIEVE_stat_dist( fsMatch, fsStrength );

                } else if ( lc_stda( argc, argv, "--thre-dist", "-t" ) ) {

                    /* Threshold distance */
                    fsMatch = fs_matchSIEVE_thre_dist( fsMatch, fsMinimum, fsMaximum );

                } else if ( lc_stda( argc, argv, "--stat-disp", "-d" ) ) {

                    /* Statistical displacement */
                    fsMatch = fs_matchSIEVE_stat_disp( fsMatch, fsStrength );

                } else if ( lc_stda( argc, argv, "--stat-flow", "-f" ) ) {

                    /* Statistical displacement */
                    fsMatch = fs_matchSIEVE_stat_flow( fsMatch, fsStrength );

                } else if ( lc_stda( argc, argv, "--dich-slop", "-l" ) ) {

                    /* Statistical displacement */
                    fsMatch = fs_matchSIEVE_dich_slop( fsMatch );

                }

                /* Open output stream */
                fsStream.open( fsSievefile, std::ios::out );

                /* Check stream openning */
                if ( fsStream.is_open() == true ) {

                    /* Export matches count */
                    fsStream << fsMatch.size() << std::endl;

                    /* Export matches coordinates and index */
                    for ( unsigned int fsIndex( 0 ); fsIndex < fsMatch.size(); fsIndex ++ ) {

                        /* Export matches coordinates */
                        fsStream << fsMatch[fsIndex].ai << " " 
                                 << fsMatch[fsIndex].bi << " " 
                                 << fsMatch[fsIndex].ax << " " 
                                 << fsMatch[fsIndex].ay << " " 
                                 << fsMatch[fsIndex].bx << " " 
                                 << fsMatch[fsIndex].by << std::endl;

                    }

                    /* Close output stream */
                    fsStream.close();

                    /* Display message */
                    std::cout << fsMatch.size() << " matches have passed the sieve !" << std::endl;


                /* Display message */
                } else { std::cout << "Error : Unable to open output file" << std::endl; }

            /* Display message */
            } else { std::cout << "Error : Unable to open input file" << std::endl; }

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

/*
    Source - Statistical distance filter
 */

    std::vector < fs_Match_t > fs_matchSIEVE_stat_dist( std::vector < fs_Match_t > const fsRaw, float const fsStrength ) {

        /* Instance return variable */
        std::vector < fs_Match_t > fsSieve;

        /* Instance distance vector */
        std::vector < float > fsDist;

        /* Statistical quantities variables */
        float fsMean ( 0.0 );
        float fsStdd ( 0.0 );

        /* Compute distances */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ )

            /* Push current distance */
            fsDist.push_back( FS_DIST( fsRaw[fsIndex] ) );

        /* Compute statistical quantities */
        fsMean = LC_VMEAN( fsDist );
        fsStdd = LC_VSTDD( fsDist, fsMean );

        /* Statistical distance filter */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ )

            /* Apply sieve */
            if ( ( fsDist[fsIndex] - fsMean ) < fsStrength * fsStdd ) fsSieve.push_back( fsRaw[fsIndex] );

        /* Return filtered matches */
        return( fsSieve );

    }

/*
    Source - Threshold distance filter
 */

    std::vector < fs_Match_t > fs_matchSIEVE_thre_dist( std::vector < fs_Match_t > const fsRaw, float const fsMininum, float const fsMaximum ) {

        /* Instance return variable */
        std::vector < fs_Match_t > fsSieve;

        /* Threshold distance filter */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ )

            /* Apply sieve */
            if ( ( FS_DIST( fsRaw[fsIndex] ) > fsMininum ) && 
                 ( FS_DIST( fsRaw[fsIndex] ) < fsMaximum ) ) fsSieve.push_back( fsRaw[fsIndex] );

        /* Return filtered matches */
        return( fsSieve );

    }

/*
    Source - Statistical displacement filter
 */

    std::vector < fs_Match_t > fs_matchSIEVE_stat_disp( std::vector < fs_Match_t > const fsRaw, float const fsStrength ) {

        /* Instance return variable */
        std::vector < fs_Match_t > fsSieve;

        /* Instance distance vector */
        std::vector < float > fsDispX;
        std::vector < float > fsDispY;

        /* Statistical quantities variables */
        float fsMeanX ( 0.0 );
        float fsMeanY ( 0.0 );
        float fsStddX ( 0.0 );
        float fsStddY ( 0.0 );

        /* Compute displacement */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ ) {

            /* Push current distance */
            fsDispX.push_back( fabs( fsRaw[fsIndex].ax - fsRaw[fsIndex].bx ) );
            fsDispY.push_back( fabs( fsRaw[fsIndex].ay - fsRaw[fsIndex].by ) );

        }

        /* Compute statistical quantities */
        fsMeanX = LC_VMEAN( fsDispX );
        fsMeanY = LC_VMEAN( fsDispY );
        fsStddX = LC_VSTDD( fsDispX, fsMeanX );
        fsStddY = LC_VSTDD( fsDispY, fsMeanY );

        /* Statistical distance filter */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ )

            /* Apply sieve */
            if ( ( ( fsDispX[fsIndex] - fsMeanX ) < fsStrength * fsStddX ) && 
                 ( ( fsDispY[fsIndex] - fsMeanY ) < fsStrength * fsStddY ) ) fsSieve.push_back( fsRaw[fsIndex] );

        /* Return filtered matches */
        return( fsSieve );

    }

/*
    Source - Statistical flow filter
 */

    std::vector < fs_Match_t > fs_matchSIEVE_stat_flow( std::vector < fs_Match_t > const fsRaw, float const fsStrength ) {

        /* Instance return variable */
        std::vector < fs_Match_t > fsSieve;

        /* Instance distance vector */
        std::vector < float > fsDispX;
        std::vector < float > fsDispY;

        /* Statistical quantities variables */
        float fsMeanX ( 0.0 );
        float fsMeanY ( 0.0 );
        float fsStddX ( 0.0 );
        float fsStddY ( 0.0 );

        /* Compute displacement */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ ) {

            /* Push current distance */
            fsDispX.push_back( fabs( fsRaw[fsIndex].ax - fsRaw[fsIndex].bx ) / FS_DIST( fsRaw[fsIndex] ) );
            fsDispY.push_back( fabs( fsRaw[fsIndex].ay - fsRaw[fsIndex].by ) / FS_DIST( fsRaw[fsIndex] ) );

        }

        /* Compute statistical quantities */
        fsMeanX = LC_VMEAN( fsDispX );
        fsMeanY = LC_VMEAN( fsDispY );
        fsStddX = LC_VSTDD( fsDispX, fsMeanX );
        fsStddY = LC_VSTDD( fsDispY, fsMeanY );

        /* Statistical distance filter */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ )

            /* Apply sieve */
            if ( ( ( fsDispX[fsIndex] - fsMeanX ) < fsStrength * fsStddX ) && 
                 ( ( fsDispY[fsIndex] - fsMeanY ) < fsStrength * fsStddY ) ) fsSieve.push_back( fsRaw[fsIndex] );

        /* Return filtered matches */
        return( fsSieve );

    }

/*
    Source - Dichotomous slope filter
 */

    std::vector < fs_Match_t > fs_matchSIEVE_dich_slop( std::vector < fs_Match_t > const fsRaw ) {

        /* Instance return variable */
        std::vector < fs_Match_t > fsSieve;

        /* Instance differentials */
        std::vector < float > fsDiffX;
        std::vector < float > fsDiffY;

        /* Statistical variables */
        int fsMeanX ( 0.0 );
        int fsMeanY ( 0.0 );

        /* Compute dichotomous filter */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ ) {

            /* Push differentials */
            fsDiffX.push_back( fsRaw[fsIndex].ax - fsRaw[fsIndex].bx );
            fsDiffY.push_back( fsRaw[fsIndex].ay - fsRaw[fsIndex].by );

        }

        /* Compute differential mean signs */
        fsMeanX = LC_SIGN( LC_VMEAN( fsDiffX ) );
        fsMeanY = LC_SIGN( LC_VMEAN( fsDiffY ) );

        /* Dichotomous slope filter */
        for ( unsigned int fsIndex( 0 ); fsIndex < fsRaw.size(); fsIndex ++ ) {

            /* Apply sieve */
            if ( ( LC_SIGN( fsDiffX[fsIndex] ) == fsMeanX ) && 
                 ( LC_SIGN( fsDiffY[fsIndex] ) == fsMeanY ) ) {

                /* Sieve passed */
                fsSieve.push_back( fsRaw[fsIndex] );

            }

        }
        
        /* Return filtered matches */
        return( fsSieve );

    }

