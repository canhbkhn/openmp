#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include <vector>
#include <omp.h>
#include <string>

/*
This is small function to test using openMP library in parallel computing and
not using lib openMP: convert 8k images from .jpg file to .png file
When execute with openMP lib, time to end process is: 2m30s
When execute with no openMP lib, time to end process is: 3m

8k images can be download at: http://academictorrents.com/download/9dea07ba660a722ae1008c4c8afdd303b6f6e53b.torrent
*/


void convertWithOpenMP()
{
	cv::String path("D:\\Dev\\Flickr8k\\Flickr8k_Dataset\\Flicker8k_Dataset\\*.jpg");
	std::vector<cv::String> fn;
	std::vector<cv::Mat> data;

	cv::glob(path, fn, true);

#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			for (size_t k = 0; k < fn.size() / 2; ++k)
			{
				cv::Mat im = cv::imread(fn[k]);
				//if (im.empty()) continue; //only proceed if sucsessful
				// you probably want to do some preprocessing
				//data.push_back(im);
				cv::imwrite("D:\\Dev\\Flickr8k\\out\\" + std::to_string(k) + ".png", im);
			}

#pragma omp section
			for (size_t k = fn.size() / 2; k < fn.size(); ++k)
			{
				cv::Mat im = cv::imread(fn[k]);
				//if (im.empty()) continue; //only proceed if sucsessful
				// you probably want to do some preprocessing
				//data.push_back(im);
				cv::imwrite("D:\\Dev\\Flickr8k\\out\\" + std::to_string(k) + ".png", im);
			}

		}
	}

	std::cout << "Done" << std::endl;
}

void convertWithoutOpenMP()
{
	cv::String path("D:\\Dev\\Flickr8k\\Flickr8k_Dataset\\Flicker8k_Dataset\\*.jpg");
	std::vector<cv::String> fn;
	std::vector<cv::Mat> data;

	cv::glob(path, fn, true);

	for (size_t k = 0; k < fn.size(); ++k)
	{
		cv::Mat im = cv::imread(fn[k]);
		cv::imwrite("D:\\Dev\\Flickr8k\\out\\" + std::to_string(k) + ".png", im);
	}

	std::cout << "Done" << std::endl;
}



int main()
{
	// with openMp
	convertWithOpenMP();

	// without openMp
	convertWithoutOpenMP();

	system("pause");
}