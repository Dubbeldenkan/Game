För att ladda in Direct3D
- Lägg in "Microsoft DirectX SDK (June 2010)" i lämplig mapp.
- Öppna visual studio och höger klicka på "Direct3DWrapper, öppna properties, välj Configuration: all configuration.
	- VC++ Directories 
		- Under "Include Directories", lägg till länken till där SDK placerades + "\Include"
		- Under "Library Directories", lägg till länken till där SDK placerades + "\Lib\x86"
		(Obs inbland tycker visual studio om att ändra "(" till %28 och ")" till %29, då får man ändra till paranteser manuellt. 


Lägg till samma länkningar för "Game". 



För att lägga till wrapper till ett nytt project:
- Lägg till Direct3DWrapper i samma solution som det andra projektet, lägg till ..\Direct3DWrapper\ under 
	C/C++ >> General >> additional include directories. 

Samt gå in under C/C++ General och lägg till "..\Direct3DWrapper" under "additional include Directories"

- Lägg till d3dx9.lib och d3d9.lib under Linker >> Input >> additional dependencies (Under configururation: debug samt under release)
- Ändra wrappern till ett statiskt bibliotek under Configuration Properties >> General >> Configuration Type, under General 
	ändra även Character set till "use multi-byte character set"