py get-sdl.py
cd SDL2-2.26.2/VisualC
msbuild SDL.sln /p:Configuration=Release /p:Platform=x64

copy "C:\Takeshi\Projetos\sdl-playground\SDL2-2.26.2\VisualC\x64\Release\SDL2.lib" "C:\Takeshi\Projetos\sdl-playground\lib"
copy "C:\Takeshi\Projetos\sdl-playground\SDL2-2.26.2\VisualC\x64\Release\SDL2main.lib" "C:\Takeshi\Projetos\sdl-playground\lib"
copy "C:\Takeshi\Projetos\sdl-playground\SDL2-2.26.2\VisualC\x64\Release\SDL2.dll" "C:\Takeshi\Projetos\sdl-playground\lib"

copy "C:\Takeshi\Projetos\sdl-playground\SDL2-2.26.2\include\" "C:\Takeshi\Projetos\sdl-playground\include\SDL2\"

cd "..\..\"