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

    # include "feature-key-scale.hpp"

/*
    Source - Entry point
 */

    int main ( int argc, char ** argv ) {

        /* Path strings */
        char  fsKeyIPath[256] = { '\0' };
        char  fsKeyOPath[256] = { '\0' };

        /* Parameters variables */
        float fsScale = 1.0;

        /* Keypoint structure size variables */
        int   fsRows = 0;

        /* Keypoint parameters variables */
        float fsX = 0.0;
        float fsY = 0.0;
        float fsSize = 0.0;
        float fsAngle = 0.0;
        float fsResponse = 0.0;
        float fsOctave = 0.0;

        /* Stream variables */
        std::fstream fsIStream;
        std::fstream fsOStream;

        /* Search in parameters */
        stdp( stda( argc, argv, "--input" , "-i" ), argv,   fsKeyIPath, __STDP_STRING );
        stdp( stda( argc, argv, "--output", "-o" ), argv,   fsKeyOPath, __STDP_STRING );
        stdp( stda( argc, argv, "--scale" , "-s" ), argv, & fsScale   , __STDP_FLOAT  );

        /* Software swicth */
        if ( stda( argc, argv, "--help", "-h" ) ) {

            /* Display message */
            std::cout << FS_HELP;

        } else {

            /* Open keypoint files */
            fsIStream.open( fsKeyIPath, std::ios::in  );
            fsOStream.open( fsKeyOPath, std::ios::out );

            /* Read parameters */
            fsIStream >> fsRows;

            /* Export parameters */
            fsOStream << fsRows << std::endl;

            /* Reading keypoints */
            for ( int fsIndex = 0; fsIndex < fsRows; fsIndex ++ ) {

                /* Read keypoints */
                fsIStream >> fsX >> fsY >> fsSize >> fsAngle >> fsResponse >> fsOctave;

                /* Write scaled keypoints */
                fsOStream << fsX * fsScale << " " << fsY * fsScale << " " << fsSize * fsScale << " " << fsAngle << " " << " " << fsResponse << " " << fsOctave << std::endl;

            }

            /* Close streams */
            fsIStream.close();
            fsOStream.close();

            /* Display message */
            std::cout << fsRows << " keypoints have been scaled" << std::endl;

        }

        /* Return to system */
        return( EXIT_SUCCESS );

    }

