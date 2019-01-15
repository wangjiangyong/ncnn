//
//  object.cpp
//  FaceTracking
//
//  Created by Menglong Yang on 2018/11/16.
//  Copyright © 2018 Menglong Yang. All rights reserved.
//

#include "object.hpp"

using namespace std;

using namespace cv;

Ptr<Tracker> createTracker(string trackerType)
{
#if (CV_MINOR_VERSION < 3)
    {
        tracker = Tracker::create(trackerType);
    }
#else
    Ptr<Tracker> tracker;
    if (trackerType ==  "BOOSTING")
        tracker = TrackerBoosting::create();
    else if (trackerType == "MIL")
        tracker = TrackerMIL::create();
    else if (trackerType == "KCF")
        tracker = TrackerKCF::create();
    else if (trackerType == "TLD")
        tracker = TrackerTLD::create();
    else if (trackerType == "MEDIANFLOW")
        tracker = TrackerMedianFlow::create();
    else if (trackerType == "GOTURN")
        tracker = TrackerGOTURN::create();
    else if (trackerType == "MOSSE")
        tracker = TrackerMOSSE::create();
    else if (trackerType == "CSRT")
        tracker = TrackerCSRT::create();
    else {
        cout << "Incorrect tracker name" << endl;
    }
#endif
    return tracker;
}

object:: object(std::string _id, InputArray image, const Rect2d& boundingBox, double _scale, std::string algorithm)
{
    status = 1;
    tracker_type = algorithm;
    scale = _scale;
    tracker = createTracker(tracker_type);
    Mat dst_img;
    Size rs = Size(int(1.0 / scale * image.cols()), int(1.0 / scale * image.rows()));
    resize(image, dst_img, rs);
    Rect2d bbox(boundingBox.x / scale, boundingBox.y / scale, boundingBox.width /scale, boundingBox.height / scale);
    tracker->init(dst_img, bbox);
    id = _id;

    lost_time = 0;
}

object:: ~object()
{
    status = 0;
    tracker.release();
}

void object::update(InputArray image)
{
    Mat dst_img;
    Size rs = Size(int(1.0 / scale * image.cols()), int(1.0 / scale * image.rows()));
    resize(image, dst_img, rs);
    
    bool success = tracker->update(dst_img, location);
    if (status == -1) {
        lost_time++;
        return;
    }
    
    if (success) {
        lost_time = 0;
        status = 2;
    }
    else {
        status = 0;
        lost_time++;
    }
}

void object::update(InputArray image, const cv::Rect2d& boundingBox)
{
    tracker.release();
    tracker = createTracker(tracker_type);
    Mat dst_img;
    Size rs = Size(int(1.0 / scale * image.cols()), int(1.0 / scale * image.rows()));
    resize(image, dst_img, rs);
    Rect2d bbox(boundingBox.x / scale, boundingBox.y / scale, boundingBox.width /scale, boundingBox.height / scale);
    tracker->init(dst_img, bbox);
    lost_time = 0;
    status = 1;
}
