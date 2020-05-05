#ifndef __STRUCTURED_LIGHT_HPP__
#define __STRUCTURED_LIGHT_HPP__

#include <opencv2/core/core.hpp>

#ifndef _MSC_VER
#  ifndef _isnan
#    include <math.h>
#    define _isnan std::isnan
#  endif
#endif

namespace sl
{
    enum DecodeFlags {SimpleDecode = 0x00, GrayPatternDecode = 0x01, RobustDecode = 0x02};

    extern const float PIXEL_UNCERTAIN;
    extern const unsigned short BIT_UNCERTAIN;

    bool decode_pattern(const std::vector<cv::Mat> & images, cv::Mat & pattern_image, cv::Mat & min_max_image, cv::Size const& projector_size,
                        unsigned flags = SimpleDecode, const cv::Mat & direct_light = cv::Mat(), unsigned m = 5);
    unsigned short get_robust_bit(unsigned value1, unsigned value2, unsigned Ld, unsigned Lg, unsigned m);
    void convert_pattern(cv::Mat & pattern_image, cv::Size const& projector_size, const int offset[2], bool binary);
    cv::Mat estimate_direct_light(const std::vector<cv::Mat> & images, float b);

    cv::Mat get_gray_image(cv::Mat img);
    static inline bool INVALID(float value) {return _isnan(value)>0;}
    static inline bool INVALID(const cv::Vec2f & pt) {return _isnan(pt[0]) || _isnan(pt[1]);}
    static inline bool INVALID(const cv::Vec3f & pt) {return _isnan(pt[0]) || _isnan(pt[1]) || _isnan(pt[2]);}

    int binaryToGray(int value);
    inline int binaryToGray(int value, unsigned offset);
    inline int grayToBinary(int value, unsigned offset);

    cv::Mat colorize_pattern(const cv::Mat & pattern_image, unsigned set, float max_value);
};

#endif //__STRUCTURED_LIGHT_HPP__
