/*
 * lung_detector.h
 *
 *  Created on: Feb 25, 2017
 *      Author: sara
 */

#ifndef LUNG_SEGMENTATOR_H_
#define LUNG_SEGMENTATOR_H_

#include "../lits_scan/lits_scan.h"
#include "lung_segmentator.cuh"

/******************************************************************************
 * LiTS_lung_segmentator a class for lungs segmentation.
 *
 * It has means of lungs segmentation.
 *
 * Attributes:
 *
 *      ds_factor: factor by which volume would be down-sampled
 *          for certain processing steps in order to reduce computational time
 *      lung_volume_th: lower threshold for both lungs in mm^3
 *      air_th: threshold below which everything is
 *          considered to be air
 *      lung_assumed_center_n: assumed normalized mass center
 *          of the both lungs together
 *      body_bounds_th: side, front and back body bounds thresholds
 *
 * Methods:
 *
 *      LiTS_lung_detector: default and one constructor with all
 *          parameters
 *      adjust_segmentation_parameters: adjust segmentation parameters to the
 *          properties of the input data
 *      lung_segmentation: method for extraction of the binary mask
 *          corresponding to the both lung wings
******************************************************************************/
class LiTS_lung_segmentator
{

private:

	unsigned int ds_factor[3] = {4, 4, 1};
	float lung_volume_th;
	float air_th;
	float lung_assumed_center_n[3] = {0.5, 0.6, 0.9};
	unsigned int body_bounds_th[3] = {20, 20, 20};

public:

	LiTS_lung_segmentator(float lung_volume_th_ = 100.0 * 100.0 * 50.0,
			              float air_th_=-0.49);

	LiTS_lung_segmentator(unsigned int *subsample_factor_,
			              float lung_volume_th_, float air_th_,
			              float *lung_assumed_center_n_,
			              unsigned int *body_bounds_th_);

	void adjust_segmentation_parameters(LiTS_scan *scan,
	                                    unsigned int *ds_factor,
	                                    float &lung_V_th_vox,
	                                    unsigned int *bbounds);

	void lung_segmentation(LiTS_scan *scan);

};


#endif /* LUNG_SEGMENTATOR_H_ */
