#include <iostream>
#include <opencv.hpp>
using namespace std;
using namespace cv;

//创建检测器对象
CascadeClassifier classifier;

//初始化函数
void init() {
	//指定人脸配置文件路径(在opencv安装的文件夹内)
	string path = "D:\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml";
	//加载人脸配置文件
	classifier.load(path);
}

/*
* @param src 待识别的图像数据
* @param result 人脸识别结果
*/
bool Classify_face(Mat src,vector<Rect> &result) {
	//清理历史数据防止内存溢出
	result.clear();
	//使用detectMultiScale方法识别src内的人脸，并将识别结果存储在result内
	//识别结果是矩阵数组，每个矩阵有x,y,width,height四个信息，表示人脸在图像上的位置
	classifier.detectMultiScale(src, result);
	//result大小为0表示没有识别到人脸
	if (result.size() <= 0) {
		return false;
	}
	return true;
}

/*
* @brief 画框函数
* @param src 待被画框的图像
* @param result 人脸识别得到的矩阵数组
*/
void Paint_tangle(Mat &src,vector<Rect> result) {
	//定义框线颜色
	Scalar color=CV_RGB(0, 255, 0);
	//循环给所有人脸识别结果位置画框
	for (int i = 0; i < result.size(); i++) {
		rectangle(src, result[i].tl(), result[i].br(), color, 1);
	}
}

//@brief 图片文件人脸识别测试函数
void ImageClassifyTest() {
	vector<Rect> ret;
	Mat img = imread("test1.jpg");
	if (Classify_face(img, ret)) {
		Paint_tangle(img,ret);
		imshow("图片文件人脸识别_单人", img);
	}
	img = imread("test2.jpg");
	if (Classify_face(img, ret)) {
		Paint_tangle(img, ret);
		imshow("图片文件人脸识别_多人", img);
		waitKey(0);
	}
}

//@brief 视频文件人脸识别测试函数
void VideoClassifyTest() {
	VideoCapture cap("test.mp4");
	if (!cap.isOpened()) {
		cout << "视频文件打开失败" << endl;
		return;
	}
	Mat frame;
	vector<Rect> ret;
	while (true) {
		cap >> frame;
		if (frame.empty()) {
			break;
		}
		if (Classify_face(frame, ret)) {
			Paint_tangle(frame, ret);
			imshow("视频文件人脸识别", frame);
			waitKey(2);
		}
	}
}

//@brief 摄像头视频流人脸识别测试函数
void CameraClassifyTest() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "摄像头打开失败" << endl;
		return;
	}
	Mat frame;
	vector<Rect> ret;
	while (true) {
		cap >> frame;
		if (frame.empty()) {
			break;
		}
		if (Classify_face(frame, ret)) {
			Paint_tangle(frame, ret);
			imshow("摄像头视频流人脸识别", frame);
			waitKey(2);
		}
	}
}

int main()
{
	init();
	//图片文件人脸识别测试
	ImageClassifyTest();
	//视频文件人脸识别测试
	//VideoClassifyTest();
	//摄像头视频流人脸识别测试
	//CameraClassifyTest();
	return 0;
}
