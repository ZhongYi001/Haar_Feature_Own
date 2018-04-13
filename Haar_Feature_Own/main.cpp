#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>
#include <io.h>

#include "Haar.h"

using namespace cv;
using namespace std;

void getAllFiles(string path, vector<string>& files);

string output = "../csv/Train5.csv";
float feat_type = 1;		// 1 是正样本，0是负样本



int main()
{
	HaarFeature m_feature(1, 6);
	int Win_size = 24;
	vector<string> files;
	string DATA_DIR = "../P_Train";
	//测试
	char * DistAll = "AllFiles.txt";
	getAllFiles(DATA_DIR, files);//所有文件与文件夹的路径都输出
	ofstream ofn(DistAll);  //输出文件流
	int file_size = files.size();
	ofn << file_size << endl;
	for (int i = 0; i< file_size; i++)
	{
		ofn << files[i] << endl;
	}
	ofn.close();


	ofstream outFile;
	outFile.open(output, ios::out);
	for (unsigned int i = 0; i < file_size; i++)
	{
		cout << files[i] << endl;
		Mat image = imread(files[i]);
		if (image.empty())
		{
			cout << "Load the image error!" << endl;
			return -1;
		}
		resize(image, image, Size(Win_size, Win_size) );
		//imshow("1", image);
		//Mat imageRGB[3];
		//split(image, imageRGB);
		//for (int i = 0; i < 3; i++)
		//{
		//	equalizeHist(imageRGB[i], imageRGB[i]);
		//}
		//merge(imageRGB, 3, image);
		cvtColor(image, image, CV_RGB2GRAY);



		//Rect rect = Rect(0, 0, 0, 0);
		//int size_max = 6;
		//vector<HaarFeature> m_feature;
		vector<float> m_feat;

		double time0 = static_cast<double>(getTickCount());


		m_feature.caluHf(image, m_feat);
		

		cout << m_feat.size() << endl;
		//m_feat = m_feature[3520].caluHf(image);
		//cout << i << "";
		int zero = 0;
		for (unsigned int j = 0; j < m_feat.size(); j++)
		{
			float tmp;
			tmp = m_feat[j];
			
			//cout << i << "|";
			outFile << tmp << ',';
			//cout << m_feat << endl;
			//if (m_feat < -1.70141e+38 || m_feat > 1.70141e+38)
			//{
			//	cout << i << endl;
			//}
			if (tmp == 0)
				zero++;
		}
		outFile << feat_type << endl;

		//if (zero == 13711)
		//	break;

		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		cout << "提取特征运行时间为：" << time0 << "秒" << endl;

	}
	outFile.close();


	system("pause");
	return 0;
}


void getAllFiles(string path, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //判断是否为文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("/").append(fileinfo.name));//保存文件夹名字
					getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);//递归当前文件夹
				}
			}
			else    //文件处理
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));//文件名
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}