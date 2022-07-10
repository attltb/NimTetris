TARGET_SOURCES (${ProjectName}
	PRIVATE
	BinaryData.hpp
	Bitmap32.hpp
	Bitmap32Pool.hpp
	Blender32.hpp
	Drawable.hpp
	Game.hpp
	KeyCode.hpp
	Randomizer.hpp
	ResourceCollection.hpp
	ResourceKind.hpp
	Resources.hpp
	Thread.hpp
	ThreadManager.hpp
	Timer.hpp
	TimerManager.hpp
	WindowHandle.hpp
	WindowMessageHandler.hpp
)

ADD_SUBDIRECTORY (_OS)