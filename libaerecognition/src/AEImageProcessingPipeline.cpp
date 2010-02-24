#include "AEImageProcessingPipeline.h"

using namespace std;
using namespace Aetherspark::ImageProcessing;

AEImageProcessingPipeline::AEImageProcessingPipeline() :
_filtersOn(true)
{

}

void AEImageProcessingPipeline::addFilter(AEImagePipelineFilterRef filter)
{
	_filters.push_back(filter);
}

void AEImageProcessingPipeline::insertFilter(AEImagePipelineFilterRef filter, unsigned long filterIndex) throw(out_of_range)
{
	if(filterIndex > _filters.size())
	{
		throw out_of_range("Specified filter index is invalid.");
	}
	_filters.insert(_filters.begin() + filterIndex, filter);
}

void AEImageProcessingPipeline::removeFilter(unsigned long filterIndex) throw(out_of_range)
{
	if(filterIndex >= _filters.size())
	{
		throw out_of_range("Specified filter index is invalid.");
	}
	_filters.erase(_filters.begin() + filterIndex);
}

void AEImageProcessingPipeline::removeAllFilters()
{
	_filters.clear();
}

void AEImageProcessingPipeline::toggleFilters(bool on)
{
	_filtersOn = on;
}

IplImage* AEImageProcessingPipeline::processImage(IplImage *img)
{
	//Make a copy of the image for modification
	IplImage *newImg = cvCloneImage(img);
	
	if(_filtersOn)
	{
		vector<AEImagePipelineFilterRef>::iterator it;
		for(it = _filters.begin(); it != _filters.end(); it++)
		{
			(*it)->processImage(img, newImg, this);
		}
	}
	
	return newImg;
}

