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

string output = "../csv/N_Train4.csv";
float feat_type = 0;		// 1 ����������0�Ǹ�����



int main()
{
	int Win_size = 24;
	vector<string> files;
	string DATA_DIR = "../N_Train";
	//����
	char * DistAll = "AllFiles.txt";
	getAllFiles(DATA_DIR, files);//�����ļ����ļ��е�·�������
	ofstream ofn(DistAll);  //����ļ���
	int file_size = files.size();
	ofn << file_size << endl;
	for (int i = 0; i< file_size; i++)
	{
		ofn << files[i] << endl;
	}
	ofn.close();


	ofstream outFile;
	outFile.open(output, ios::out);
	for (int i = 0; i < files.size(); i++)
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



		Rect rect = Rect(0, 0, 0, 0);
		int size_max = 6;
		int x_Max, y_Max;
		vector<HaarFeature> m_feature;

		double time0 = static_cast<double>(getTickCount());
		for (int size = 1; size <= size_max; size = size + 1)
		{
			//cout << endl << "�߶ȴ�С" << size << endl;
			for (int type = 0; type <= 7; type++)
			{
				switch (type)
				{
				case 0:
				{
					x_Max = image.cols - 2 * size;
					y_Max = image.rows - 2 * size;
					break;
				}
				case 1:
				{
					x_Max = image.cols - 2 * size;
					y_Max = image.rows - 2 * size;
					break;
				}
				case 2:
				{
					x_Max = image.cols - 3 * size;
					y_Max = image.rows - 2 * size;
					break;
				}
				case 3:
				{
					x_Max = image.cols - 2 * size;
					y_Max = image.rows - 3 * size;
					break;
				}
				case 4:
				{
					x_Max = image.cols - 4 * size;
					y_Max = image.rows - 2 * size;
					break;
				}
				case 5:
				{
					x_Max = image.cols - 2 * size;
					y_Max = image.rows - 4 * size;
					break;
				}
				case 6:
				{
					x_Max = image.cols - 2 * size;
					y_Max = image.rows - 4 * size;
					break;
				}
				case 7:
				{
					x_Max = image.cols - 2 * size;
					y_Max = image.rows - 1 * size;
					break;
				}
				}
				//cout << endl << "������� " << type << endl;
				for (rect.x = 0; rect.x <= x_Max; rect.x++)
				{
					for (rect.y = 0; rect.y <= y_Max; rect.y++)
					{
						//cout << rect.x << "|" << rect.y << "   ";
						m_feature.push_back(HaarFeature(rect, type, size));			// ��������ģ��
					}
				}
			}
		}


		float m_feat;
		int feat_num = (int)m_feature.size();
		cout << "��������: " << feat_num << endl;


		//m_feat = m_feature[3520].caluHf(image);
		//cout << i << "";

		for (int i = 0; i < feat_num; i++)
		{
			m_feat = m_feature[i].caluHf(image);
			//cout << i << "|";
			outFile << m_feat << ',';
			//cout << m_feat << endl;
			//if (m_feat < -1.70141e+38 || m_feat > 1.70141e+38)
			//{
			//	cout << i << endl;
			//}
		}
		outFile << feat_type << endl;


		time0 = ((double)getTickCount() - time0) / getTickFrequency();
		cout << "��ȡ��������ʱ��Ϊ��" << time0 << "��" << endl;

	}
	outFile.close();


	system("pause");
	return 0;
}


void getAllFiles(string path, vector<string>& files)
{
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
	string p;  //string�������˼��һ����ֵ����:assign()���кܶ����ذ汾
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //�ж��Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("/").append(fileinfo.name));//�����ļ�������
					getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);//�ݹ鵱ǰ�ļ���
				}
			}
			else    //�ļ�����
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));//�ļ���
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
		_findclose(hFile);
	}
}