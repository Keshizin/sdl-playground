@SET PROJ_PATH=%cd%
@SET SDL_VERSION=SDL3-3.1.0

py get-sdl.py %SDL_VERSION%
cd %SDL_VERSION%/VisualC
msbuild SDL.sln /p:Configuration=Release /p:Platform=x64

copy "%PROJ_PATH%\%SDL_VERSION%\VisualC\x64\Release\SDL3.lib" "%PROJ_PATH%\lib"
copy "%PROJ_PATH%\%SDL_VERSION%\VisualC\x64\Release\SDL3_test.lib" "%PROJ_PATH%\lib"
copy "%PROJ_PATH%\%SDL_VERSION%\VisualC\x64\Release\SDL3.dll" "%PROJ_PATH%\bin"
copy "%PROJ_PATH%\%SDL_VERSION%\include\SDL3\" "%PROJ_PATH%\include\SDL3\"

cd %PROJ_PATH%

del %SDL_VERSION%.zip
@rmdir /s /q %SDL_VERSION%
