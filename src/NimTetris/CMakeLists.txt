TARGET_SOURCES (${ProjectName}
	PRIVATE
	Blocks.cpp
	Blocks.hpp
	Board10x10.cpp
	Board10x10.hpp
	ErrorStrings.hpp
	NimTetris.cpp
	NimTetris.hpp
	NimTetrisAI.cpp
	NimTetrisAI.hpp
	NimTetrisAIThreadRunner.cpp
	NimTetrisAIThreadRunner.hpp
	NimTetrisAutosaveds.cpp
	NimTetrisAutosaveds.hpp
	NimTetrisAutosaver.cpp
	NimTetrisAutosaver.hpp
	NimTetrisGraphics.cpp
	NimTetrisGraphics.hpp
	NimTetrisPlayerInfo.hpp
	NimTMessageHandler.cpp
	NimTMessageHandler.hpp
)

ADD_SUBDIRECTORY (_OS)
ADD_SUBDIRECTORY (_Language)
ADD_SUBDIRECTORY (Actor)
ADD_SUBDIRECTORY (AI)