TARGET_SOURCES (${ProjectName}
	PRIVATE
	Randomizer.cpp
	ResourceCollection.cpp
	Resources.cpp
)

ADD_SUBDIRECTORY (_OS)
ADD_SUBDIRECTORY (Drawable)
ADD_SUBDIRECTORY (NimTetris)