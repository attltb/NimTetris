TARGET_SOURCES (${ProjectName}
	PRIVATE
	DialogBox.hpp
	WinMain.cpp
	resource.h
	NimTetris.ico
	small.ico
)

if(${NT_LANGUAGE} MATCHES "Korean")
	TARGET_SOURCES (${ProjectName}
		PRIVATE
		DialogBox.kor.cpp
		NimTetris.kor.rc
	)
elseif(${NT_LANGUAGE} MATCHES "English")
	TARGET_SOURCES (${ProjectName}
		PRIVATE
		DialogBox.eng.cpp
		NimTetris.eng.rc
	)
endif() 