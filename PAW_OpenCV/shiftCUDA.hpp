/*
*  Software License Agreement (BSD License)
*
*  Copyright (c) 2012, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
*  File:    shift.hpp
*  Author:  Hilton Bristow
*  Created: Aug 23, 2012
*/

#ifndef SHIFTCUDA_HPP_
#define SHIFTCUDA_HPP_

#include <limits>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>

/*! @brief shift the values in a matrix by an (x,y) offset
*
* Given a matrix and an integer (x,y) offset, the matrix will be shifted
* such that:
*
* 	src(a,b) ---> dst(a+y,b+x)
*
* In the case of a non-integer offset, (e.g. cv::Point2f(-2.1, 3.7)),
* the shift will be calculated with subpixel precision using bilinear
* interpolation.
*
* All valid OpenCV datatypes are supported. If the source datatype is
* fixed-point, and a non-integer offset is supplied, the output will
* be a floating point matrix to preserve subpixel accuracy.
*
* All border types are supported. If no border type is supplied, the
* function defaults to BORDER_CONSTANT with 0-padding.
*
* The function supports in-place operation.
*
* Some common examples are provided following:
* \code
* 	// read an image from file
* 	Mat mat = imread(filename);
* 	Mat dst;
*
* 	// Perform Matlab-esque 'circshift' in-place
* 	shift(mat, mat, Point(5, 5), BORDER_WRAP);
*
* 	// Perform shift with subpixel accuracy, padding the missing pixels with 1s
* 	// NOTE: if mat is of type CV_8U, then it will be converted to type CV_32F
* 	shift(mat, mat, Point2f(-13.7, 3.28), BORDER_CONSTANT, 1);
*
* 	// Perform subpixel shift, preserving the boundary values
* 	shift(mat, dst, Point2f(0.093, 0.125), BORDER_REPLICATE);
*
* 	// Perform a vanilla shift, integer offset, very fast
* 	shift(mat, dst, Point(2, 2));
* \endcode
*
* @param src the source matrix
* @param dst the destination matrix, can be the same as source
* @param delta the amount to shift the matrix in (x,y) coordinates. Can be
* integer of floating point precision
* @param fill the method used to fill the null entries, defaults to BORDER_CONSTANT
* @param value the value of the null entries if the fill type is BORDER_CONSTANT
*/
void shiftCUDA(const cv::cuda::GpuMat& src, cv::cuda::GpuMat& dst, cv::Point2f delta, int fill = cv::BORDER_CONSTANT, cv::Scalar value = cv::Scalar(0, 0, 0, 0));


#endif /* SHIFTCUDA_HPP_ */