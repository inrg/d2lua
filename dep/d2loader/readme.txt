			D2Loader Plugin Support
	
	the plugin struct is very simple now, check the source code of sample.dll
for it.
	so,you may ask why plugin here.
	here is a big feature of it:
	the plugin will be loaded into "Diablo II" process. so, you can use
GetModuleHandle to search a certain module (WriteProcessMemoryEx and ReadProcessMemoryEx
is unsafe here,for the dll module maybe rebased by the OS).even more,you can
apply certain hook to the game in order to run your own code. very simple, all
are done in a single process. try it out yourself.

	comments and suggestions are welcomed to onlyer@263.net. also, you can
send me your own plugins and i may put them into next release.

	to install a plugin, just make a directory with the name "plugin"
in your diablo2	directory,and then copy the .dll into it. the loader will search
and load it at startup (if possible)
