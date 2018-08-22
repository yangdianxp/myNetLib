set PROTOC=..\..\..\protobuf\protoc.exe
for /r %%r in (*.proto) do (
	%PROTOC% -I=%~dp0 --cpp_out=%~dp0 %%r
)