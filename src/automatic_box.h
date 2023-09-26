#pragma once

#include "rotateInterface.h"
#include "det_timu_yolov5.hpp"
#include "cls_image_rotate_tal.hpp"

using namespace facethink;

#include <string>
#include <vector>

class AutomaticBox final{
private:
    std::vector<int>                  anchor_;  // 0-x; 1-y
    static std::string                rotation_model_;
    static std::string                rotation_trt_;
    static std::string                rotate_cfg_;
    static std::unique_ptr<jietiRotateModel> p_rotation_;
    static std::unique_ptr<rotateInterface>  p_rot_interface_;

public:
    AutomaticBox(){}
    ~AutomaticBox(){}

public:
    static bool Init();

    bool handler(cv::Mat &cv_image_);

};
