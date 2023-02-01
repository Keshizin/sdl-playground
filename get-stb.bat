@SET PROJ_PATH=%cd%
@SET STB_NAME=stb-master

@py get-stb.py
@cd %STB_NAME%

@copy "%PROJ_PATH%\%STB_NAME%\stb_image.h" "%PROJ_PATH%\include\stb"
@copy "%PROJ_PATH%\%STB_NAME%\stb_image_write.h" "%PROJ_PATH%\include\stb"
@copy "%PROJ_PATH%\%STB_NAME%\stb_image_resize.h" "%PROJ_PATH%\include\stb"
@copy "%PROJ_PATH%\%STB_NAME%\stb_truetype.h" "%PROJ_PATH%\include\stb"
@copy "%PROJ_PATH%\%STB_NAME%\stb_ds.h" "%PROJ_PATH%\include\stb"

@cd %PROJ_PATH%
@del %STB_NAME%.zip
@rmdir /s /q %STB_NAME%