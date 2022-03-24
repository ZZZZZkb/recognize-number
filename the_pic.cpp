#include <opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include <imgproc.hpp>

using namespace std;
using namespace cv;
void getContours(Mat imgDil, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		string objectType;
		if (100<area&& area< 880) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);


			boundRect[i] = boundingRect(conPoly[i]);

			int objCor = (int)conPoly[i].size();
			/*cout << objCor << endl;*/
			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4) {
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else objectType = "Rect";
			}
			else if (objCor > 4) { objectType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
		}
	}
}

void guessNumber(Mat imgDil)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		if (0 < area&&area<350) 
		{
			cout << "1" ;
		}
	
		if ( 700 < area && area < 720)
		{
			cout << "4" ;
		}
		if (510 < area && area < 540)
		{
			cout << "7" ;
			
		}
		if (1200 < area && area < 1250)
		{
			cout << "8" ;
		}
		if (1000 < area && area < 1100)
		{
			Mat rre1;
			Rect RRe1(0, 0, 30, 28);
			rre1 = imgDil(RRe1);
			imshow("rre1", rre1);
			vector<vector<Point>> contours1;
			vector<Vec4i> hierarchy1;
			findContours(rre1, contours1, hierarchy1, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			vector<vector<Point>> conPoly(contours1.size());
			vector<Rect> boundRect(contours1.size());
			for (int i = 0; i < contours1.size(); i++)
			{
				int area1 = contourArea(contours1[i]);
				if (375 < area1 && area1 < 550)
				{
					cout << "0" ;

				}
				else
				{
					cout << "6" ;
				}
			}
		}
		if (750 < area && area < 900)
		{
			Mat rre2;
			Rect RRe2(0, 40, 30, 25);
			rre2 = imgDil(RRe2);
			imshow("rre2", rre2);
			vector<vector<Point>> contours2;
			vector<Vec4i> hierarchy2;
			findContours(rre2, contours2, hierarchy2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			vector<vector<Point>> conPoly(contours2.size());
			vector<Rect> boundRect(contours2.size());
			for (int i = 0; i < contours2.size(); i++) 
			{
				int area2 = contourArea(contours2[i]);
				if ( 0<area2&&area2 < 200)
				{
					cout << "9";
				
				}	
				else
				{
					Mat rre3;
					Rect RRe3(0, 0, 15, 50);
					rre3 = imgDil(RRe3);
					imshow("rre3", rre3);
					vector<vector<Point>> contours3;
					vector<Vec4i> hierarchy3;
					findContours(rre3, contours3, hierarchy3, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
					vector<vector<Point>> conPoly(contours3.size());
					vector<Rect> boundRect(contours3.size());
					for (int i = 0; i < contours3.size(); i++)
					{
						int area3 = contourArea(contours3[i]);
						if (0<area3&&area3<120)
						{
							cout << "3" ;
						}
						else
						{
							Mat rre4;
							Rect RRe4(0, 35, 15, 30);
							rre4 = imgDil(RRe4);
							imshow("rre4", rre4);
							vector<vector<Point>> contours4;
							vector<Vec4i> hierarchy4;
							findContours(rre4, contours4, hierarchy4, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
							vector<vector<Point>> conPoly(contours4.size());
							vector<Rect> boundRect(contours4.size());
							for (int i = 0; i < contours4.size(); i++)
							{
								int area4 = contourArea(contours4[i]);
								if (0 < area4 && area4 < 180)
								{
									cout << "5" ;
								}
								else
								{
									cout << "2" ;
								}
							}
						
						}
			
					}
				
				
				
				}
			}
		}

	}
}





int main()
{
	Mat image = imread("pic.jpg");
	Mat grey;
	Mat bin;
	cvtColor(image, grey, COLOR_BGR2GRAY);
	threshold(grey, bin, 100, 255, THRESH_BINARY_INV);
	namedWindow("img", 0);
	resizeWindow("img", image.size() );
	imshow("img", bin);
	Mat image_dil;
	Mat element = getStructuringElement(MORPH_RECT, Size(4, 3)); // ÅòÕÍ
	dilate(bin, image_dil, element);
	imshow("image_dil", image_dil);
	getContours(image_dil, image);
	
	Mat re1,re2,re3,re4;
	Rect Re1(13, 3, 30, 70);
	Rect Re2(43, 3, 30, 70);
	Rect Re3(73, 3, 30, 70);
	Rect Re4(103, 3, 30, 70);
	re1 = image_dil(Re1);
	re2 = image_dil(Re2);
	re3 = image_dil(Re3);
	re4 = image_dil(Re4);
	
	//getContours(re1, re1);
	guessNumber(re1);
	guessNumber(re2);
	guessNumber(re3);
	guessNumber(re4);
	imshow("re1", re1);
	imshow("re2", re2);
	imshow("re3", re3);
	imshow("re4", re4);
	imshow("image_di", image);

	waitKey(0);
	return 0;





}