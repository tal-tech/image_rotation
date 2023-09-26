#include "automatic_box.h"

#include <mutex>
std::mutex rotation_mutex;

std::string AutomaticBox::rotation_model_;
std::string AutomaticBox::rotation_trt_;
std::string AutomaticBox::rotate_cfg_;
std::unique_ptr<jietiRotateModel> AutomaticBox::p_rotation_ = nullptr;
std::unique_ptr<rotateInterface> AutomaticBox::p_rot_interface_ = nullptr;

bool AutomaticBox::Init() {
    // 旋转模型
    rotation_model_ = "/home/guoweiye/roration_model/src/alg/model/cls_image_rotate_v1.0.0.onnx";
    rotation_trt_   = "/home/guoweiye/roration_model/src/alg/model/cls_image_rotate_v1.0.0.trt";
    rotate_cfg_     = "/home/guoweiye/roration_model/src/alg/model/config.ini";

    // init algorithm model
    if (nullptr == p_rotation_) {
        p_rotation_.reset(new jietiRotateModel());
        if (nullptr != p_rotation_) {
            p_rotation_->Init(rotation_model_, rotate_cfg_);
        } else {
            std::cout << "rotate model init failed" << std::endl;
        }
    }
    // 旋转接口是否创建
    if (nullptr == p_rot_interface_) {
        p_rot_interface_.reset(new rotateInterface());
    }
    return true;
}

bool AutomaticBox::handler(cv::Mat &cv_image_) {

    // TODO: 业务处理及调用模型等，下面是模拟输出结果

    int angle_index = 0;
    std::unique_lock<std::mutex> lock(rotation_mutex);
    std::vector<float> vec_probs;
    // 旋转函数调用
    {
        p_rot_interface_->getAngle(p_rotation_.get(), cv_image_, angle_index, vec_probs);
    }

    // 旋转校验
    if(cv_image_.cols == 0)
        return false;

    if ((cv_image_.rows / cv_image_.cols) >= 5) {
        return  false;
    }
    if (cv_image_.rows <= 1440) {
        if ((cv_image_.rows / cv_image_.cols) > 5) {
            return  false;
        }
    }

    if ((cv_image_.rows > 1440) && (cv_image_.rows < 5000)) {
        if ((cv_image_.rows / cv_image_.cols) >= 5) {
            return  false;
        }
        if ((cv_image_.rows / cv_image_.cols) > 3 && (cv_image_.rows / cv_image_.cols) < 5 && (cv_image_.cols > 720)) {
            return  false;
        }
    }
    return true;
}

int main()
{
    AutomaticBox rorat;

    // init model
    if(!rorat.Init()){
        std::cout<<"start roration_model failed"<<std::endl;
        return -1;
    }
    
    // read picture
    cv::Mat image = cv::imread("./image.jpg");
    
    if(!image.data){
        std::cerr<<"read image error"<<std::endl;
        return -1;
    }
    
    if(rorat.handler(image)){
        std::cout<<"rotate image successfully"<<std::endl;
    }
    else{
        std::cout<<"rotate image failed"<<std::endl;
        return -1;
    }

    return 0;
}
