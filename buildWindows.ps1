Remove-Item "build\*" -Force -Recurse

New-Item -ItemType Directory -Force -Path build

Set-Location build

Clear-Host

cmake -G "NMake Makefiles" ..

nmake

.\Test.exe 

Set-Location ..
