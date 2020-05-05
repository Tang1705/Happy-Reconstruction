#include "Calibrator.h"
#include "structured_light.h"
#include "CalibrationData.h"

#include <fstream>

#include <QtCore/QList>

Calibrator::Calibrator()
{

}

Calibrator::~Calibrator()
{

}

void Calibrator::addFrameSequence(std::vector<cv::Mat> &frameSeq)
{
    int n = frameSeqs.size();
    frameSeqs.resize(n+1);
    std::vector<cv::Mat> &frame = frameSeqs[n];
    for(int i = 0; i < frameSeq.size(); i++)
    {
        frame.push_back(frameSeq[i]);
    }
	std::cout <<"Calibrator::addFrameSequence : frame.size(): "<< frame.size() << std::endl;
}

void Calibrator::reset()
{
    frameSeqs.clear();
    board_corners.clear();
    projector_corners.clear();
    pattern_list.clear();
}

void Calibrator::setBoardRows(int rows) {
    board_rows = rows;
    board_size = cv::Size(board_rows, board_cols);
}

void Calibrator::setBoardCols(int cols) {
    board_cols = cols;
    board_size = cv::Size(board_rows, board_cols);
}

void Calibrator::setCornerSize(double cornerSize) {
    dot_dis = cornerSize;
    corner_size = cv::Size2f(cornerSize, cornerSize);
}

void Calibrator::setDotDiameter(double dotDiameter) {
    dot_diameter = dotDiameter;
}
void Calibrator::setCalibBoard(unsigned board) {
    board_type = board;
}

CalibrationData* Calibrator::calibrate()
{

    CalibrationData  *res = new CalibrationData();

//    detect corners ////////////////////////////////////
    for(int i = 0; i < frameSeqs.size(); i++)
    {
        std::vector<cv::Point2f> corners = extract_board_corners( frameSeqs[i][0] );
        board_corners.push_back(corners);
//        std::cout<<i<<" corners: "<<corners.size()<<std::endl;
//        for(int j = 0; j < corners.size(); j++) {
//            std::cout<<corners[j]<<std::endl;
//        }
    }

//    collect projector correspondences
    std::vector<cv::Point2f> pcorners;
    for(int i = 0; i < frameSeqs.size(); i++)
    {
        std::vector<cv::Point2f> const& corners = board_corners[i];
        cv::Mat pattern_image;
        cv::Mat min_max_image;
        if(corners.size()==0)
        {
            projector_corners.push_back(pcorners);
            pattern_list.push_back(pattern_image);
            continue;
        }
        if(!decode_gray_set(i , pattern_image  ,min_max_image))
        {
            projector_corners.push_back(pcorners);
            pattern_list.push_back(pattern_image);
            continue;
        }

        pattern_list.push_back(pattern_image);
        for (std::vector<cv::Point2f>::const_iterator iter=corners.begin(); iter!=corners.end(); iter++)
        {
            const cv::Point2f & p = *iter;
            cv::Point2f q;
            //find an homography around p
            unsigned WINDOW_SIZE = 30;
            std::vector<cv::Point2f> img_points , proj_points;
            if (p.x>WINDOW_SIZE && p.y>WINDOW_SIZE && p.x+WINDOW_SIZE<pattern_image.cols && p.y+WINDOW_SIZE<pattern_image.rows)
            {
                for (unsigned h=p.y-WINDOW_SIZE; h<p.y+WINDOW_SIZE; h++)
                {
                    register const cv::Vec2f * row = pattern_image.ptr<cv::Vec2f>(h);
                    register const cv::Vec2b * min_max_row = min_max_image.ptr<cv::Vec2b>(h);
                    //cv::Vec2f * out_row = out_pattern_image.ptr<cv::Vec2f>(h);
                    for (unsigned w=p.x-WINDOW_SIZE; w<p.x+WINDOW_SIZE; w++)
                    {
                        const cv::Vec2f & pattern = row[w];
                        const cv::Vec2b & min_max = min_max_row[w];
                        //cv::Vec2f & out_pattern = out_row[w];
                        if (std::isnan(pattern[0])>0 || std::isnan(pattern[1])>0)
                        {
                            continue;
                        }
                        if ((min_max[1]-min_max[0]) < static_cast<int>(threshold))
                        {   //apply threshold and skip
                            continue;
                        }

                        img_points.push_back(cv::Point2f(w,  h));
                        proj_points.push_back(cv::Point2f(pattern));

                        //out_pattern = pattern;
                    }
                }
                cv::Mat H = cv::findHomography(img_points , proj_points, cv::RANSAC);
//                std::cout << " H:\n" << H << std::endl;
                cv::Point3d Q = cv::Point3d(cv::Mat(H*cv::Mat(cv::Point3d(p.x , p.y , 1.0))));
                q = cv::Point2f(Q.x/Q.z  ,Q.y/Q.z);
                // jiuzheng
                // q.y += 118;
                pcorners.push_back(q);
            }
            else {
                pcorners.clear();
                break;
            }
        }
        std::cout<<i<<" pcorners: "<<pcorners.size()<<std::endl;
        for(int j = 0; j < pcorners.size(); j++) {
            std::cout<<pcorners[j]<<std::endl;
        }
        projector_corners.push_back(pcorners);
        pcorners.clear();
    }

    //generate world object coordinates
    unsigned count = 0;
    for(int i = 0; i < frameSeqs.size(); i++)
    {
        if(board_corners[i].size() && projector_corners[i].size())
        {
            count++;
        }
    }
    std::vector<cv::Point3f> world_corners;
    for (int h=0; h<board_size.height; h++)
    {
        for (int w=0; w<board_size.width; w++)
        {
           world_corners.push_back(cv::Point3f(corner_size.width * w,  corner_size.height * h , 0.f));
        }
    }
    std::vector<std::vector<cv::Point3f> > objectPoints;
    objectPoints.reserve(count);
    for (unsigned i=0; i<count; i++)
    {
        objectPoints.push_back(world_corners);
    }

    //generate world object coordinates
    std::vector<cv::Point3f> world_corners_p;
    for (int h=0; h<board_size.height; h++)
    {
        for (int w=0; w<board_size.width; w++)
        {
            world_corners_p.push_back(cv::Point3f(corner_size.width * w , corner_size.height * h  ,0.f));
        }
    }

    std::vector<std::vector<cv::Point3f> > objectPoints_p;
    objectPoints_p.reserve(count);
    for (unsigned i=0; i<count; i++)
    {
        objectPoints_p.push_back(world_corners_p);
    }

    //collect projector correspondences
    projector_corners.resize(count);
    pattern_list.resize(count);

    int cal_flags = 0
                  //+ cv::CALIB_FIX_K1
                  //+ cv::CALIB_FIX_K2
                  //+ cv::CALIB_ZERO_TANGENT_DIST
                  + cv::CALIB_FIX_K3
                  ;
    //calibrate the camera ////////////////////////////////////
    std::vector<cv::Mat> cam_rvecs , cam_tvecs;
    int cam_flags = cal_flags;
    cv::Size imageSize = frameSeqs[0][0].size();
    res->cam_error = cv::calibrateCamera(objectPoints , board_corners , imageSize , res->Kc , res->kc  ,cam_rvecs , cam_tvecs);
    std::cout<<"calibrate the camera !"<<std::endl;

    //calibrate the projector ////////////////////////////////////
    std::vector<cv::Mat> proj_rvecs , proj_tvecs;
    int proj_flags = cal_flags;
    cv::Size projector_size(912, 1140);
    res->proj_error = cv::calibrateCamera(objectPoints_p , projector_corners, projector_size , res->Kp , res->kp , proj_rvecs , proj_tvecs);

    std::cout<<"calibrate the projector !"<<std::endl;
    //stereo calibration
    cv::Mat E,  F;
    res->stereo_error = cv::stereoCalibrate(objectPoints , board_corners , projector_corners ,
                                            res->Kc , res->kc , res->Kp  ,res->kp  ,imageSize /*ignored*/ ,
                                            res->Rp , res->Tp , E , F );
//    res->stereo_error = cv::stereoCalibrate(objectPoints , board_corners , projector_corners , res->Kc , res->kc , res->Kp  ,res->kp  ,imageSize /*ignored*/ , res->Rp , res->Tp , E , F ,
//                                                    cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS  ,50  ,DBL_EPSILON) ,
//                                                    cv::CALIB_FIX_INTRINSIC /*cv::CALIB_USE_INTRINSIC_GUESS + cal_flags*/);
    std::cout<<"stereo calibration !"<<std::endl;


	cv::FileStorage fsc("rtc.xml", cv::FileStorage::WRITE);
	cv::FileStorage fsp("rtp.xml", cv::FileStorage::WRITE);

	// objectPoints  projector_corners  board_corners
	std::ofstream opout("objectPoints.txt");
	std::ofstream pcout("projector_corners.txt");
	std::ofstream ccout("board_corners.txt");
	for (int i = 0; i < objectPoints.size(); i++) {
		fsc << "R" + std::to_string(i) << cv::Mat(cam_rvecs[i]);
		fsc << "T" + std::to_string(i) << cv::Mat(cam_tvecs[i]);
		fsp << "R" + std::to_string(i) << cv::Mat(proj_rvecs[i]);
		fsp << "T" + std::to_string(i) << cv::Mat(proj_tvecs[i]);
		for (int j = 0; j < objectPoints[i].size(); j++) {
			opout << objectPoints[i][j] << std::endl;
			pcout << projector_corners[i][j] << std::endl;
			ccout << board_corners[i][j] << std::endl;
		}
	}
	opout.close();
	pcout.close();
	ccout.close();
	fsc.release();
	fsp.release();

    return res;

}

std::vector<cv::Point2f> Calibrator::extract_board_corners(cv::Mat &gray_image)
{
    std::vector<cv::Point2f> corners;
    int image_scale = 1;
    if (gray_image.rows<1)
    {
        return corners;
    }
    cv::Size imageSize = gray_image.size();
    if (imageSize.width>1024)
    {
        image_scale = imageSize.width/1024;
    }

    cv::Mat small_img;
    if (image_scale>1)
    {
        cv::resize(gray_image , small_img , cv::Size(gray_image.cols/image_scale , gray_image.rows/image_scale));
    }
    else
    {
       small_img = gray_image;
    }

    if(board_type == Chessboard) {
        cv::findChessboardCorners(small_img, board_size, corners);
    }
    else if(board_type == Circular) {
        cv::findCirclesGrid(small_img, board_size, corners);
    }

    if (corners.size())
    {
        for (std::vector<cv::Point2f>::iterator iter=corners.begin(); iter!=corners.end(); iter++)
        {
            *iter = image_scale*(*iter);
        }
        cv::cornerSubPix(gray_image , corners , cv::Size(11 , 11) , cv::Size(-1 , -1) ,
                            cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30 , 0.1));
    }

    return corners;
}


bool Calibrator::decode_gray_set(int ind , cv::Mat & pattern_image,  cv::Mat & min_max_image)
{
    if (ind >= frameSeqs.size())
    {   //out of bounds
        return false;
    }

    //estimate direct component
    //b = config.value("robust_estimation/b"  DEFAULT_B).toFloat();
    std::vector<cv::Mat> images;
//    QList<unsigned> direct_component_images(QList<unsigned>() << 15 << 16 << 17 << 18 << 35 << 36 << 37 << 38);
    int total_images = frameSeqs[ind].size();
    int total_patterns = total_images/2 - 1;
    const int direct_light_count = 4;
    const int direct_light_offset = 4;

    QList<unsigned> direct_component_images;
    for (unsigned i=0; i<direct_light_count; i++)
    {
        int index = total_images - total_patterns - direct_light_count - direct_light_offset + i + 1;
        direct_component_images.append(index);
        direct_component_images.append(index + total_patterns);
    }
    foreach (unsigned i , direct_component_images)
    {
        images.push_back(frameSeqs[ind][i]);
    }
    cv::Mat direct_light = sl::estimate_direct_light(images,  b);

    //m = config.value("robust_estimation/m"  DEFAULT_M).toUInt();
//    return sl::decode_pattern(frameSeqs[ind] , pattern_image , min_max_image , sl::RobustDecode|sl::GrayPatternDecode , direct_light,  m);

    cv::Size projector_size(912, 1140);
    bool rv = sl::decode_pattern(frameSeqs[ind], pattern_image, min_max_image, projector_size, sl::RobustDecode|sl::GrayPatternDecode, direct_light, m);
    return rv;
}

