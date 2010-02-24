#pragma once

#include <vector>
#include <stdexcept>

#include "AEImagePipelineFilter.h"

namespace Aetherspark
{
	namespace ImageProcessing
	{	
		class AEImageProcessingPipeline
		{
			public:
				AEImageProcessingPipeline();
			
				//Filter management
				void addFilter(AEImagePipelineFilterRef filter);
				void insertFilter(AEImagePipelineFilterRef filter, unsigned long filterIndex) throw(std::out_of_range);
				void removeFilter(unsigned long filterIndex) throw(std::out_of_range);
				void removeAllFilters();
				void toggleFilters(bool on);
				
				//Image processing
				IplImage* processImage(IplImage *img);
		
			private:
				bool _filtersOn;
				std::vector<AEImagePipelineFilterRef> _filters;
		};
	}
}

