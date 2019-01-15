//
//  main.cpp
//  FaceTracking
//
//  Created by Menglong Yang on 2018/11/13.
//  Copyright © 2018 Menglong Yang. All rights reserved.
//

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cstdio>

#include "tracking.h"
#include <pthread.h>
#include "net.h"

using namespace cv;
using namespace std;

/* 参数 : 输入图像、级联分类器、缩放倍数 */
void Detect( Mat& img, vector<Rect_<float>>& faces, ncnn::Extractor& ex );
void Draw( Mat& img, const vector<Rect>& faces);

int main()
{   
    ncnn::Net mobilenet;   
    mobilenet.load_param("face_det_120000.param");
    mobilenet.load_model("face_det_120000.bin");
    ncnn::Extractor ex = mobilenet.create_extractor();
    ex.set_num_threads(2);

    
    int max_history_length = 30;
    double image_scale = 16;
    // Create multitracker
    Tracking tracker(max_history_length, image_scale, "MEDIANFLOW");
    

    VideoCapture capture(0);
    //capture.open(0);
    if(!capture.isOpened()){
        cout << "open camera failed. " << endl;
        return -1;
    }
    
    
    Mat frame;
    
    //int iter = 0;
    while(true)
    {
        capture >> frame;
        if (frame.empty()){
            printf("empty frame!!!\n");
            continue;
        }
        vector<Rect_<float>> faces;
        Mat frame1 = frame.clone();
        bool success = false;
        bool notMatch = true;
        Detect(frame1, faces, ex);
        for(size_t jj=0; jj< faces.size();jj++)
                rectangle(frame1, faces[jj], Scalar(255, 0, 0));
        // if (iter++ % 10 == 0  ) {
        //     //double timer = (double)getTickCount();
        //     Detect(frame1, faces, ex);
        //     for(int jj=0; jj< faces.size();jj++)
        //         rectangle(frame1, faces[jj], Scalar(255, 0, 0), 2, 8);
        //     success = tracker.track(frame1, faces);
        //     // Calculate Frames per second (FPS)
        //     //float fps = getTickFrequency() / ((double)getTickCount() - timer);
        //     //printf( "detect speed = %g fps\n", fps);
        //     //notMatch =false;
        // }
        // else {
        //     // Update the tracking result
        //     //double timer = (double)getTickCount();
        //     success = tracker.track(frame1);
        //     // Calculate Frames per second (FPS)
        //     //float fps = getTickFrequency() / ((double)getTickCount() - timer);
        //     //printf( "tracking speed = %g fps\n", fps);
        // }
        
        // if (success) {
        //     const list<object*> objects = tracker.getObjects();
        //     list<object*>::const_iterator iter_obj = objects.begin();
        //     printf("wjy -debugx %d ",objects.size());
        //     for(iter_obj = objects.begin(); iter_obj != objects.end(); iter_obj++) {
        //         printf("wjy -debug %d ",(*iter_obj)->getStatus());
        //         if ((*iter_obj)->isTracked()) {
        //             Rect2d bbox = (*iter_obj)->getLocation();
        //             const string& id = (*iter_obj)->getID();
        //             int status = (*iter_obj)->getStatus();
        //             if (status==1) {
        //                 putText(frame1, id, Point(bbox.x, bbox.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 255, 0), 8);
        //                 rectangle(frame1, bbox, Scalar(0, 255, 0), 2, 8);
                        
        //             }
        //             else {
        //                 //printf("---wjy debug \n");
        //                 putText(frame1, id, Point(bbox.x, bbox.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255,0,0), 8);
        //                 rectangle(frame1, bbox, Scalar(255, 0, 0), 2, 8);
        //             }
        //         }
        //         else{
        //             notMatch = true;
        //         }
        //     }
        // }
        
        cv::imshow( "FaceDetect", frame1);    // 显示
        if(waitKey(5) > 0)   break;     // delay ms 等待按键退出
    }
    return 0;
}

void Detect( Mat& bgr, vector<Rect_<float>>& faces, ncnn::Extractor& ex )
{  
    const int target_size = 300;

    int img_w = bgr.cols;
    int img_h = bgr.rows;

    ncnn::Mat in = ncnn::Mat::from_pixels_resize(bgr.data, ncnn::Mat::PIXEL_BGR, bgr.cols, bgr.rows, target_size, target_size);
    
    const float mean_vals[3] = {127.5f, 127.5f, 127.5f};
    const float norm_vals[3] = {1.0/127.5,1.0/127.5,1.0/127.5};
    in.substract_mean_normalize(mean_vals, norm_vals);

    ex.input("data", in);

    ncnn::Mat out;
    ex.extract("detection_out",out);

    faces.clear();
    
    for (int i=0; i<out.h; i++)
    {
        const float* values = out.row(i);
        //if(values[1]<0.4)  //without objects of low probability
           //continue;
        Rect_<float> face;
        face.x = values[2] * img_w ;
        face.y = values[3] * img_h ;
        face.width = values[4] * img_w - face.x;
        face.height = values[5] * img_h  - face.y;
        printf("fuck frame!!!\n");
        printf("%f %f %f %f \n",values[2],values[3],values[4],values[5]);
        //printf("%f %f %f %f \n",float(face.x),float(face.y),float(face.width),float(face.height));
        faces.push_back(face);
    }


}

void Draw( Mat& img, const vector<Rect>& faces)
{
    /* 画矩形框出目标 */
    for ( size_t i = 0; i < faces.size(); i++ ) // faces.size():检测到的目标数量
    {
        Rect rectFace = faces[i];   
        rectangle(img, Point(rectFace.x, rectFace.y) ,Point(rectFace.x + rectFace.width, rectFace.y + rectFace.height) ,Scalar(0, 255, 0), 2, 8);
    }
    
    imshow( "FaceDetect", img );    // 显示
}
