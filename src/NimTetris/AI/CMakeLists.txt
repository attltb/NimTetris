TARGET_SOURCES (${ProjectName}
	PRIVATE
	BitScanner.h
	BlockCompressed10x10.hpp
	BlockCompressor.cpp
	BlockCompressor.hpp
	BoardCompressed10x10.hpp
	BoardCompressor.hpp
	ConnectedComponent.cpp
	ConnectedComponent.hpp
	ConnectedComponentFinder.hpp
	ConnectedComponentsWithAnalysis.cpp
	ConnectedComponentsWithAnalysis.hpp
	NimTetrisAIConfig.cpp
	NimTetrisAIConfig.hpp
	OptimizedInformationSet.cpp
	OptimizedInformationSet.hpp
)

ADD_SUBDIRECTORY (_Machine)