sami c libary
=================

This is the library for the sami plug-in written in ANSI C.

The library is divided into modules that include

*hot_reload*

This is the hot reloader for devloping sami. 

Both the _run_ module for the engine and the _client_ module use the hot reloader to run the _sami_ and _terminal_ modules respectively. TODO: gui?

Whilst it doesn't share any code with the project, [jdh's hot reloader](https://github.com/jdah/reloadhost) has been influential in the design of this component and is worth checking out.

TODO: License?
