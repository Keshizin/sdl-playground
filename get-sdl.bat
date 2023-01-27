@SET PROJ_PATH=%cd%
@SET SDL2_VERSION=SDL2-2.26.2

py get-sdl.py %SDL2_VERSION%
cd %SDL2_VERSION%/VisualC
msbuild SDL.sln /p:Configuration=Release /p:Platform=x64

copy "%PROJ_PATH%\%SDL2_VERSION%\VisualC\x64\Release\SDL2.lib" "%PROJ_PATH%\lib"
copy "%PROJ_PATH%\%SDL2_VERSION%\VisualC\x64\Release\SDL2main.lib" "%PROJ_PATH%\lib"
copy "%PROJ_PATH%\%SDL2_VERSION%\VisualC\x64\Release\SDL2.dll" "%PROJ_PATH%\bin"
copy "%PROJ_PATH%\%SDL2_VERSION%\include\" "%PROJ_PATH%\include\SDL2\"

cd %PROJ_PATH%

del %SDL2_VERSION%.zip
@rmdir /s /q %SDL2_VERSION%