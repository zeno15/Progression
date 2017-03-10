Remove-Item "build\*" -Force -Recurse

New-Item -ItemType Directory -Force -Path build

Set-Location build

Clear-Host

cmake -G "NMake Makefiles" -DSFML_DIR="C:/Libraries/SFML-2.3.2" ..

nmake

.\Test.exe

Set-Location ..
