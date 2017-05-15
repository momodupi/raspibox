#Raspibox! -- a TV box based on raspberry 2b</br>
Raspibox is a GUI for TV and NAS based on raspberry pi 2b, 
it is just a rudimentary demo for myself since this is my first time try using raspberry and qt.</br>

##Brife</br>
###Home Page</br>
Providing clock and weather on the home page.</br>
###Video Page</br>
Playing the mkv/flv/avi/mp4/rm/rmvb by using omxplayer and mplay. 
However, because the mplayer lacks of hardware accelerating, video delay might occur while playing rm/rmvb.</br>
Videos are saved in the hdisk(e.g., seagate+orico) or otherwhere.
###Picture Page</br>
Displaying the pictures saved in the hdisk. By using sambe.
Users could upload their photoes or pitures from their smart phones to the hdisk by using app(e.g., es explore)</br>
###Net Page</br>
Playing TV program by using omxplayer. The http sources of TV program reference from the internet.
###Setting Page</br>
Providing some settings for users.</br>

Thanks a lot for the contributors on github and csdn!</br>


##Install</br>
1. sudo apt-get install samba samba-common-bin</br>
2. sudo apt-get install omxplayer</br>
3. sudo apt-get install mplayer</br>
4. install ffmpeg</br>
5. install qt</br>
6. using qt open raspberry.pro, make and run</br>

##Change Log</br>
###2017.2.20</br>
1. First version</br>
