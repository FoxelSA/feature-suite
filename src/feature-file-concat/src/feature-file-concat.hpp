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

    /*! \file   feature-file-concat.hpp
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *  
     *  Software main header (single function software)
     */

    /*! \mainpage feature-file-concat
     *
     *  \section feature-suite
     *  \section _ Features detection suite
     *  
     *  The feature-suite provides tools in the context of automatic image matching.
     *  The suite is separated into small softwares that solve a specific part of
     *  the problem. It is designed so in order to perform research using each
     *  software as a brick of the overall solver.
     *
     *  \section Documentation
     *
     *  More documentation can be found on the wiki provided on the project github
     *  repository (https://github.com/FoxelSA/feature-suite/wiki).
     *
     *  \section Copyright
     * 
     *  Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch \n
     *  This program is part of the FOXEL project <http://foxel.ch>.
     *  
     *  Please read the COPYRIGHT.md file for more information.
     *
     *  \section License
     *
     *  This program is licensed under the terms of the GNU Affero General Public License
     *  v3 (GNU AGPL), with two additional terms. The content is licensed under the terms 
     *  of the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA) license.
     *
     *  You must read <http://foxel.ch/license> for more information about our Licensing
     *  terms and our Usage and Attribution guidelines.
     */

/* 
    Header - Include guard
 */

    # ifndef __FS_FILE_CONCAT__
    # define __FS_FILE_CONCAT__

/* 
    Header - Includes
 */

    # include <iostream>
    # include <fstream>
    # include <cstring>

/* 
    Header - Preprocessor definitions
 */

/* 
    Header - Preprocessor macros
 */

    /* Standard help */
    # define FS_HELP "Usage summary :\n\n"                    \
    "\tfeature-file-concat [Arguments] [Parameters] ...\n\n"  \
    "Short arguments and parameters summary :\n\n"            \
    "\t-a\tInput file\n"                                      \
    "\t-b\tInput file\n"                                      \
    "\t-o\tOutput file\n\n"                                   \
    "feature-file-concat - feature-suite\n"                   \
    "Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch\n"

    /* Define standard types */
    # define FS_NULL        0
    # define FS_STRING      1
    # define FS_CHAR        2
    # define FS_SHORT       3
    # define FS_INT         4
    # define FS_LONG        5
    # define FS_LLONG       6
    # define FS_UCHAR       7
    # define FS_USHORT      8
    # define FS_UINT        9
    # define FS_ULONG      10
    # define FS_ULLONG     11
    # define FS_FLOAT      12
    # define FS_DOUBLE     13

/* 
    Header - Typedefs
 */

/* 
    Header - Structures
 */

/* 
    Header - Function prototypes
 */

    /*! \brief Software main function (single function software)
     *  
     *  The main function frame follows : parameters are initialized and read. The
     *  two input file are openned and the output file is created. After size reading
     *  and concatenation result export, the input files line are copied in the output
     *  file.
     *  
     *  \param argc Standard main parameter
     *  \param argv Standard main parameter
     */

    int main ( int argc, char ** argv );

    /*! \brief Search agrument position in argv
     *  
     *  This function search in the argv string array the position of the argument
     *  defined through ltag/stag and return the index of the corresponding parameter
     *  in argv.
     *  
     *  \param argc Standard main parameter
     *  \param argv Standard main parameter
     *  \param ltag Long-form argument string (--argument)
     *  \param stag Short-form argument string (-a)
     *  \return Index of parameter in argv
     */

    int  stda ( int argc, char ** argv, const char * const ltag, const char * const stag );

    /*! \brief Parameter reader in argv
     *  
     *  This function interpret the parameter in the desired type and return it through
     *  the param variable. The argi variable is typically set using stda function. If
     *  argi is set to FS_NULL, the function does nothing.
     *  
     *  \param argi Index of the parameter in argv
     *  \param argv Standard main parameter
     *  \param param Pointer to the variable that recieve the parameter
     *  \param type Type to use for parameter interpretation
     */

    void stdp ( int argi, char ** argv, void * param, int type );

/*
    Header - Include guard
 */

    # endif


