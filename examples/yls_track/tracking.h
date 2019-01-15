//
//  tracking.hpp
//  FaceTracking
//
//  Created by Menglong Yang on 2018/11/16.
//  Copyright © 2018 Menglong Yang. All rights reserved.
//

#ifndef tracking_hpp
#define tracking_hpp

#include <stdio.h>
#include <opencv2/tracking.hpp>
#include "object.hpp"
#include <map>
#include <list>

using namespace cv;

/************************************ MultiTracker Class ---By Menglong Yang---) ************************************/
/** @brief This class is used to track multiple objects using the specified tracker algorithm.
 * The Tracking is naive implementation of multiple object tracking based on OpenCV.
 * It process the tracked objects independently without any optimization accross the tracked objects.
 */
class Tracking
{
public:
    
    Tracking(int _max_history_size = 30, double scale = 16.0, std::string algorithm = "MEDIANFLOW", int _max_object_num=0);
    ~Tracking();
    
    /**
     * \brief Update the current tracking status.
     * The result will be saved in the internal storage.
     * @param image input image
     */
    bool track(InputArray image);
    
    /**
     * \brief Update the current tracking status.
     * @param image input image
     * @param boundingBox the tracking result, represent a list of ROIs of the tracked objects.
     */
    
    bool track(InputArray image, std::vector<Rect2d> & boundingBox);
    bool track(InputArray image, std::vector<Rect> & boundingBox);
    
    /**
     * \brief Returns a reference to a storage for the tracked objects, each object corresponds to one tracker algorithm
     */
    const std::list< object* >& getObjects() const;
    
private:
    /**
     * \brief Add a new object to be tracked.
     *
     * @param object_id identity of object
     * @param image input image
     * @param boundingBox a rectangle represents ROI of the tracked object
     */
    bool add(std::string object_id, InputArray image, const Rect2d& boundingBox);
    
    
    //!<  storage for the objects.
    std::list< object* > objectList;
    
    /**
     * How many history points to keep track of.
     */
    int max_history_size;
    
    std::string trackerType;
    
    int iter;
    double scale;
    int max_object_num;
    
};


#endif /* tracking_hpp */
