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
float feat_type = 1;		// 1 ����������0�Ǹ�����



int main()
{
	HaarFeature m_feature(1, 6);
	int Win_size = 24;
	vector<string> files;
	string DATA_DIR = "../P_Train";
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