# unix_socket_ser_cli

1.A C++ shared library able to parse a simple INI file with the following publicinterfaces:

  ```unsigned short load_resource(const std::string& path);```

allows an application to load and parse in volatile memory a INI resource filelocated in a standard Linux file system. example:

  ```unsigned short res =load_resource(“/tmp/example.ini”);```

return values: 0 in case of success, 1 in case of read errors, 255 in case of generic error.

  ```unsigned short get_value(const std::string& key,std::string& value);```

allows an application to retrieve the value of a key available in a previously loaded INI file. example: 

  ```std::string buffer; unsigned short res =get_value(“section.foo.bar”, buffer);```

return values: 0 in case of success, 3 in case of missing key, 4 in case a resource file has not been loaded yet, 255 in case of generic error

  ```unsigned short set_value(const std::string& key, conststd::string &value);```

allows an application to store the value of a key in a previously loaded INI file. This adds or replace the new key/value pair both in the volatile memory and in the INI file on the file system. example:

  ```unsigned short res =set_value(“section.color.red”, “roses are red”);```

 return values: 0 in case of success, 4 in case a resource file has not been loaded yet, 255 in case of generic error.

2.A C++ Server application able to use the above mentioned shared library and to expose a basic API to localhost:12345. The server shall expose the following APIs(every API must end with a \n character):

○ LOAD PATH will load the INI file specified by the PATH argument (by calling theload_resource library API)return values: the same returned by the library followed by a \n character, or127\n in case of unknown command. 

  **example: "LOAD /tmp/example.ini\n" -> "0\n"**

○ GET KEY will get the value identified by the KEY argument (by calling the get_valuelibrary API)return values: the same returned by the library followed by the loaded valueand by a \n character, or 127\n in case of unknown command. 

  **example: "GET section.foo.bar\n" -> "0 some value\n"**

○ SET KEY VALUE will set the value identified by the VALUE argument at the KEY argument (by calling the set_value library API)
return values: the same returned by the library followed by a \n character, or 127\n in case of unknown command

  **example: "SET section.color.red roses are red\" -> "0\n"**

3.A C++ Client application exposing a user a basic CLI allowing a user to request theserver to perform the above TCP requets to the Server:

**./client --load /tmp/example.ini** -> triggers the LOAD PATHServer API and prints the results to standard output

**./client --get section.foo.bar** -> triggers the GET KEY ServerAPI and prints the results to standard output

**./client --set section.color.red "roses are red"** -> triggersthe SET KEY VALUE Server API and prints the results to standard output

4.A simple bash script to be used to test the system:

test 1:
i.launch the server
ii.verify the server is up and running by checking its PID and the serverslistening to port 12345
iii.stop the server with a SIGINT unix signal
iv.verify the server is no more running by checking its PID and that thereare no more servers listening to port 12345

test 2:
i.write a test INI file to /tmp
ii.launch the server
iii.launch the client and load the test INI file
iv.verify the load succeededv.launch the client and get one of the values inside the test INI file
vi.verify the get operation succeededvii.launch the client and get a non existent value
viii.verify the operation failed with error 3
ix.launch the client and set a new key value pair
x.verify the set operation succeededxi.stop the server with a SIGINT unix signal 

Simplified INI file reference:[section]foo.bar = some value

Note for configuration:

Inside util.hpp it's possible to configure the log file and logging level
