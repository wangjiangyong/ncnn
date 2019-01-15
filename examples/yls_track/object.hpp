//
//  object.hpp
//  FaceTracking
//
//  Created by Menglong Yang on 2018/11/16.
//  Copyright © 2018 Menglong Yang. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

#include <stdio.h>
#include <opencv2/tracking.hpp>
#include <map>

class object {
    std::string id;
    
    cv::Rect2d location;
    
    //!<  each object corresponds to one tracker algorithm.
    cv::Ptr<cv::Tracker> tracker;
    
    int lost_time;
    
    std::string tracker_type;
    
    int status; // 0 denotes the object is lost, 1 denotes the object is detected, 2 denotes the object is tracked, -1 denotes the object is not matched with any object detected out by the detector
    
    double scale; // scale the input image for fast runtime
        
public:
    object(std::string _id, cv::InputArray& image, const cv::Rect2d& boundingBox, double scale, std::string algorithm);  //wjy
    void update(cv::InputArray& image);  //wjy
    void update(cv::InputArray& image, const cv::Rect2d& boundingBox);  //wjy
    bool lost_too_long(int expiration=5)
    {
        return lost_time > expiration; 
    };

    bool isTracked() {return status > 0; };
    int getStatus() {return status; };
    const cv::Rect2d getLocation()
    {
        return cv::Rect2d(location.x * scale, location.y * scale, location.width * scale, location.height * scale); 
    };
    const std::string& getID() {return id; };
    
    void setStatus(int _status)
    {
        status = _status; 
    };
    
    ~object();
};

#endif /* object_hpp */
