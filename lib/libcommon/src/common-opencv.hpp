/*
 * feature-suite libcommon - feature-suite common library
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

    /*! \file   common-opencv.hpp
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  OpenCV function interface
     */

/* 
    Header - Include guard
 */

    # ifndef __LC_OPENCV__
    # define __LC_OPENCV__

/* 
    Header - Includes
 */

    # include "common.hpp"
    # include <opencv2/opencv.hpp>
    # include <opencv2/highgui/highgui_c.h>

/* 
    Header - Preprocessor definitions
 */

/* 
    Header - Preprocessor macros
 */

/* 
    Header - Typedefs
 */

/* 
    Header - Structures
 */

/* 
    Header - Function prototypes
 */

    /*! \brief Image exportation interface
     *
     *  This function is a simple front end to the OpenCV image exportation
     *  function. It simply takes care of specific options that can be passed to
     *  the OpenCV function according to the image format such as compression
     *  or quality. The determination of the output format is made on the basis
     *  of the file extention.
     *
     *  \param  lcPath          Image exportation path
     *  \param  lcImage         Image to export
     *  \param  lcOption        Image exportation options
     *
     *  \return The function returns true if the exportation succeed, false
     *  otherwise - repport OpenCV function value
     */    

    bool lc_imwrite ( char * lcPath, cv::Mat lcImage, int lcOption );

    /*! \brief Image exportation methods
     *
     *  This function uses the OpenCV exportation method to export the provided
     *  image in JPEG format using the specified quality value. The JPEG quality
     *  value has to be between 0 and 100.
     *
     *  \param  lcPath          Image exportation path
     *  \param  lcImage         Image to export
     *  \param  lcQuality       JPEG image quality
     *
     *  \return The function returns true if the exportation succeed, false
     *  otherwise - repport OpenCV function value
     */

    bool lc_imwrite_jpeg ( char * lcPath, cv::Mat lcImage, int lcQuality );

    /*! \brief Image exportation methods
     *
     *  This function uses the OpenCV exportation method to export the provided
     *  image in PNG format using the specified compression value. The PNG
     *  compression value has to be between 0 and 9.
     *
     *  \param  lcPath          Image exportation path
     *  \param  lcImage         Image to export
     *  \param  lcCompression   JPEG image quality
     *
     *  \return The function returns true if the exportation succeed, false
     *  otherwise - repport OpenCV function value
     */

    bool lc_imwrite_png ( char * lcPath, cv::Mat lcImage, int lcCompression );

/*
    Header - Include guard
 */

    # endif

