#include "Haar.h"  
#include <iostream>  
#include <math.h>

using namespace std;

HaarFeature::HaarFeature(int& size_min, int& size_max, const int& pic_size = 24)
{
	Rect rect = Rect(0, 0, 0, 0);
	int x_Max = 0, y_Max = 0;


	for (int size = 1; size <= size_max; size++)
	{
		for (int type = 0; type <= 7; type++)
		{
			switch (type)
			{
			case 0:
			{
				x_Max = pic_size - 2 * size;
				y_Max = pic_size - 2 * size;
				break;
			}
			case 1:
			{
				x_Max = pic_size - 2 * size;
				y_Max = pic_size - 2 * size;
				break;
			}
			case 2:
			{
				x_Max = pic_size - 3 * size;
				y_Max = pic_size - 2 * size;
				break;
			}
			case 3:
			{
				x_Max = pic_size - 2 * size;
				y_Max = pic_size - 3 * size;
				break;
			}
			case 4:
			{
				x_Max = pic_size - 4 * size;
				y_Max = pic_size - 2 * size;
				break;
			}
			case 5:
			{
				x_Max = pic_size - 2 * size;
				y_Max = pic_size - 4 * size;
				break;
			}
			case 6:
			{
				x_Max = pic_size - 2 * size;
				y_Max = pic_size - 4 * size;
				break;
			}
			case 7:
			{
				x_Max = pic_size - 2 * size;
				y_Max = pic_size - 1 * size;
				break;
			}
			}

			for (int x = 0; x <= x_Max; x++)
			{
				for (int y = 0; y <= y_Max; y++)
				{
					rect = Rect(x, y, 0, 0);
					switch (type)
					{
					case 0:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 1 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_weights.push_back(-1.f);
						m_weights.push_back(2.f);
						m_weights.push_back(0.f);
						m_weights.push_back(0.f);
						break;
					}
					case 1:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_weights.push_back(-1.f);
						m_weights.push_back(2.f);
						m_weights.push_back(0.f);
						m_weights.push_back(0.f);
						break;
					}
					case 2:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 3 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 1 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_weights.push_back(1.f);
						m_weights.push_back(-3.f);
						m_weights.push_back(3.f);
						m_weights.push_back(0.f);
						break;
					}
					case 3:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 3 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 1 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_weights.push_back(1.f);
						m_weights.push_back(-3.f);
						m_weights.push_back(3.f);
						m_weights.push_back(0.f);
						break;
					}
					case 4:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 4 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 3 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 1 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_weights.push_back(1.f);
						m_weights.push_back(-2.f);
						m_weights.push_back(2.f);
						m_weights.push_back(0.f);
						break;
					}
					case 5:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 4 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 3 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 1 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_weights.push_back(1.f);
						m_weights.push_back(-2.f);
						m_weights.push_back(2.f);
						m_weights.push_back(0.f);
						break;
					}
					case 6:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 4 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 2 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 1 * size, 4 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 1 * size, 1 * size));
						m_weights.push_back(1.f);
						m_weights.push_back(-2.f);
						m_weights.push_back(-2.f);
						m_weights.push_back(4.f);
						break;
					}
					case 7:
					{
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 1 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 1 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 1 * size));
						m_rects.push_back(Rect(rect.x, rect.y, 2 * size, 1 * size));
						m_weights.push_back(-1.f);
						m_weights.push_back(0.f);
						m_weights.push_back(0.f);
						m_weights.push_back(0.f);
						break;
					}
					}
				}
			}
		}
	}
}


float HaarFeature::sum(Mat& _img, Rect& _rect)
{
	int x = _rect.x + _rect.width;
	int y = _rect.y + _rect.height;
	Mat _imgInt;
	int tempVal = 0;
	integral(_img, _imgInt, CV_32F);
	//int a, b, c, d;
	//a = ;
	//tempVal = a + b + c + d;
	tempVal =
		_imgInt.at<int>(x, y) +
		_imgInt.at<int>(_rect.x + 1, _rect.y + 1) -
		_imgInt.at<int>(x , _rect.y + 1) -
		_imgInt.at<int>(_rect.x + 1, y);
	return tempVal;
}


float HaarFeature::caluHf(Mat& _img)
{
	Mat _imgInt;
	int tempVal = 0;
	int Val = 0;
	float a1 = m_weights[0], 
		a2 = m_weights[1],
		a3 = m_weights[2],
		a4 = m_weights[3];
	Rect r1 = m_rects[0], 
		r2 = m_rects[1],
		r3 = m_rects[2], 
		r4 = m_rects[3];
	for (int i = 0; i < m_rects.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Val += m_weights[j] * ;
		}
	}
	Val = a1 * sum(_img, r1) +
		a2 * sum(_img, r2) +
		a3 * sum(_img, r3) +
		a4 * sum(_img, r4);
	
	float g_sum = sum(_img, Rect(r1.x, r1.y, _img.cols - 2, _img.rows - 2));
	float g_sqsum = g_sum * g_sum;
	float mean = g_sum / ((_img.cols - 2 ) * (_img.rows - 2)),
		sqmean = g_sqsum / ((_img.cols - 2) * (_img.rows - 2));
	float varNormFactor = sqrt(sqmean - mean * mean); 
	if (g_sum == 0 || varNormFactor == 0)
	{
		return Val / (_img.cols * _img.rows);
	}
	else
	return Val / (varNormFactor);

}