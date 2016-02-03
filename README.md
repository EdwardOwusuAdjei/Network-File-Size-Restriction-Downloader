#Bypass Known Proxy/Network File Size Download Restriction
Set Byte Preprocessor value properly..Currently 200MB.
Compile: g++ bigfiledownloader.cpp -o biggie -lboost_regex

Depends on : <br/>1. C++ Boost Library
<br/>		2. GNU project C and C++ compiler.	
		3. Curl.
		4. A Stupid Network Admin who says don't exceed a file size
		   during downloads.
