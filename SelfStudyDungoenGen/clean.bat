echo delete generated files

rmdir /s /q .vs
rmdir /s /q Binaries
rmdir /s /q Build
rmdir /s /q DerivedDataCache
rmdir /s /q Intermediate
rmdir /s /q Saved
del *.vsconfig
del *.sln