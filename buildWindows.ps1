Remove-Item "build\*" -Force -Recurse

New-Item -ItemType Directory -Force -Path build

cd build

cmake -G "NMake Makefiles" ..

nmake

.\Test.exe

cd ..
