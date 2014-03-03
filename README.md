ProcessTool
===========
A simple system tool designed for Windows OS used to retrieve running process and software installed. 
* * *
Overview
========
This program possess **two features**:*(1)* Retrieve the list of running processes, including system processes. And it will update the process information every minute.*(2)* It can collect the information of software installed on the machine. If you want, you can even save the two lists into local files.

How to get the source code
--------------------------
Open your git bash and change to the directory into which you want to save the source code, and type the following command:
```bash
$ git clone git@github.com:csuft/ProcessTool.git .
```
When the command finished, you can find a newly created sub directory in the path you choosed.

Prerequisite
------------
Before you start to compile the source code, you have to meet some prerequisites:  
* This project is based on ```VS2010```, so ```Visual Studio 2010 Ultimate Edition``` will be necessary for the beginning.
* ```Qt library version 5.2.1```. **Warning**: you should download the **OpenGL** version for some reason. Otherwise, the executable program you compiled will **lose focus** when you restore the window after minimized.
* BE PATIENT. 

Solutions to Potential Problems
-------------------------------
* **Compilation error:** When compiling the source code, you may encounter a linkage error called: ```Can't resolve QString::fromStdWString()```. It is said to be a bug of Qt framework according to the following reference link(http://stackoverflow.com/questions/4521252/qt-msvc-and-zcwchar-t-i-want-to-blow-up-the-world). After a while of searching, I finally found a solution to this problem: Switch the project option:  ```project property```->```C/C++```->```language```->```make wchar_t as builtin type```.  It is depending on your project settings.
* **Windows lost focus:** For some unknown reasons, a custom widget will surely lose the focus when restored from minimized status if your Qt library is not based on OpenGL version. That is to say, the program will not repaint its sub-widgets in time unless we do something to make a difference. The only solution I know to this problem is install the **OpenGL version** of Qt library.

Implementation
==============

For more information, please visit: http://www.cnblogs.com/csuftzzk.
Screen Shots
============
**Default system theme on Windows 7:**
     
![MethodOne.jpg](https://github.com/csuft/ProcessTool/raw/master/screenshots/2014-03-01_063319.png "")
      
**Custom theme on Window 7:**    
 
![MethodOne.jpg](https://github.com/csuft/ProcessTool/raw/master/screenshots/2014-03-02_031320.png "")
![MethodOne.jpg](https://github.com/csuft/ProcessTool/raw/master/screenshots/2014-03-02_031912.png "")
![MethodOne.jpg](https://github.com/csuft/ProcessTool/raw/master/screenshots/2014-03-02_031949.png "")
* * *

To Do List
==========
* Run on system boot
* Export tables to Microsoft Excels
* System Tray Support(Maybe)
* Retrieve application icons.

Copyright
=========
No permissions need to be granted. You can download, use, modify or redistribute freely.
